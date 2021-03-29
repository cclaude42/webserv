/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:29:28 by cclaude           #+#    #+#             */
/*   Updated: 2021/03/29 18:30:17 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// Member functions

int		Server::setup(void)
{
	_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_fd == -1)
	{
		std::cerr << RED << "Could not create server." << RESET << std::endl;
		return (-1);
	}
	this->setAddr();
	if (bind(_fd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1)
	{
		std::cerr << RED << "Could not bind port " << _listen.port << "." << RESET << std::endl;
		return (-1);
	}
	if (listen(_fd, 1000) == -1)
	{
		std::cerr << RED << "Could not listen." << RESET << std::endl;
		return (-1);
	}
	return (0);
}

void		Server::setAddr(void)
{
	ft_memset((char *)&_addr, 0, sizeof(_addr));
	_addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = ft_htonl(_listen.host);
	_addr.sin_port = ft_htons(_listen.port);
}

long		Server::accept(void)
{
	long	socket;

	socket = ::accept(_fd, NULL, NULL);
	if (socket == -1)
		std::cerr << RED << "Could not create socket. " << strerror(errno) << RESET << std::endl;
	else
	{
		fcntl(socket, F_SETFL, O_NONBLOCK);
		_requests.insert(std::make_pair(socket, ""));
	}
	return (socket);
}

void		Server::process(long socket, Config & conf)
{
	RequestConfig	requestConf;
	Response		response;
	std::string		recvd = "";

	if (_requests[socket].find("Transfer-Encoding: chunked") != std::string::npos &&
		_requests[socket].find("Transfer-Encoding: chunked") < _requests[socket].find("\r\n\r\n"))
		this->processChunk(socket);

	if (OUT)
	{
		if (_requests[socket].size() < 1000)
			std::cout << "\nRequest :" << std::endl << "[" << YELLOW << _requests[socket] << RESET << "]" << std::endl;
		else
			std::cout << "\nRequest :" << std::endl << "[" << YELLOW << _requests[socket].substr(0, 1000) << "..." << _requests[socket].substr(_requests[socket].size() - 10, 15) << RESET << "]" << std::endl;
	}

	if (_requests[socket] != "")
	{
		Request			request(_requests[socket]);

		if (request.getRet() != 200)
			request.setMethod("GET");

		requestConf = conf.getConfigForRequest(this->_listen,  request.getPath(), request.getHeaders().at("Host"), request.getMethod(), request);

		response.call(request, requestConf);

		_requests.erase(socket);
		_requests.insert(std::make_pair(socket, response.getResponse()));
	}
}

void		Server::processChunk(long socket)
{
	std::string	head = _requests[socket].substr(0, _requests[socket].find("\r\n\r\n"));
	std::string	chunks = _requests[socket].substr(_requests[socket].find("\r\n\r\n") + 4, _requests[socket].size() - 1);
	std::string	subchunk = chunks.substr(0, 100);
	std::string	body = "";
	int			chunksize = strtol(subchunk.c_str(), NULL, 16);
	size_t		i = 0;

	while (chunksize)
	{
		i = chunks.find("\r\n", i) + 2;
		body += chunks.substr(i, chunksize);
		i += chunksize + 2;
		subchunk = chunks.substr(i, 100);
		chunksize = strtol(subchunk.c_str(), NULL, 16);
	}

	_requests[socket] = head + "\r\n\r\n" + body + "\r\n\r\n";
}

int			Server::recv(long socket)
{
	char	buffer[RECV_SIZE] = {0};
	int		ret;

	ret = ::recv(socket, buffer, RECV_SIZE - 1, 0);

	if (ret == 0 || ret == -1)
	{
		this->close(socket);
		if (!ret)
			std::cout << "\rConnection was closed by client.\n" << std::endl;
		else
			std::cout << "\rRead error, closing connection.\n" << std::endl;
		return (-1);
	}

	_requests[socket] += std::string(buffer);

	size_t	i = _requests[socket].find("\r\n\r\n");
	if (i != std::string::npos)
	{
		if (_requests[socket].find("Content-Length: ") == std::string::npos)
		{
			if (_requests[socket].find("Transfer-Encoding: chunked") != std::string::npos)
			{
				if (checkEnd(_requests[socket], "0\r\n\r\n") == 0)
					return (0);
				else
					return (1);
			}
			else
				return (0);
		}

		size_t	len = std::atoi(_requests[socket].substr(_requests[socket].find("Content-Length: ") + 16, 10).c_str());
		if (_requests[socket].size() >= len + i + 4)
			return (0);
		else
			return (1);
	}

	return (1);
}

int			Server::send(long socket)
{
	static std::map<long, size_t>	sent;

	if (sent.find(socket) == sent.end())
		sent[socket] = 0;

	if (OUT && sent[socket] == 0)
	{
		if (_requests[socket].size() < 1000)
			std::cout << "\rResponse :                " << std::endl << "[" << GREEN << _requests[socket] << RESET << "]\n" << std::endl;
		else
			std::cout << "\rResponse :                " << std::endl << "[" << GREEN << _requests[socket].substr(0, 1000) << "..." << _requests[socket].substr(_requests[socket].size() - 10, 15) << RESET << "]\n" << std::endl;
	}

	std::string	str = _requests[socket].substr(sent[socket], RECV_SIZE);
	int	ret = ::send(socket, str.c_str(), str.size(), 0);

	if (ret == -1)
	{
		this->close(socket);
		sent[socket] = 0;
		return (-1);
	}
	else
	{
		sent[socket] += ret;
		if (sent[socket] >= _requests[socket].size())
		{
			_requests.erase(socket);
			sent[socket] = 0;
			return (0);
		}
		else
			return (1);
	}
}

void		Server::close(int socket)
{
	if (socket > 0)
		::close(socket);
	_requests.erase(socket);
}

void		Server::clean(void)
{
	if (_fd > 0)
		::close(_fd);
	_fd = -1;
}

// Getters

long		Server::getFD(void)
{
	return (_fd);
}

// Overloaders

Server &	Server::operator=(const Server & src)
{
	_listen = src._listen;
	_fd = src._fd;
	_addr = src._addr;
	return (*this);
}

// Constructors and destructors

Server::Server(void)
{
	// Wait, that's illegal !
}

Server::Server(const t_listen & listen)
{
	_listen = listen;
	_fd = -1;
	this->setAddr();
}

Server::Server(const Server & src)
{
	*this = src;
}

Server::~Server(void)
{
}

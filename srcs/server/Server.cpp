/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:29:28 by cclaude           #+#    #+#             */
/*   Updated: 2021/03/02 10:37:44 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// Member functions

long		Server::run(Config & conf, long socket)
{
	Request			request;
	RequestConfig	requestConf;
	Response		response;
	std::string		recvd;

	if (socket == 0)
		this->accept();
	else
		_socket = socket;

	recvd = this->recv();

	if (recvd != "")
	{
		request.parse(recvd);

		requestConf = conf.getConfigForRequest(this->_listen, request.getPath(), request.getHeaders().at("Host"));


		//	DEBUG
		std::cout << RED << "Reqested path : " << request.getPath() << RESET << '\n';
		std::cout << YELLOW << "Content-Location : " << requestConf.getContentLocation() << RESET << '\n';
		std::cout << YELLOW << "Full path : " << requestConf.getPath() << RESET << '\n';

		//  /DEBUG

		response.call(request, requestConf);

		this->send(response.getResponse());
	}

	if (_closed)
	{
		this->close();
		return (-1);
	}
	else
		return (_socket);
}

void		Server::setup(void)
{
	_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_fd == -1)
		std::cerr << RED << "Could not create server." << RESET << std::endl;
	this->setAddr();
	if (bind(_fd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1)
		std::cerr << RED << "Could not bind port " << _listen.port << "." << RESET << std::endl;
	if (listen(_fd, 1) == -1)
		std::cerr << RED << "Could not listen." << RESET << std::endl;
}

void		Server::setAddr(void)
{
	ft_memset((char *)&_addr, 0, sizeof(_addr));
	_addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = ft_htonl(_listen.host);
	_addr.sin_port = ft_htons(_listen.port);
}

void		Server::accept(void)
{
	unsigned int	addrlen;

	_socket = ::accept(_fd, (struct sockaddr *)&_addr, (socklen_t *)&addrlen);
	if (_socket == -1)
		std::cerr << RED << "Could not create socket." << RESET << std::endl;
	fcntl(_socket, F_SETFL, O_NONBLOCK);
}

std::string	Server::recv(void)
{
	char		buffer[4096];
	std::string	request = "";
	int			ret;
	int			tries = 0;

	_closed = 0;
	for ( int i = 0 ; i < 5000 ; i++ )
	{
		ft_memset(buffer, 0, 4096);
		ret = ::recv(_socket, buffer, 4095, 0);
		if (ret == -1)
			tries++;
		else if (ret == 0)
			_closed = 1;
		request += std::string(buffer);
	}

	if (_closed)
		std::cout << "Connection was closed." << std::endl;
	else if (tries == 5000)
		std::cerr << RED << "Could not read request." << RESET << std::endl;
	else
		std::cout << "Request :" << std::endl << "[" << YELLOW << request << RESET << "]" << std::endl;

	return (request);
}

void		Server::send(std::string resp)
{
	std::cout << "Response :" << std::endl << "[" << GREEN << resp << RESET << "]" << std::endl;

	if (::send(_socket, resp.c_str(), resp.size(), 0) == -1)
		std::cerr << RED << "Could not send response." << RESET << std::endl;
}

void		Server::close(void)
{
	if (_socket > 0)
		::close(_socket);
	_socket = -1;
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
	_socket = src._socket;
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
	_socket = -1;
	this->setAddr();
}

Server::Server(const Server & src)
{
	*this = src;
}

Server::~Server(void)
{
}

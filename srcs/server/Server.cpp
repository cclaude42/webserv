/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:29:28 by cclaude           #+#    #+#             */
/*   Updated: 2021/03/01 11:49:04 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// Member functions

void		Server::run(Config & conf)
{
	Request			request;
	RequestConfig	requestConf;
	Response		response;
	std::string		recvd;

	this->accept();

	recvd = this->recv();
	if (recvd == "")
		return ;

	request.parse(recvd);

	requestConf = conf.getConfigForRequest(this->_listen, request.getPath(), request.getHeaders().at("Host"));


	//DEBUG
	std::cout << RED << "Path :\n" << request.getPath() << RESET << '\n';

	// CgiHandler		cgiH(request, requestConf);
	// std::cout << RED << "CGI :\n\n";
	// std::cout << cgiH.executeCgi("test_us/cgi_tester");
	// std::cout << RESET << "\n\n";

	// std::cout << YELLOW << "END OF CGI" << RESET << '\n';


	//  /DBEUG

	response.call(request, requestConf);

	this->send(response.getResponse());

	this->close();
}

void		Server::setup(void)
{
	_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_fd == -1)
		std::cerr << "Could not create server." << std::endl;
	this->setAddr();
	if (bind(_fd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1)
		std::cerr << "Could not bind port " << _listen.port << "." << std::endl;
	if (listen(_fd, 1) == -1)
		std::cerr << "Could not listen." << std::endl;
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
	int			tries = 0;

	for ( int i = 0 ; i < 5000 ; i++ )
	{
		ft_memset(buffer, 0, 4096);
		if (::recv(_socket, buffer, 4095, 0) == -1)
			tries++;
		request += std::string(buffer);
	}

	if (tries == 5000)
		std::cerr << RED << "Could not read request." << RESET << std::endl;
	std::cout << "Request :" << std::endl << "[" << YELLOW << request << RESET << "]" << std::endl;

	return (request);
}

void		Server::send(std::string resp)
{
	std::cout << "Response :" << std::endl << "[" << GREEN << resp << RESET << "]" << std::endl;

	if (::send(_socket, resp.c_str(), resp.size(), 0) == -1)
		std::cerr << "Could not send response." << std::endl;
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

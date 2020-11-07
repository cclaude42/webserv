/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:29:28 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/07 15:49:12 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// Member functions

void		Server::setup(void)
{
	_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_fd == -1)
		std::cout << "Could not create server." << std::endl;
	this->setAddr();
	if (bind(_fd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1)
		std::cout << "Could not bind port." << std::endl;
	if (listen(_fd, 10) == -1)
		std::cout << "Could not listen." << std::endl;
}

void		Server::setAddr(void)
{
	ft_memset((char *)&_addr, 0, sizeof(_addr));
	_addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = ft_htonl(INADDR_ANY);
	_addr.sin_port = ft_htons(8080);
}

void		Server::accept(void)
{
	unsigned int	addrlen;

	_socket = ::accept(_fd, (struct sockaddr *)&_addr, (socklen_t *)&addrlen);
	if (_socket == -1)
		std::cout << "Could not create socket." << std::endl;
}

std::string	Server::recv(void)
{
	char		buffer[4096];
	std::string	request = "";
	int			read = 4095;

	while (read == 4095)
	{
		ft_memset(buffer, 0, 4096);
		read = ::recv(_socket, buffer, 4095, 0);
		if (read == -1)
			std::cout << "Could not read request." << std::endl;
		request += std::string(buffer);
	}

	return (request);
}

void		Server::send(std::string resp)
{
	if (::send(_socket, resp.c_str(), resp.size(), 0) == -1)
		std::cout << "Could not send response." << std::endl;
}

void		Server::close(void)
{
	::close(_socket);
}

void		Server::end(void)
{
	::close(_fd);
}

// Overloaders

Server &	Server::operator=(const Server & src)
{
	(void)src;
	return (*this);
}

// Constructors and destructors

Server::Server(void)
{
	_fd = -1;
	_socket = -1;
	_request = "NONE";
	this->setAddr();
}

Server::Server(const Server & src)
{
	(void)src;
}

Server::~Server(void)
{
}

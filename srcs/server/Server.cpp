/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:29:28 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/04 16:32:00 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// Member functions

void		Server::setup(void)
{
	_fd = socket(AF_INET, SOCK_STREAM, 0);
	this->setAddr();
	bind(_fd, (struct sockaddr *)&_addr, sizeof(_addr));
	listen(_fd, 10);
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

	_socket = ::accept(_fd, (struct sockaddr *)&_addr, &addrlen);
}

std::string	Server::recv(void)
{
	char		buffer[4096];
	std::string	request = "";
	int			read = 1;

	while (read)
	{
		ft_memset(buffer, 0, 4096);
		read = ::recv(_socket, buffer, 4095, 0);
		request += std::string(buffer);
	}

	std::cout << "Received something !" << std::endl;

	return (request);
}

void		Server::send(std::string resp)
{
	// ::send(_fd, resp.c_str(), resp.size(), 0);
	std::cout << resp;
}

void		Server::close(void)
{
	::close(_socket);
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

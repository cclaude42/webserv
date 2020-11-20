/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:29:28 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/18 13:16:14 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// Member functions

void		Server::run(Config& conf)
{
	Request		req;
	Response	resp;
	RequestConfig reqConf;
	std::string	request;

	this->accept();

	request = this->recv();
	req.parse(request);

	reqConf = conf.getConfigForRequest(this->_listen, req.getPath(), req.getHeaders().at("Host"));

	resp.setFilename(_tmp_root);
	resp.make(req, reqConf);

	this->send(resp.getResponse());

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
	if (listen(_fd, 10) == -1)
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
		std::cerr << "Could not create socket." << std::endl;
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
			std::cerr << "Could not read request." << std::endl;
		request += std::string(buffer);
	}

	return (request);
}

void		Server::send(std::string resp)
{
	// std::cout << resp << std::endl;

	if (::send(_socket, resp.c_str(), resp.size(), 0) == -1)
		std::cerr << "Could not send response." << std::endl;
}

void		Server::close(void)
{
	::close(_socket);
}

void		Server::clean(void)
{
	::close(_fd);
}

// Getters

long		Server::getFD(void)
{
	return (_fd);
}

// Setters

// Temporary function, only for testing !
void		Server::setTmpRoot(std::string root)
{
	_tmp_root = root;
}

// Overloaders

Server &	Server::operator=(const Server & src)
{
	_fd = src._fd;
	_socket = src._socket;
	_request = src._request;
	_addr = src._addr;
	_listen = src._listen;
	return (*this);
}

// Constructors and destructors

Server::Server(void)
{
	// Wait, that's illegal !
}

Server::Server(const t_listen & listen)
{
	_fd = -1;
	_socket = -1;
	_request = "NONE";
	this->setAddr();
	_listen = listen;
	_tmp_root = "root/index.html";
}

Server::Server(const Server & src)
{
	*this = src;
}

Server::~Server(void)
{
}

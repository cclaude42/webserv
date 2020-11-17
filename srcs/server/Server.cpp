/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:29:28 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/16 19:48:42 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// Member functions

void		Server::setup(int port)
{
	_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_fd == -1)
		std::cout << "Could not create server." << std::endl;
	this->setAddr(port);
	if (bind(_fd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1)
		std::cout << "Could not bind port." << std::endl;
	if (listen(_fd, 10) == -1)
		std::cout << "Could not listen." << std::endl;
}

void		Server::setAddr(int port)
{
	ft_memset((char *)&_addr, 0, sizeof(_addr));
	_addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = ft_htonl(INADDR_ANY);
	_addr.sin_port = ft_htons(port);
}

/*
void		Server::setRequest(Request& req)
{
	this->_req = req;
}

void		Server::setMap()
{
	this->methods.emplace("GET", &Server::get);
}

const Request&	Server::getRequest() const
{
	return this->_req;
}
*/

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
	// std::cout << resp << std::endl;

	if (::send(_socket, resp.c_str(), resp.size(), 0) == -1)
		std::cout << "Could not send response." << std::endl;
}

std::string	Server::answer(std::string method, Request& req)
{
	// THIS IS WHERE THE SHAME BEGINS

	if (method == "GET")
		return this->get_head(req);
	if (method == "HEAD")
		return this->get_head(req);
	if (method == "POST")
		return this->post(req);
	if (method == "PUT")
		return this->put(req);
	if (method == "DELETE")
		return this->ft_delete(req);
	if (method == "CONNECT")
		return this->connect(req);
	if (method == "OPTIONS")
		return this->options(req);
	if (method == "TRACE")
		return this->trace(req);
	
	// PLEASE DO NOT LET THIS GO INTO PROD
	// THIS IS REALLY SHAMEFULL

	std::cout << "BAD REQUEST MOFO\n";
	return ("BAD REQUEST 400 MOFO");
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
//	_request = "NONE";
	_rootPath = "/home/hannibal/Documents/Cursus42/webserv/root";
	this->setAddr();
}

Server::Server(const Server & src)
{
	(void)src;
}

Server::~Server(void)
{
}

// HTTP METHODS
/*
std::string	Server::call(const std::string& met, Request& req)
{
	std::string	ret = this->_methods[met](req);

	return ret;
}
*/

std::string		Server::get_head(Request& req)
{
	std::string content;
	std::string	ret;
	ResponseHeader rh;

	content = readContent(req.getPath());
	ret = rh.getHeader(content, req.getPath(), req.getRet());
	std::cout << "=======RESPONSE=======\n";
	std::cout << ret << '\n';
	std::cout << "======================\n";
	if (req.getMethod() == "GET")
		ret += content;
	return ret;
}

std::string		Server::post(Request& req)
{
	(void)req;
	return "Yeeahaw from post\n";
}

std::string		Server::put(Request& req)
{
	(void)req;
	return "Yeeahaw from put\n";
}

std::string		Server::ft_delete(Request& req)
{
	(void)req;
	return "Yeeahaw from delete\n";
}

std::string		Server::connect(Request& req)
{
	(void)req;
	return "Yeeahaw from connect\n";
}

std::string		Server::options(Request& req)
{
	(void)req;
	return "Yeeahaw from options\n";
}

std::string		Server::trace(Request& req)
{
	(void)req;
	return "Yeeahaw from trace\n";
}


std::string		Server::readContent(std::string path)
{
	path = this->_rootPath + path;
	std::cout << "combined path : " << path << '\n';
	std::ifstream t(path);
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
}


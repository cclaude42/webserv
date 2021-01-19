/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:27:33 by hbaudet           #+#    #+#             */
/*   Updated: 2021/01/19 15:43:09 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

std::vector<std::string>	Request::methods = initMethods();

std::vector<std::string>		initMethods()
{
	std::vector<std::string>	methods;

	methods.push_back("GET");
	methods.push_back("HEAD");
	methods.push_back("POST");
	methods.push_back("PUT");
	methods.push_back("DELETE");
	methods.push_back("CONNECT");
	methods.push_back("OPTIONS");
	methods.push_back("TRACE" );
	
	return methods;
}

Request::Request() :
	_method(""), _version(""), _ret(200), _body(""), _port(80), _path(""), _querry(""), _raw("")
{
	if (PRINT)
		std::cout << "Constructor called\n";

	this->resetHeaders();
}

Request::Request(const std::string& str) :
	_method (""), _version(""), _ret(200), _body(""), _port(80), _path(""), _querry(""), _raw("")
{
	if (PRINT)
		std::cout << "std:string constructor called\n";

	this->resetHeaders();
	this->parse(str); 
	if (this->_ret != 200)
		std::cout << "Parse error : " << this->_ret << '\n';
}

Request::~Request()
{
	if (PRINT)
		std::cout << "Destructor called\n";
}

Request::Request(const Request& obj)
{
	if (PRINT)
		std::cout << "Copy Constructor called\n";
	*this = obj;
}

Request&	Request::operator=(const Request& obj)
{
	if (PRINT)
		std::cout << "Assignation operator called\n";
	this->_headers = obj.getHeaders();
	this->_method = obj.getMethod();
	this->_version = obj.getVersion();
	this->_ret = obj.getRet();
	this->_body = obj.getBody();
	this->_port = obj.getPort();
	this->_path = obj.getPath();

	return *this;
}

/*** GETTERS ***/

const std::map<std::string, std::string>&	Request::getHeaders() const
{
	return this->_headers;
}

const std::string&	Request::getMethod() const
{
	return this->_method;
}

const std::string&	Request::getVersion() const
{
	return this->_version;
}

int					Request::getRet() const
{
	return this->_ret;
}

const std::string&	Request::getBody() const
{
	return this->_body;
}

int					Request::getPort() const
{
	return this->_port;
}

std::string			Request::getPath() const
{
	return this->_path;
}

std::string			Request::getQuerry() const
{
	return this->_querry;
}

std::string			Request::getRaw() const
{
	return this->_raw;
}

/*** SETTERS ***/
/*
void	Request::setHeader(const std::string& key, const std::string& value)
{
	this->_headers[key] = value;
}
*/

void	Request::setBody(std::vector<std::string> line, size_t i)
{
	while (i < line.size())
	{
		this->_body.append(line[i]);
		this->_body.push_back('\n');
		i++;
	}
}
void	Request::setBody(std::string bod)
{
	this->_body = bod;
}

void	Request::setRet(int ret)
{
	this->_ret = ret;
}

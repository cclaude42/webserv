/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:27:33 by hbaudet           #+#    #+#             */
/*   Updated: 2021/03/11 16:26:30 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"


std::vector<std::string>		Request::initMethods()
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

std::vector<std::string>	Request::methods = Request::initMethods();

Request::Request() :
	_method(""), _version(""), _ret(200), _body(""), _port(80), _path(""), _query(""), _raw("")
{
	if (PRINT)
		std::cout << "Constructor called\n";

	this->resetHeaders();
}

Request::Request(const std::string& str) :
	_method (""), _version(""), _ret(200), _body(""), _port(80), _path(""), _query(""), _raw("")
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

std::string			Request::getQuery() const
{
	return this->_query;
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
		if (line[i] != "\r")
		{
			this->_body.append(line[i]);
			if (i != line.size() - 1)
				this->_body.push_back('\n');
		}
		i++;

		// size_t j;
		// for (j = 0; j < line[i].size() && line[i][j] != '\r' && line[i][j] != '\n'; j++);
		// while (line[i][line[i].size() - 1] == '\r' || line[i][line[i].size() - 1] == '\n')
		// 	line[i].resize(line[i].size() - 1);
		// this->_body.append(line[i].substr(j));
		// this->_body.push_back('\n');
		// i++;
	}
}
void	Request::setBody(const std::string &bod)
{
	this->_body = bod;
}

void	Request::setRet(int ret)
{
	this->_ret = ret;
}

void	Request::setMethod(const std::string &method)
{
	this->_method = method;
}
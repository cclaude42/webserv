/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:27:33 by hbaudet           #+#    #+#             */
/*   Updated: 2021/03/22 11:40:52 by hbaudet          ###   ########.fr       */
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
	this->_env_for_cgi.clear();
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
	this->_env_for_cgi = obj.getEnv();
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

const std::map<std::string, std::string>&	Request::getEnv() const
{
	return this->_env_for_cgi;
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

void	Request::setBody(const std::vector<std::string> &line, size_t i)
{
	this->_body.clear();
	for (; i < line.size(); i++)
	{
		if (line[i].size() && line[i][0] != '\r')
			this->_body.append(line[i] + "\n");
	}
	if (this->_body.size() > 0 && this->_body[this->_body.size() - 1] == '\n')
		pop(this->_body);
	if (this->_body.size() > 0 && this->_body[this->_body.size() - 1] == '\r')
		pop(this->_body);
	// std::cerr << RED << "Set body (" << this->_body.size() << ") : " << this->_body.substr(0, 20) << RESET << "\n";
}

void	Request::setRet(int ret)
{
	this->_ret = ret;
}

void	Request::setMethod(const std::string &method)
{
	this->_method = method;
}

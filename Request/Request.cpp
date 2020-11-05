/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:27:33 by hbaudet           #+#    #+#             */
/*   Updated: 2020/11/05 16:39:13 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request() : method(""), version(""), ret(200)
{
	if (PRINT)
		std::cout << "Constructor called\n";
	this->resetHeaders();
}

Request::Request(const char *str) : method (""), version(""), ret(200)
{
	if (PRINT)
		std::cout << "C-String constructor called\n";

	this->resetHeaders();
	this->parse(str);
	if (this->ret != 200)
		std::cout << "Parse error : " << this->ret << '\n';
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
	this->headers = obj.getHeaders();
	this->method = obj.getMethod();
	this->version = obj.getVersion();
	this->ret = obj.getRet();

	return *this;
}

/*** GETTERS ***/

const std::map<std::string, std::string>&	Request::getHeaders() const
{
	return this->headers;
}

const std::string&	Request::getMethod() const
{
	return this->method;
}

const std::string&	Request::getVersion() const
{
	return this->version;
}

const int			Request::getVersion() const
{
	return this->ret;
}

/*** SETTERS ***/

void	Request::setHeader(const std::string& key, const std::string& value)
{
	this->headers[key] = value;
}

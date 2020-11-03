/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:27:33 by hbaudet           #+#    #+#             */
/*   Updated: 2020/11/03 18:55:40 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request()
{
	if (PRINT)
		std::cout << "Constructor called\n";
	this->resetHeaders();
}

Request::Request(const char *str)
{
	if (PRINT)
		std::cout << "C-String constructor called\n";

	this->resetHeaders();
	this->parse(str);
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

	return *this;
}

/*** GETTERS ***/

const std::map<std::string, std::string>&	Request::getHeaders() const
{
	return this->headers;
}

/*** SETTERS ***/

void	Request::setHeader(const std::string& key, const std::string& value)
{
	this->headers[key] = value;
}

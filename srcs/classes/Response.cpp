/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:18:58 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/04 16:14:41 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

// Member functions

void			Response::make(void)
{
	this->fillContent();
	// Set header accordingly
	_response = _header.getHeader() + _content;
}

void			Response::fillContent(void)
{
	_content = "yyy";
	_content += "\r\n";
}

// Setter functions

void			Response::setFilename(std::string filename)
{
	_filename = filename;
}

// Getter functions

std::string		Response::getResponse(void)
{
	return (_response);
}

// Overloaders

Response & Response::operator=(const Response & src)
{
	(void)src;
	return (*this);
}

// Constructors and destructors

Response::Response(void)
{

}

Response::Response(const Response & src)
{
	(void)src;
}

Response::~Response(void)
{
}

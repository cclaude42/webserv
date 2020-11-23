/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:18:58 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/19 15:54:15 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

// Member functions

void			Response::call(Request & request, RequestConfig & requestConf)
{
	ResponseHeader	head;

	if (request.getMethod() == "GET")
	{
		fillContent(requestConf.getPath());
		_response = head.getHeader(_content, requestConf.getPath(), _code) + _content;
	}
	else if (request.getMethod() == "HEAD")
	{
		fillContent(requestConf.getPath());
		_response = head.getHeader(_content, requestConf.getPath(), _code);
	}
	else if (request.getMethod() == "HEAD")
}

void			Response::get(void)
{

}

void			Response::head(void)
{

}

void			Response::post(void)
{

}

void			Response::get(void)
{

}

void			Response::get(void)
{

}

void			Response::get(void)
{

}

void			Response::get(void)
{

}

void			Response::fillContent(std::string path)
{
	int		fd = open(path.c_str(), O_RDONLY);
	char	buffer[4096];
	int		ret = 4095;

	_content = "";
	while (ret == 4095)
	{
		ft_memset(buffer, 0, 4096);
		ret = read(fd, buffer, 4095);
		_content += std::string(buffer);
	}

	close(fd);
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
	_code = 200;
}

Response::Response(const Response & src)
{
	(void)src;
}

Response::~Response(void)
{
}

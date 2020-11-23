/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:18:58 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/23 17:41:04 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

// Member functions

void			Response::call(Request & request, RequestConfig & requestConf)
{
	if (request.getMethod() == "GET")
		getMethod(requestConf);
	else if (request.getMethod() == "HEAD")
		headMethod(requestConf);
}

void			Response::getMethod(RequestConfig & requestConf)
{
	ResponseHeader	head;

	fillContent(requestConf.getPath());
	_response = head.getHeader(_content, requestConf.getPath(), _code) + _content;
}

void			Response::headMethod(RequestConfig & requestConf)
{
	ResponseHeader	head;

	fillContent(requestConf.getPath());
	_response = head.getHeader(_content, requestConf.getPath(), _code);
}

void			Response::postMethod(void)
{

}

void			Response::putMethod(void)
{

}

void			Response::deleteMethod(void)
{

}

void			Response::connectMethod(void)
{

}

void			Response::optionsMethod(void)
{

}

void			Response::traceMethod(void)
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

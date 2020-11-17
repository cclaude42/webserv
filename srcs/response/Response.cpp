/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:18:58 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/17 20:33:30 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

// Member functions

void			Response::make(void)
{
	ResponseHeader	head;

	fillContent();
	// Set header accordingly
	_response = head.getHeader(_content, _filename, _code) + _content;
}

void			Response::fillContent(void)
{
	int		fd = open(_filename.c_str(), O_RDONLY);
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
	_code = 200;
}

Response::Response(const Response & src)
{
	(void)src;
}

Response::~Response(void)
{
}

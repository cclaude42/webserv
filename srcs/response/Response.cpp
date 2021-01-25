/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:18:58 by cclaude           #+#    #+#             */
/*   Updated: 2021/01/25 19:54:52 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

// Member functions

void			Response::call(Request & request, RequestConfig & requestConf)
{
	_code = 200;
	_path = requestConf.getPath();

	if (request.getMethod() == "GET")
		getMethod();
	else if (request.getMethod() == "HEAD")
		headMethod();
	else if (request.getMethod() == "POST")
		postMethod();
	else if (request.getMethod() == "PUT")
		putMethod(request.getBody());
	else if (request.getMethod() == "DELETE")
		deleteMethod();
	else if (request.getMethod() == "CONNECT")
		connectMethod();
	else if (request.getMethod() == "OPTIONS")
		optionsMethod();
	else if (request.getMethod() == "TRACE")
		traceMethod(request);
}

// Methods

void			Response::getMethod(void)
{
	ResponseHeader	head;

	_code = readContent();
	_response = head.getHeader(_content, _path, _code) + _content;
}

void			Response::headMethod(void)
{
	ResponseHeader	head;

	_code = readContent();
	_response = head.getHeader(_content, _path, _code);
}

void			Response::postMethod(void)
{
	// NEED CGI ?
}

void			Response::putMethod(std::string content)
{
	ResponseHeader	head;

	_code = writeContent(content);
	_response = head.getHeader(_content, _path, _code);
}

void			Response::deleteMethod(void)
{
	ResponseHeader	head;

	if (fileExists(_path))
	{
		if (remove(_path.c_str()) == 0)
			_code = 204;
		else
			_code = 403;
	}
	else
		_code = 404;

	_response = head.getHeader(_content, _path, _code);
}

void			Response::connectMethod(void)
{
	// LINK TO OTHER SERVER ?
}

void			Response::optionsMethod(void)
{
	ResponseHeader	head;

	_code = readContent();
	_response = head.getHeader(_content, _path, _code);

}

void			Response::traceMethod(Request & request)
{
	_response = request.getRaw();
}

// Utils

int				Response::readContent(void)
{
	std::ifstream	file;

	_content = "";

	if (fileExists(_path) == 0)
		return (404);

	file.open(_path.c_str(), std::ifstream::in);
	if (file.is_open() == false)
		return (403);

	_content.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	file.close();

	return (200);
}

int				Response::writeContent(std::string content)
{
	std::ofstream	file;
	int				ret = 204;

	if (fileExists(_path) == 0)
		ret = 201;

	file.open(_path.c_str(), std::ofstream::out | std::ofstream::trunc);

	if (file.is_open() == false)
		return (403);

	file << content;
	file.close();

	return (ret);
}

int				Response::fileExists(std::string path)
{
	struct stat		stats;

	if (stat(path.c_str(), &stats) == 0)
		return (1);
	return (0);
}

// Getter functions

std::string		Response::getResponse(void)
{
	return (_response);
}

// Overloaders

Response & Response::operator=(const Response & src)
{
	_response = src._response;
	_content = src._content;
	_path = src._path;
	_code = src._code;
	return (*this);
}

// Constructors and destructors

Response::Response(void)
{
}

Response::Response(const Response & src)
{
	*this = src;
}

Response::~Response(void)
{
}

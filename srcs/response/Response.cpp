/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:18:58 by cclaude           #+#    #+#             */
/*   Updated: 2021/02/23 15:57:09 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

// Member functions

void			Response::call(Request & request, RequestConfig & requestConf)
{
	_code = 200;
	_path = requestConf.getPath();

	if (request.getMethod() == "GET")
		getMethod(request, requestConf);
	else if (request.getMethod() == "HEAD")
		headMethod();
	else if (request.getMethod() == "POST")
		postMethod(request, requestConf);
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

void			Response::getMethod(Request & request, RequestConfig & requestConf)
{
	ResponseHeader	head;

	if (requestConf.getCgiPass() != "")
	{
		CgiHandler	cgi(request, requestConf);

		_content = cgi.executeCgi(requestConf.getCgiPass());

		_code = 200;// Placeholder
	}
	else
		_code = readContent();

	_response = head.getHeader(_content, _path, _code) + _content;
}

void			Response::headMethod(void)
{
	ResponseHeader	head;

	_code = readContent();
	_response = head.getHeader(_content, _path, _code);
}

void			Response::postMethod(Request & request, RequestConfig & requestConf)
{
	ResponseHeader	head;

	if (requestConf.getCgiPass() != "")
	{
		CgiHandler	cgi(request, requestConf);

		_content = cgi.executeCgi(requestConf.getCgiPass());

		_code = 200;// Placeholder
	}
	else
	{
		srand(time(NULL));
		// int	list[] = { 100, 101, 200, 201, 202, 203, 204, 205, 206, 300, 301, 302, 303, 304, 305, 306, 307, 400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413, 414, 415, 416, 417, 500, 501, 502, 503, 504, 505 };
		_code = 405;// Making shit up
		_content = "POST request with no executable ?";
	}

	_response = head.getHeader(_content, _path, _code) + _content;
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
	std::ifstream		file;
	std::stringstream	buffer;

	_content = "";

	if (fileExists(_path) == 0)
		return (404);

	file.open(_path.c_str(), std::ifstream::in);
	if (file.is_open() == false)
		return (403);

	buffer << file.rdbuf();
	_content = buffer.str();

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

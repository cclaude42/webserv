/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:18:58 by cclaude           #+#    #+#             */
/*   Updated: 2021/03/03 19:35:03 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

// Member functions

void			Response::call(Request & request, RequestConfig & requestConf)
{
	_code = request.getRet();
	_path = requestConf.getPath();

	if (requestConf.getAllowedMethods().find(request.getMethod()) == requestConf.getAllowedMethods().end())
	{
		ResponseHeader	head;

		_code = 405;
		_response = head.notAllowed(requestConf.getAllowedMethods(), requestConf.getContentLocation()) + "\r\n";

		return ;
	}

	if (request.getMethod() == "GET")
		getMethod(request, requestConf);
	else if (request.getMethod() == "HEAD")
		headMethod(requestConf);
	else if (request.getMethod() == "POST")
		postMethod(request, requestConf);
	else if (request.getMethod() == "PUT")
		putMethod(request.getBody(), requestConf);
	else if (request.getMethod() == "DELETE")
		deleteMethod(requestConf);
	else if (request.getMethod() == "CONNECT")
		connectMethod(requestConf);
	else if (request.getMethod() == "OPTIONS")
		optionsMethod(requestConf);
	else if (request.getMethod() == "TRACE")
		traceMethod(request, requestConf);
}

// Methods

void			Response::getMethod(Request & request, RequestConfig & requestConf)
{
	ResponseHeader	head;

	if (requestConf.getCgiPass() != "")
	{
		CgiHandler	cgi(request, requestConf);

		std::cout << "Executing CGI\n";
		_content = cgi.executeCgi(requestConf.getCgiPass());
		std::cout << "Finished executing CGI\n";

		_code = 200;// Placeholder
	}
	else if  (_code == 200)
	{
		_code = readContent();
	}
	else
	{
		_content = "\r\n<html><head><title>" + to_string(_code) +"</title></head><body><h1>ERROR ";
		_content += to_string(_code) + "</h1></body></html>";
	}
	_response = head.getHeader(_content, _path, _code, requestConf.getContentLocation()) + _content + "\r\n";
}

void			Response::headMethod(RequestConfig & requestConf)
{
	ResponseHeader	head;

	_code = readContent();
	_response = head.getHeader(_content, _path, _code, requestConf.getContentLocation());
}

void			Response::postMethod(Request & request, RequestConfig & requestConf)
{
	ResponseHeader	head;

	if (requestConf.getCgiPass() != "")
	{
		CgiHandler	cgi(request, requestConf);

		std::cout << "Executing CGI\n";
		_content = cgi.executeCgi(requestConf.getCgiPass());
		std::cout << "Finished executing CGI\n";

		_code = 200;// Placeholder
	}
	else
	{
		srand(time(NULL));
		// int	list[] = { 100, 101, 200, 201, 202, 203, 204, 205, 206, 300, 301, 302, 303, 304, 305, 306, 307, 400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413, 414, 415, 416, 417, 500, 501, 502, 503, 504, 505 };
		_code = 405;// Making shit up
		_content = "\r\n<html><head><title>405</title></head><body>405 Forbidden yo!</body></html>\r\n";
	}

	_response = head.getHeader(_content, _path, _code, requestConf.getContentLocation()) + _content + "\r\n";
}

void			Response::putMethod(std::string content, RequestConfig & requestConf)
{
	ResponseHeader	head;

	_code = writeContent(content);
	_response = head.getHeader(_content, _path, _code, requestConf.getContentLocation()) + "\r\n";
}

void			Response::deleteMethod(RequestConfig & requestConf)
{
	ResponseHeader	head;

	if (pathIsFile(_path))
	{
		if (remove(_path.c_str()) == 0)
			_code = 204;
		else
			_code = 403;
	}
	else
		_code = 404;

	_response = head.getHeader(_content, _path, _code, requestConf.getContentLocation());
}

void			Response::connectMethod(RequestConfig & requestConf)
{
	// LINK TO OTHER SERVER ?
	(void)requestConf;
}

void			Response::optionsMethod(RequestConfig & requestConf)
{
	ResponseHeader	head;

	_code = readContent();
	_response = head.getHeader(_content, _path, _code, requestConf.getContentLocation());

}

void			Response::traceMethod(Request & request, RequestConfig & requestConf)
{
	(void)requestConf;
	_response = request.getRaw();
}

// Utils

int				Response::readContent(void)
{
	std::ifstream		file;
	std::stringstream	buffer;

	_content = "\r\n";

	if (pathIsFile(_path) == 0)
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

	if (pathIsFile(_path))
	{
		file.open(_path.c_str());
		file << content;
		file.close();
		return (204);
	}
	else
	{
		file.open(_path.c_str(), std::ofstream::out | std::ofstream::trunc);
		if (file.is_open() == false)
			return (403);

		file << content;
		file.close();
		return (201);
	}
}

int				Response::fileExists(std::string path) //deprecated, replaced by ::pathIsFile()
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

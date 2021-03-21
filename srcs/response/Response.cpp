/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:18:58 by cclaude           #+#    #+#             */
/*   Updated: 2021/03/21 13:23:12 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

// Member functions

void			Response::call(Request & request, RequestConfig & requestConf)
{
	_code = request.getRet();
	_path = requestConf.getPath();

	if (requestConf.getAllowedMethods().find(request.getMethod()) == requestConf.getAllowedMethods().end())
		_code = 405;
	else if (requestConf.getClientBodyBufferSize() < request.getBody().size())
		_code = 413;

	if (_code == 405 || _code == 413)
	{
		ResponseHeader	head;

		_response = head.notAllowed(requestConf.getAllowedMethods(), requestConf.getContentLocation(), _code) + "\r\n";
		return ;
	}
	timeit("RESPONSE START");
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
		timeit("RESPONSE END");
}

// Methods

void			Response::getMethod(Request & request, RequestConfig & requestConf)
{
	ResponseHeader	head;

	(void)request;
	// if (requestConf.getCgiPass() != "")
	// {
	// 	CgiHandler	cgi(request, requestConf);

	// 	std::cout << "Executing CGI\n";
	// 	_response = cgi.executeCgi(requestConf.getCgiPass());
	// 	std::cout << "Finished executing CGI\n";

	// 	_code = 200;// Placeholder
	// }
	if  (_code == 200)
	{
		_code = readContent();
	}
	else
	{
		_response = "";
	}

	if (_response != "")
		_response += "\r\n";
	else
		_response = head.getHeader(_response.size(), _path, _code, requestConf.getContentLocation()) + "\r\n";
}

void			Response::headMethod(RequestConfig & requestConf)
{
	ResponseHeader	head;

	_code = readContent();
	_response = head.getHeader(_response.size(), _path, _code, requestConf.getContentLocation());
}

void			Response::postMethod(Request & request, RequestConfig & requestConf)
{
	ResponseHeader	head;

	timeit("RESPONSE POST");
	if (requestConf.getCgiPass() != "")
	{
		CgiHandler	cgi(request, requestConf);
		timeit("RESPONSE POST CGI INIT");
		_response = cgi.executeCgi(requestConf.getCgiPass());
		timeit("RESPONSE POST CGI EXEC");
		while (countSubstr(_response, "\r\n\r\n") > 0 || !checkStart(_response, "\r\n"))
		{
			// std::cerr << "Parsed : [" << _response.substr(0, _response.find("\r\n")) << "]" << std::endl;
			_response = _response.substr(_response.find("\r\n") + 2, _response.size());
		}
		timeit("RESPONSE POST CGI PARSE");
		while (!checkEnd(_response, "\r\n"))
			_response = _response.substr(0, _response.size() - 2);
		timeit("RESPONSE POST CHECKEND");
		_code = 200;
	}
	else
	{
		_code = 204;
		_response = "";
	}
	_response = head.getHeader(_response.size(), _path, _code, requestConf.getContentLocation()) + "\r\n" + _response;
	timeit("RESPONSE POST HEADER");
}

void			Response::putMethod(std::string content, RequestConfig & requestConf)
{
	ResponseHeader	head;

	_code = writeContent(content);
	_response = head.getHeader(_response.size(), _path, _code, requestConf.getContentLocation()) + "\r\n";
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

	_response = head.getHeader(_response.size(), _path, _code, requestConf.getContentLocation()) + "\r\n";
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
	_response = head.getHeader(_response.size(), _path, _code, requestConf.getContentLocation()) + "\r\n";

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

	_response = "";

	if (pathIsFile(_path) == 0)
		return (404);

	file.open(_path.c_str(), std::ifstream::in);
	if (file.is_open() == false)
		return (403);

	buffer << file.rdbuf();
	_response = buffer.str();

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

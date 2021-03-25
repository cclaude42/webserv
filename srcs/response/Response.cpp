/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:18:58 by cclaude           #+#    #+#             */
/*   Updated: 2021/03/25 10:55:28 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

// Static Assets

std::map<std::string, void (Response::*)(Request &, RequestConfig &)>	Response::initMethods() 
{
	std::map<std::string, void (Response::*)(Request &, RequestConfig &)> map;
	
	map["GET"] = &Response::getMethod;
	map["HEAD"] = &Response::headMethod;
	map["POST"] = &Response::postMethod;
	map["PUT"] = &Response::putMethod;
	map["DELETE"] = &Response::deleteMethod;
	map["CONNECT"] = &Response::connectMethod;
	map["OPTIONS"] = &Response::optionsMethod;
	map["TRACE"] = &Response::traceMethod;

	return map;
}

std::map<std::string, void (Response::*)(Request &, RequestConfig &)> Response::_method = Response::initMethods();

// Member functions

void			Response::call(Request & request, RequestConfig & requestConf)
{
	_errorMap = requestConf.getErrorPage();
	_isAutoIndex = requestConf.getAutoIndex();
	_code = request.getRet();
	_hostPort.host = requestConf.getHostPort().host;
	_hostPort.port = requestConf.getHostPort().port;
	_path = requestConf.getPath();

	std::cerr << "Requested Method : " << request.getMethod() << '\n';
	std::cerr << "Allowed Methods : " << '\n';
	for (std::set<std::string>::iterator it = requestConf.getAllowedMethods().begin(); it != requestConf.getAllowedMethods().end(); it++)
		std::cerr << *it << '\n';
	if (requestConf.getAllowedMethods().find(request.getMethod()) == requestConf.getAllowedMethods().end())
		_code = 405;
	else if (requestConf.getClientBodyBufferSize() < request.getBody().size())
		_code = 413;

	if (_code == 405 || _code == 413)
	{
		ResponseHeader	head;

		_response = head.notAllowed(requestConf.getAllowedMethods(), requestConf.getContentLocation(), _code, requestConf.getLang()) + "\r\n";
		return ;
	}

	
	(this->*Response::_method[request.getMethod()])(request, requestConf);

	// if (request.getMethod() == "GET")
	// 	getMethod(request, requestConf);
	// else if (request.getMethod() == "HEAD")
	// 	headMethod(request, requestConf);
	// else if (request.getMethod() == "POST")
	// 	postMethod(request, requestConf);
	// else if (request.getMethod() == "PUT")
	// 	putMethod(request, requestConf);
	// else if (request.getMethod() == "DELETE")
	// 	deleteMethod(request, requestConf);
	// else if (request.getMethod() == "CONNECT")
	// 	connectMethod(request, requestConf);
	// else if (request.getMethod() == "OPTIONS")
	// 	optionsMethod(request, requestConf);
	// else if (request.getMethod() == "TRACE")
	// 	traceMethod(request, requestConf);
}

// Methods

void			Response::getMethod(Request & request, RequestConfig & requestConf)
{
	ResponseHeader	head;

	if (requestConf.getCgiPass() != "")
	{
		std::cerr << "Running cgi ...\n";
		CgiHandler	cgi(request, requestConf);
		size_t		i = 0;
		size_t		j = _response.size() - 2;

		_response = cgi.executeCgi(requestConf.getCgiPass());

		while (_response.find("\r\n\r\n", i) != std::string::npos || _response.find("\r\n", i) == i)
		{
			std::string	str = _response.substr(i, _response.find("\r\n", i) - i);
			std::cerr << "Found [" << str << "]" << std::endl;
			if (str.find("Status: ") == 0)
				_code = std::atoi(str.substr(8, 3).c_str());
			else if (str.find("Content-type: ") == 0)
				_type = str.substr(14, str.size());
			i += str.size() + 2;
		}
		while (_response.find("\r\n", j) == j)
			j -= 2;

		_response = _response.substr(i, j - i);
	}
	else if  (_code == 200)
		_code = readContent();
	else
		_response = this->readHtml(_errorMap[_code]);
	std::cerr << "TYPE IS" << _type << std::endl;
	_response = head.getHeader(_response.size(), _path, _code, _type, requestConf.getContentLocation(), requestConf.getLang()) + "\r\n" + _response;
}

void			Response::headMethod(Request & request, RequestConfig & requestConf)
{
	ResponseHeader	head;
	(void)request;

	_code = readContent();
	_response = head.getHeader(_response.size(), _path, _code, _type, requestConf.getContentLocation(), requestConf.getLang());
}

void			Response::postMethod(Request & request, RequestConfig & requestConf)
{
	ResponseHeader	head;

	if (requestConf.getCgiPass() != "")
	{
		CgiHandler	cgi(request, requestConf);
		size_t		i = 0;
		size_t		j = _response.size() - 2;

		_response = cgi.executeCgi(requestConf.getCgiPass());

		while (_response.find("\r\n\r\n", i) != std::string::npos || _response.find("\r\n", i) == i)
		{
			std::string	str = _response.substr(i, _response.find("\r\n", i) - i);
			if (str.find("Status: ") == 0)
				_code = std::atoi(str.substr(8, 3).c_str());
			else if (str.find("Content-Type: ") == 0)
				_type = str.substr(14, str.size());
			i += str.size() + 2;
		}
		while (_response.find("\r\n", j) == j)
			j -= 2;

		_response = _response.substr(i, j - i);
	}
	else
	{
		_code = 204;
		_response = "";
	}
	_response = head.getHeader(_response.size(), _path, _code, _type, requestConf.getContentLocation(), requestConf.getLang()) + "\r\n" + _response;
}

void			Response::putMethod(Request & request, RequestConfig & requestConf)
{
	ResponseHeader	head;
	std::string		content;

	content = request.getBody();
	_response = "";
	_code = writeContent(content);
	if (_code != 201 && _code != 204)
		_response = this->readHtml(_errorMap[_code]);
	_response = head.getHeader(_response.size(), _path, _code, _type, requestConf.getContentLocation(), requestConf.getLang()) + "\r\n" + _response;
}

void			Response::deleteMethod(Request & request, RequestConfig & requestConf)
{
	ResponseHeader	head;
	(void)request;

	_response = "";
	if (pathIsFile(_path))
	{
		if (remove(_path.c_str()) == 0)
			_code = 204;
		else
			_code = 403;
	}
	else
		_code = 404;
	if (_code == 403 || _code == 404)
		_response = this->readHtml(_errorMap[_code]);
	_response = head.getHeader(_response.size(), _path, _code, _type, requestConf.getContentLocation(), requestConf.getLang()) + "\r\n" + _response;

		
}

void			Response::connectMethod(Request & request, RequestConfig & requestConf)
{
	// LINK TO OTHER SERVER ?
	(void)request;
	(void)requestConf;
}

void			Response::optionsMethod(Request & request, RequestConfig & requestConf)
{
	ResponseHeader	head;
	(void)request;

	_code = readContent();
	_response = head.getHeader(_response.size(), _path, _code, _type, requestConf.getContentLocation(), requestConf.getLang()) + "\r\n";

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

	if (pathIsFile(_path))
	{
		file.open(_path.c_str(), std::ifstream::in);
		if (file.is_open() == false)
		{
			_response = _errorMap[403];
			return (403);
		}

		buffer << file.rdbuf();
		_response = buffer.str();

		file.close();
	}
	else if (_isAutoIndex) {
		buffer << AutoIndexGenerator::getPage(_path.c_str(),\
			to_string(_hostPort.host), _hostPort.port);
		_response = buffer.str();
		_type = "text/html";
	}
	else
	{
		_response = this->readHtml(_errorMap[404]);
		return (404);
	}

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

std::string		Response::readHtml(const std::string& path)
{
	std::ofstream		file;
	std::stringstream	buffer;
	
	if (pathIsFile(path))
	{
		file.open(path.c_str(), std::ifstream::in);
		if (file.is_open() == false)
			return ("<!DOCTYPE html>\n<html><title>40404</title><body>There was an error finding your error page</body></html>\n");

		buffer << file.rdbuf();
		file.close();
		return (buffer.str());
	}
	else
		return ("<!DOCTYPE html>\n<html><title>40404</title><body>There was an error finding your error page</body></html>\n");
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

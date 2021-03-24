/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:18:58 by cclaude           #+#    #+#             */
/*   Updated: 2021/03/24 17:16:00 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

// Member functions

void			Response::call(Request & request, RequestConfig & requestConf)
{
	_code = request.getRet();
	_path = requestConf.getPath();
	_isAutoIndex = requestConf.getAutoIndex();
	_hostPort = requestConf.getHostPort();

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
		std::cerr << "Running cgi ...\n";
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
	else {
		if  (_code == 200)
		{
			_code = readContent();
		}
		else
		{
			_response = "";
		}
	}
	if (_response != "")
		_response = head.getHeader(_response.size(), _path, _code, requestConf.getContentLocation(), requestConf.getLang())
					+ "\r\n" + _response;
	else
		_response = head.getHeader(_response.size(), _path, _code, requestConf.getContentLocation(), requestConf.getLang()) + "\r\n";
}

void			Response::headMethod(RequestConfig & requestConf)
{
	ResponseHeader	head;

	_code = readContent();
	_response = head.getHeader(_response.size(), _path, _code, requestConf.getContentLocation(), requestConf.getLang());
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
	_response = head.getHeader(_response.size(), _path, _code, requestConf.getContentLocation(), requestConf.getLang()) + "\r\n" + _response;
}

void			Response::putMethod(std::string content, RequestConfig & requestConf)
{
	ResponseHeader	head;

	_code = writeContent(content);
	_response = head.getHeader(_response.size(), _path, _code, requestConf.getContentLocation(), requestConf.getLang()) + "\r\n";
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

	_response = head.getHeader(_response.size(), _path, _code, requestConf.getContentLocation(), requestConf.getLang()) + "\r\n";
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
	_response = head.getHeader(_response.size(), _path, _code, requestConf.getContentLocation(), requestConf.getLang()) + "\r\n";

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

	if (pathIsFile(_path)) {
		file.open(_path.c_str(), std::ifstream::in);
		if (file.is_open() == false)
			return (403);

		buffer << file.rdbuf();
		_response = buffer.str();

		file.close();
	}
	else if (this->_isAutoIndex) {
			AutoIndexGenerator	gen;

			buffer << gen.getPage(_path.c_str(), to_string(_hostPort.host), _hostPort.port);
			_response = buffer.str();
		}
	else
		return (404);


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

Response::Response(void):
_isAutoIndex(false)
{
}

Response::Response(const Response & src)
{
	*this = src;
}

Response::~Response(void)
{
}

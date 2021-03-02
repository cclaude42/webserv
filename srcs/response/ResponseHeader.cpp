/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseHeader.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 15:17:39 by cclaude           #+#    #+#             */
/*   Updated: 2021/03/02 14:28:45 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResponseHeader.hpp"

// Member functions

std::string		ResponseHeader::getHeader(const std::string& content, const std::string& path, int code, const std::string& contentLocation)
{
	std::string	header;

	resetValues();
	setValues(content, path, code, contentLocation);

	header = "HTTP/1.1 " + to_string(code) + " " + getStatusMessage(code) + "\r\n";
	header += writeHeader();

	return (header);
}

std::string		ResponseHeader::notAllowed(std::set<std::string> methods, const std::string& path)
{
	std::string	header;

	resetValues();
	setValues("", path, 405, path);
	setAllow(methods);

	header = "HTTP/1.1 405 Method Not Allowed\r\n";
	header += writeHeader();

	return (header);
}

std::string		ResponseHeader::writeHeader(void)
{
	std::string	header = "";

	if (_allow != "")
		header += "Allow: " + _allow + "\r\n";
	if (_contentLanguage != "")
		header += "Content-Language: " + _contentLanguage + "\r\n";
	if (_contentLength != "")
		header += "Content-Length: " + _contentLength + "\r\n";
	if (_contentLocation != "")
		header += "Content-Location: " + _contentLocation + "\r\n";
	if (_contentType != "")
		header += "Content-Type: " + _contentType + "\r\n";
	if (_date != "")
		header += "Date: " + _date + "\r\n";
	if (_lastModified != "")
		header += "Last-Modified: " + _lastModified + "\r\n";
	if (_location != "")
		header += "Location: " + _location + "\r\n";
	if (_retryAfter != "")
		header += "Retry-After: " + _retryAfter + "\r\n";
	if (_server != "")
		header += "Server: " + _server + "\r\n";
	if (_transferEncoding != "")
		header += "Transfer-Encoding: " + _transferEncoding + "\r\n";
	if (_wwwAuthenticate != "")
		header += "WWW-Authenticate: " + _wwwAuthenticate + "\r\n";
	// header += "\r\n";

	return (header);
}

std::string		ResponseHeader::getStatusMessage(int code)
{
	// if (code == 100)
	// 	return ("Continue");
	// else if (code == 200)
	// 	return ("OK");
	// else if (code == 201)
	// 	return ("Created");
	// else if (code == 204)
	// 	return ("No Content");
	// else if (code == 400)
	// 	return ("Bad Request");
	// else if (code == 403)
	// 	return ("Forbidden");
	// else if (code == 404)
	// 	return ("Not Found");
	// else if (code == 405)
	// 	return ("Method Not Allowed");
	// else
	// 	return ("Unknown Code");
	if (_errors.find(code) != _errors.end())
		return _errors[code];
	return ("Unknown Code");
}

void			ResponseHeader::initErrorMap()
{
	_errors[100] = "Continue";
	_errors[200] = "OK";
	_errors[201] = "Created";
	_errors[204] = "No Content";
	_errors[400] = "Bad Request";
	_errors[403] = "Forbidden";
	_errors[404] = "Not Found";
	_errors[405] = "Method Not Allowed";
}

void			ResponseHeader::setValues(const std::string& content, const std::string& path, int code, const std::string& contentLocation)
{
	setAllow();
	setContentLanguage(content);
	setContentLength(content.size());
	setContentLocation(contentLocation, code);
	setContentType(path);
	setDate();
	setLastModified(path);
	setLocation(code, path);
	setRetryAfter(code, 3);
	setServer();
	setTransferEncoding();
	setWwwAuthenticate(code);
}

void			ResponseHeader::resetValues(void)
{
	_allow = "";
	_contentLanguage = "";
	_contentLength = "";
	_contentLocation = "";
	_contentType = "";
	_date = "";
	_lastModified = "";
	_location = "";
	_retryAfter = "";
	_server = "";
	_transferEncoding = "";
	_wwwAuthenticate = "";
	initErrorMap();
}

// Setter functions

void			ResponseHeader::setAllow(std::set<std::string> methods)
{
	std::set<std::string>::iterator it = methods.begin();

	while (it != methods.end())
	{
		_allow += *(it++);

		if (it != methods.end())
			_allow += ", ";
	}
}

void			ResponseHeader::setAllow(void)
{
	_allow = "";
}

void			ResponseHeader::setContentLanguage(const std::string& content)
{
	(void)content;
	_contentLanguage = "en-US";
}

void			ResponseHeader::setContentLength(int size)
{
	_contentLength = to_string(size);
}

void			ResponseHeader::setContentLocation(const std::string& path, int code)
{
	(void)code;
	// if (code != 404)
		_contentLocation = path;
}

void			ResponseHeader::setContentType(std::string type)
{
	if (type == "")
		return ;
	type = type.substr(type.rfind(".") + 1, type.size() - type.rfind("."));
	if (type == "html")
		_contentType = "text/html";
	else if (type == "css")
		_contentType = "text/css";
	else if (type == "js")
		_contentType = "text/javascript";
	else if (type == "jpeg" || type == "jpg")
		_contentType = "image/jpeg";
	else if (type == "png")
		_contentType = "image/png";
	else if (type == "bmp")
		_contentType = "image/bmp";
	else
		_contentType = "text/plain";
}

void			ResponseHeader::setDate(void)
{
	char			buffer[100];
	struct timeval	tv;
	struct tm		*tm;

	gettimeofday(&tv, NULL);
	tm = gmtime(&tv.tv_sec);
	strftime(buffer, 100, "%a, %d %b %Y %H:%M:%S GMT", tm);
	_date = std::string(buffer);
}

void			ResponseHeader::setLastModified(const std::string& path)
{
	char			buffer[100];
	struct stat		stats;
	struct tm		*tm;

	if (stat(path.c_str(), &stats) == 0)
	{
		tm = gmtime(&stats.st_mtime);
		strftime(buffer, 100, "%a, %d %b %Y %H:%M:%S GMT", tm);
		_lastModified = std::string(buffer);
	}
}

void			ResponseHeader::setLocation(int code, const std::string& redirect)
{
	if (code == 201 || code / 100 == 3)
	{
		_location = redirect;
	}
}

void			ResponseHeader::setRetryAfter(int code, int sec)
{
	if (code == 503 || code == 429 || code == 301)
	{
		_retryAfter = to_string(sec);
	}
}

void			ResponseHeader::setServer(void)
{
	_server = "Weebserv/1.0.0 (Unix)";
}

void			ResponseHeader::setTransferEncoding(void)
{
	_transferEncoding = "identity";
}

void			ResponseHeader::setWwwAuthenticate(int code)
{
	if (code == 401)
	{
		_wwwAuthenticate = "Basic realm=\"Access requires authentification\" charset=\"UTF-8\"";
	}
}

// Overloaders

ResponseHeader & ResponseHeader::operator=(const ResponseHeader & src)
{
	(void)src;
	return (*this);
}

// Constructors and destructors

ResponseHeader::ResponseHeader(void)
{
	resetValues();
}

ResponseHeader::ResponseHeader(const ResponseHeader & src)
{
	(void)src;
}

ResponseHeader::~ResponseHeader(void)
{
}

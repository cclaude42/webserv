/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseHeader.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 15:17:39 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/17 16:18:11 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResponseHeader.hpp"

// Member functions

std::string		ResponseHeader::getHeader(std::string content, std::string filename, int code)
{
	std::string	header;

	setValues(content, filename, code);

	header = "HTTP/1.1 " + std::to_string(code) + " " + getStatusMessage(code) + "\r\n";
	header += writeHeader();

	resetValues();

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
	header += "\r\n";

	// std::cout << "[" << header << "]" << std::endl;

	return (header);
}

std::string		ResponseHeader::getStatusMessage(int code)
{
	if (code == 200)
		return ("OK");
	else
		return ("Unkown code");
}

void			ResponseHeader::setValues(std::string content, std::string filename, int code)
{
	(void)code;
	if (code == 405)
		setAllow("GET, HEAD, POST");
	setContentLanguage(content);
	setContentLength(content.size());
	setContentLocation(filename);
	setContentType(filename);
	setDate();
	setLastModified(filename);
	setLocation(code, "NONE");
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
}

// Setter functions

void			ResponseHeader::setAllow(std::string cmd)
{
	_allow = cmd;
}

void			ResponseHeader::setContentLanguage(std::string content)
{
//	_contenLanguage = findLanguage(content); // Parse file in search for
	_contentLangugage = "en-US";			// <html lang="fr"> 
}

void			ResponseHeader::setContentLength(int size)
{
	_contentLength = std::to_string(size);
}

void			ResponseHeader::setContentLocation(std::string path)
{
	_contentLocation = path;
}

void			ResponseHeader::setContentType(std::string type)
{
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

void			ResponseHeader::setLastModified(std::string path)
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

void			ResponseHeader::setLocation(int code, std::string redirect)
{
	if (code == 201 || code / 100 == 3)
	{
		_location = "/" + redirect;
	}
}

void			ResponseHeader::setRetryAfter(int code, int sec)
{
	if (code == 503 || code == 429 || code == 301)
	{
		_retryAfter = std::to_string(sec);
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

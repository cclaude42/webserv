/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseHeader.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 15:17:39 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/04 16:27:44 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResponseHeader.hpp"

// Member functions

std::string		ResponseHeader::getHeader(void)
{
	std::string	header = "";

	header += "HTTP/1.1 " + std::to_string(200) + " " + "OK" + "\r\n";
	header += "Allow: " + _allow + "\r\n";
	header += "Content-Language: " + _contentLanguage + "\r\n";
	header += "Content-Length: " + _contentLength + "\r\n";
	header += "Content-Location: " + _contentLocation + "\r\n";
	header += "Content-Type: " + _contentType + "\r\n";
	header += "Date: " + _date + "\r\n";
	header += "Last-Modified: " + _lastModified + "\r\n";
	header += "Location: " + _location + "\r\n";
	header += "Retry-After: " + _retryAfter + "\r\n";
	header += "Server: " + _server + "\r\n";
	header += "Trasnfer-Encoding: " + _transferEncoding + "\r\n";
	header += "WWW-Authenticate: " + _wwwAuthenticate + "\r\n";
	header += "\r\n";

	return (header);
}

// Setter functions

void			ResponseHeader::setAllow(std::string str)
{
	_allow = str;
}

void			ResponseHeader::setContentLanguage(std::string str)
{
	_contentLanguage = str;
}

void			ResponseHeader::setContentLength(std::string str)
{
	_contentLength = str;
}

void			ResponseHeader::setContentLocation(std::string str)
{
	_contentLocation = str;
}

void			ResponseHeader::setContentType(std::string str)
{
	_contentType = str;
}

void			ResponseHeader::setDate(std::string str)
{
	_date = str;
}

void			ResponseHeader::setLastModified(std::string str)
{
	_lastModified = str;
}

void			ResponseHeader::setLocation(std::string str)
{
	_location = str;
}

void			ResponseHeader::setRetryAfter(std::string str)
{
	_retryAfter = str;
}

void			ResponseHeader::setServer(std::string str)
{
	_server = str;
}

void			ResponseHeader::setTransferEncoding(std::string str)
{
	_transferEncoding = str;
}

void			ResponseHeader::setWwwAuthenticate(std::string str)
{
	_wwwAuthenticate = str;
}

// Getter functions

std::string		ResponseHeader::getAllow(void)
{
	return (_allow);
}

std::string		ResponseHeader::getContentLanguage(void)
{
	return (_contentLanguage);
}

std::string		ResponseHeader::getContentLength(void)
{
	return (_contentLength);
}

std::string		ResponseHeader::getContentLocation(void)
{
	return (_contentLocation);
}

std::string		ResponseHeader::getContentType(void)
{
	return (_contentType);
}

std::string		ResponseHeader::getDate(void)
{
	return (_date);
}

std::string		ResponseHeader::getLastModified(void)
{
	return (_lastModified);
}

std::string		ResponseHeader::getLocation(void)
{
	return (_location);
}

std::string		ResponseHeader::getRetryAfter(void)
{
	return (_retryAfter);
}

std::string		ResponseHeader::getServer(void)
{
	return (_server);
}

std::string		ResponseHeader::getTransferEncoding(void)
{
	return (_transferEncoding);
}

std::string		ResponseHeader::getWwwAuthenticate(void)
{
	return (_wwwAuthenticate);
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
	_allow = "xxx";
	_contentLanguage = "xxx";
	_contentLength = "xxx";
	_contentLocation = "xxx";
	_contentType = "xxx";
	_date = "xxx";
	_lastModified = "xxx";
	_location = "xxx";
	_retryAfter = "xxx";
	_server = "xxx";
	_transferEncoding = "xxx";
	_wwwAuthenticate = "xxx";
}

ResponseHeader::ResponseHeader(const ResponseHeader & src)
{
	(void)src;
}

ResponseHeader::~ResponseHeader(void)
{
}

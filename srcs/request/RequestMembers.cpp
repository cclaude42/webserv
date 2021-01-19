/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestMembers.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:10:06 by hbaudet           #+#    #+#             */
/*   Updated: 2021/01/19 15:17:13 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

void	Request::displayHeaders() const
{
	std::cout << *this;
}

std::ostream&	operator<<(std::ostream& os, const Request& re)
{
	std::map<std::string, std::string>::const_iterator	it;

	os << "Method : " << re.getMethod() << " |\tHTTP version : ";
	os << re.getVersion() << '\n';
	os << "Port : " << re.getPort() << '\n';
	os << "Path : " << re.getPath() << '\n';

	for (it = re.getHeaders().begin(); it != re.getHeaders().end(); it++)
		os << it->first << ": " << it->second << '\n';

	os << '\n' << "Request body :\n" << re.getBody() << '\n';

	return os;
}

void	Request::resetHeaders()
{
	this->_headers = {
	{"Accept-Charsets", ""},
	{"Accept-Language", ""},
	{"Allow", ""},
	{"Authorization", ""},
	{"Aontent-Language", ""},
	{"Content-Length", ""},
	{"Content-Location", ""},
	{"Content-Type", ""},
	{"Date", ""},
	{"Host", ""},
	{"Last-Modified", ""},
	{"Location", ""},
	{"Referer", ""},
	{"Retry-After", ""},
	{"Server", ""},
	{"Transfer-Encoding", ""},
	{"User-Agent", ""},
	{"Www-Authenticate", ""},
	};
}

int		Request::readFirstLine(std::string& line)
{
	size_t	i = line.find_first_of(' ');

	if (i == std::string::npos)
	{
		this->_ret = 400;
		std::cout << "RFL no space after method" << '\n';
		return 400;
	}
	this->_method.assign(line, 0, i);
	return this->readPath(line, i);
}

int		Request::readPath(std::string& line, size_t i)
{
	size_t	j;

	if ((j = line.find_first_not_of(' ', i)) == std::string::npos)
	{
		this->_ret = 400;
		std::cout << "No PATH / HTTP version\n";
		return 400;
	}
	if ((i = line.find_first_of(' ', j)) == std::string::npos)
	{
		this->_ret = 400;
		std::cout << "No HTTP version\n";
	}
	this->_path.assign(line, j, i - j);
	return this->readVersion(line, i);
}

int		Request::readVersion(std::string& line, size_t i)
{
	if ((i = line.find_first_not_of(' ', i)) == std::string::npos)
	{
		this->_ret = 400;
		std::cout << "No HTTP version\n";
	}
	if (line[i] == 'H' && line[i + 1] == 'T' && line[i + 2] == 'T' &&
			line[i + 3] == 'P' && line[i + 4] == '/')
		this->_version.assign(line, i + 5, 3);
	if (this->_version != "1.0" && this->_version != "1.1")
	{
		this->_ret = 400;
		std::cout << "BAD HTTP VERSION (" << this->_version << ")\n";
		return (this->_ret);
	}
	return (this->checkMethod());
}

int		Request::checkMethod()
{
	for (size_t i = 0; i < this->methods.size(); i++)
		if (this->methods[i] == this->_method)
			return this->_ret;
	std::cout << "Invalid method requested\n";
	this->_ret = 400;
	return this->_ret;
}

int		Request::checkPort()
{
	size_t i = this->_headers["Host"].find_first_of(':');

	if (i == std::string::npos)
		this->_port = 80;
	else
	{
		std::string tmp(this->_headers["Host"], i + 1);
		this->_port = stoi(tmp);
	}
	return (this->_port);
}

int		Request::parse(const std::string& str)
{
	std::string		key;
	std::string		value;
	std::vector<std::string> line = split(str, '\n');
	size_t			i;

	// std::cout << "Request:\n" << str << "===================\n";

	this->_raw = str;
	if (line.size() < 2)
		this->_ret = 400;
	else
	{
		this->readFirstLine(line[0]);
		for (i = 1; i < line.size() && this->_ret != 400; i++)
		{
			key = readKey(line[i]);
			value = readValue(line[i]);
			if (line[i][0] == '\r')
				break;
			if (line[i].back() == '\r')
				line[i].pop_back();
			if (this->_headers.count(key))
				this->_headers[key] = strip(value, ' ');
		}
		if (i < line.size())
			this->setBody(line, i);
		this->checkPort();
	}
	this->stripAll();
	this->_querry = findQuerry(this->_path);
	return (this->_ret);
}

void	Request::stripAll()
{
	strip(this->_method, '\n');
	strip(this->_method, '\r');
	strip(this->_method, ' ');
	strip(this->_version, '\n');
	strip(this->_version, '\r');
	strip(this->_version, ' ');
	strip(this->_path, '\n');
	strip(this->_path, '\r');
	strip(this->_path, ' ');
}

std::string	Request::findQuerry(std::string path)
{
	size_t		i;
	std::string	ret;

	i = path.find_first_of('?');
	if (i != std::string::npos)
		ret.assign(path, i, std::string::npos);

	return ret;
}

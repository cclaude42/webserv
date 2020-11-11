/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestMembers.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:10:06 by hbaudet           #+#    #+#             */
/*   Updated: 2020/11/11 18:50:31 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

void	Request::displayHeaders()
{
	std::cout << *this;
}

std::ostream&	operator<<(std::ostream& os, const Request& re)
{
	std::map<std::string, std::string>::const_iterator	it;

	os << "Method : " << re.getMethod() << " |\tHTTP version : ";
	os << re.getVersion() << '\n';

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
	{"Derver", ""},
	{"Transfer-Encoding", ""},
	{"User-Agent", ""},
	{"Www-Authenticate", ""},
	};
}

void	Request::readFirstLine(char *line)
{
	size_t	i;

	for (i = 0; line[i] && line[i] != ' '; i++)
		this->_method.push_back(line[i]);
	while (line[++i] == ' ');
	if (line[i] == '/')
		i++;
	while (line[++i] == ' ');
	if (line[i] == 'H' && line[i + 1] == 'T' && line[i + 2] == 'T' &&
		line[i + 3] == 'P' && line[i + 4] == '/')
		this->_version.append(line, i + 5, 3);
	if (this->_version != "1.0" && this->_version != "1.1")
		this->_ret = 400;
	this->checkMethod();
}

void	Request::readFirstLine(std::string& line)
{
	size_t	i = line.find_first_of(' ');

	if (i == std::string::npos)
	{
		this->_ret = 400;
		std::cout << "RFL no space after method" << '\n';
	}
	else
	{
		this->_method.append(line, 0, i);
		if ((i = line.find_first_not_of(" /", i)) == std::string::npos)
			this->_ret = 400;
		else
		{
			if (line[i] == 'H' && line[i + 1] == 'T' && line[i + 2] == 'T' &&
					line[i + 3] == 'P' && line[i + 4] == '/')
				this->_version.append(line, i + 5, 3);
			if (this->_version != "1.0" && this->_version != "1.1")
			{
				this->_ret = 400;
				std::cout << "BAD HTTP VERSIONi (" << this->_version << ")\n";
			}
			strip(this->_method, ' ');
			this->checkMethod();
		}
	}
}

void	Request::checkMethod()
{
	for (size_t i = 0; i < this->methods.size(); i++)
		if (this->methods[i] == this->_method)
			return;
	std::cout << "Invalid method requested\n";
	this->_ret = 400;
}

void	Request::checkPort()
{
	size_t i = this->_headers["Host"].find_first_of(':');

	if (i == std::string::npos)
		return;
	std::string tmp(this->_headers["Host"], i + 1);
	this->_port = stoi(tmp);
	this->_headers["Host"].erase(i);
}

int		Request::parse(const char *str)
{
	char 			**line = ft_split(str, '\n');
	std::string		key;
	std::string		value;
	int				i;

	if (!line || !line[0] || !line[1])
		this->_ret = 400;
	else
	{
		this->readFirstLine(line[0]);
		for (i = 1; line[i] && this->_ret != 400; i++)
		{
			key = readKey(line[i]);
			value = readValue(line[i]);
			if (line[i][0] == '\r')
				break;
			if (line[i][ft_strlen(line[i]) - 1] == '\r')
				line[i][ft_strlen(line[i]) - 1] = '\0';
			if (this->_headers.count(key))
				this->_headers[key] = strip(value, ' ');
		}
		this->checkPort();
		if (line[i])
			this->setBody(line, i);
		for (int i = 0; line[i]; i++)
			free(line[i]);
	}
	free(line);

	return (this->_ret);
}

int		Request::parse(const std::string& str)
{
	std::string		key;
	std::string		value;
	std::vector<std::string> line = split(str, '\n');
	size_t			i;


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

	return (this->_ret);
}

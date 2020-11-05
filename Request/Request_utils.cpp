/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request_utils.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:10:06 by hbaudet           #+#    #+#             */
/*   Updated: 2020/11/05 16:36:16 by hbaudet          ###   ########.fr       */
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

	return os;
}

void	Request::resetHeaders()
{
	this->headers = {
	{"Accept-Charsets", ""},
	{"Accept-Language", ""},
	{"Allow", ""},
	{"Authorization", ""},
	{"Content-Language", ""},
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
	{"WWW-Authenticate", ""},
	};
}

void	Request::readFirstLine(char *line)
{
	size_t	i;

	for (i = 0; line[i] && line[i] != ' '; i++)
		this->method.push_back(line[i]);
	while (line[++i] == ' ');
	if (line[i] == '/')
		i++;
	while (line[++i] == ' ');
	if (ft_strlen(line) < i + 13)
	{
		this->ret = 400;
		return;
	}
	if (line[i] == 'H' && line[i + 1] == 'T' && line[i + 2] == 'T' &&
		line[i + 3] == 'P' && line[i + 4] == '/')
		this->version.append(line, i + 5, 3);
}

static std::string	readKey(char *line)
{
	std::string	ret;

	for (int i = 0; line[i] && line[i] != ':'; i++)
		ret.push_back(line[i]);
	return (ret);
}

static std::string	readValue(char *line)
{
	int i;
	std::string	ret;

	for (i = 0; line[i] && line[i] != ':'; i++);
	while (line[++i] && line[i] == ' ');
	i--;
	while (line[++i])
		ret.push_back(line[i]);
	return ret;
}

int		Request::parse(const char *str)
{
	char 			**line = ft_split(str, '\n');
	std::string		key;
	std::string		value;;

	if (!line || !line[0] || !line[1])
		this->ret = 400;
	else
	{
	this->readFirstLine(line[0]);
	for (int i = 1; line[i]; i++)
	{
		key = readKey(line[i]);
		value = readValue(line[i]);
		if (line[i][0] == '\r')
			break;
		if (line[i][ft_strlen(line[i]) - 1] == '\r')
			line[i][ft_strlen(line[i]) - 1] = '\0'; //	useless ?
		if (this->headers.count(key))
			this->headers[key] = value;
	}
	for (int i = 0; line[i]; i++)
		free(line[i]);
	}
	free(line);

	return (this->ret);
}

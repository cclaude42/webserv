/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request_utils.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:10:06 by hbaudet           #+#    #+#             */
/*   Updated: 2020/11/03 19:11:49 by hbaudet          ###   ########.fr       */
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

int		Request::parse(const char *str)
{
	char **line = ft_split(str, '\n');
	char test[] = "test yo\n";

	ft_putstr_fd(test, 1);
	if (!line || !line[0] || !line[1])
		this->ret = 400;
	return (this->ret);
}

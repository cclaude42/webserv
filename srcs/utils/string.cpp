/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:58:08 by cclaude           #+#    #+#             */
/*   Updated: 2021/03/22 10:52:47 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int								countSubstr(std::string & str, std::string sub)
{
	int						n = 0;
	std::string::size_type	pos = 0;

	while ((pos = str.find(sub, pos)) != std::string::npos)
	{
		n++;
		pos += sub.length();
	}

	return (n);
}

int								checkStart(std::string & str, std::string end)
{
	size_t	i = 0;
	size_t	j = 0;

	while (j < end.size())
	{
		if (i >= str.size() || str[i] != end[j])
			return (1);
		i++;
		j++;
	}
	return (0);
}

int								checkEnd(std::string & str, std::string end)
{
	size_t	i = str.size();
	size_t	j = end.size();

	while (j > 0)
	{
		i--;
		j--;
		if (i < 0 || str[i] != end[j])
			return (1);
	}
	return (0);
}

std::string						readKey(char *line)
{
	std::string	ret;

	for (int i = 0; line[i] && line[i] != ':'; i++)
		ret.push_back(line[i]);
	capitalize(ret);
	return (ret);
}

std::string						readKey(std::string& line)
{
	std::string	ret;

	size_t	i = line.find_first_of(':');
	ret.append(line, 0 , i);
	capitalize(ret);
	return (ret);
}

std::string						readValue(char *line)
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

std::string						readValue(std::string& line)
{
	size_t i;
	std::string	ret;

	i = line.find_first_of(':');
	i = line.find_first_not_of(' ', i + 1);
	if (i != std::string::npos)
		ret.append(line, i, std::string::npos);
	return ret;
}

std::vector<std::string>		split(const std::string& str, char c)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(str);

	while (std::getline(tokenStream, token, c))
		tokens.push_back(token);
	return tokens;
}

std::string&					strip(std::string& str, char c)
{
	while (str[str.size()] == c)
		str = str.substr(0, str.size());
	return str;
}

std::string&					to_upper(std::string& str)
{
	std::transform(str.begin(), str.end(),str.begin(), ::toupper);
	return str;
}

std::string&					to_lower(std::string& str)
{
	std::transform(str.begin(), str.end(),str.begin(), ::tolower);
	return str;
}

std::string&					pop(std::string& str)
{
	if (str.size())
		str.resize(str.size() - 1);
	return str;
}

std::string&					capitalize(std::string& str)
{
	size_t	i = 0;

	to_lower(str);
	str[i] = std::toupper(str[i]);
	while((i = str.find_first_of('-', i + 1)) != std::string::npos)
	{
		if (i + 1 < str.size())
		str[i + 1] = std::toupper(str[i + 1]);
	}
	return str;
}

std::string	to_string(size_t n)
{
	std::stringstream tmp;

	tmp << n;

	return tmp.str();
}

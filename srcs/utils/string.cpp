/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:58:08 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/09 16:24:59 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

std::string					readKey(char *line)
{
	std::string	ret;

	for (int i = 0; line[i] && line[i] != ':'; i++)
		ret.push_back(line[i]);
	return (ret);
}

std::string					readKey(std::string& line)
{
	std::string	ret;

	size_t	i = line.find_first_of(':');
		ret.append(line, 0 , i);
	return (ret);
}

std::string					readValue(char *line)
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

std::string					readValue(std::string& line)
{
	size_t i;
	std::string	ret;

	i = line.find_first_of(':');
	i = line.find_first_not_of(' ', i);
	ret.append(line, i, std::string::npos);
	return ret;
}

std::vector<std::string>	split(const std::string& str, char c)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(str);
	
	while (std::getline(tokenStream, token, c))
		tokens.push_back(token);
	return tokens;
}

std::string					strip(std::string& str, char c)
{
	while (str.back() == c)
		str.pop_back();
	return str;
}

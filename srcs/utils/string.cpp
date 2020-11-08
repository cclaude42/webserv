/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:58:08 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/08 14:10:22 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

std::string	readKey(char *line)
{
	std::string	ret;

	for (int i = 0; line[i] && line[i] != ':'; i++)
		ret.push_back(line[i]);
	return (ret);
}

std::string	readValue(char *line)
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

std::string	strip(std::string& str, char c)
{
	while (str.back() == c)
		str.pop_back();
	return str;
}

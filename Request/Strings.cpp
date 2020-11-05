/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Strings.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 17:36:55 by hbaudet           #+#    #+#             */
/*   Updated: 2020/11/05 17:43:40 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Strings.hpp"

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


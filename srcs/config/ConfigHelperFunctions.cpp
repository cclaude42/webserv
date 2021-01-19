/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigHelperFunctions.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 14:28:07 by user42            #+#    #+#             */
/*   Updated: 2021/01/19 15:28:39 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigHelperFunctions.hpp"

// HELPFUL FUNCTIONS
bool isDigits(const std::string &str) {
	return str.find_first_not_of("0123456789") == std::string::npos;
}

unsigned int	strToIp(std::string strIp) {
	size_t  sep;
	unsigned int   n;
	unsigned char  m[4];
	size_t  start = 0;
	if (strIp == "localhost")
		strIp = "127.0.0.1";
	for (unsigned int i = 3 ; i != std::numeric_limits<uint32_t>::max(); i--) {
		sep = strIp.find_first_of(".", sep);
		std::string str = strIp.substr(start, sep);
		n = ft_atoi(str.c_str());
		m[i] = static_cast<unsigned char>(n);
		sep++;
		start = sep;
	}
	unsigned final = *(reinterpret_cast<unsigned int *>(m));
	return final;
}

std::string	removeAdjacentSlashes(std::string &str) {
	std::string	ret;
	bool		lastIsSlash = false;

	for (std::string::size_type i = 0; i < str.length(); i++) {
		if (str[i] == '/') {
			if (!lastIsSlash)
				ret.push_back(str[i]);
			lastIsSlash = true;
		}
		else {
			lastIsSlash = false;
			ret.push_back(str[i]);	
		}
	}
	return ret;
}
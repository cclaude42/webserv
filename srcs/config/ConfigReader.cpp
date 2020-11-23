/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigReader.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:34:43 by user42            #+#    #+#             */
/*   Updated: 2020/11/14 14:51:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigReader.hpp"

ConfigReader::ConfigReader(void) {
	return ;
}

ConfigReader::ConfigReader(ConfigReader const &src) {
	if (this != &src)
		*this = src;
	return ;
}

ConfigReader::~ConfigReader(void) {
	return ;
}

ConfigReader	&ConfigReader::operator=(ConfigReader const &src) {
	if (this != &src)
		*this = src;
	return *this;
}

fileVector				ConfigReader::split(std::string str, std::string charset) {
	fileVector	tokens;

	str += charset[0]; // in order to count the last char, I know it's not pretty but I spent way too much time on this
	std::string::size_type	start = str.find_first_not_of(charset, 0);
	std::string::size_type	end = 0;
	while (true) {
		end = str.find_first_of(charset, start);
		if (end == std::string::npos) {
			break;
		}
		std::string	s = str.substr(start, end - start);
		tokens.push_back(s);
		if ((start = str.find_first_not_of(charset, end)) == std::string::npos)
			break ;
	}
	return tokens;
}

fileVector	ConfigReader::readFile(const char *filename) {
	int							ret = READER_BUFFER_SIZE;
	char						buffer[READER_BUFFER_SIZE + 1];
	std::string					line = "";
	int							fd;
	fileVector					file;

	for (int i = 0; i < READER_BUFFER_SIZE + 1;  i++)
		buffer[i] = '\0';
	if ((fd = open(filename, O_RDONLY)) <= 0)
		return file;

	for (ret = READER_BUFFER_SIZE; ret > 0;\
	ret = read(fd, buffer,READER_BUFFER_SIZE )) {
		buffer[ret] = '\0';
		line += buffer;
	}

	//	Get the last line, which is ignored otherwise
	if (ret == -1) {
		std::cerr << "error reading file" << std::endl;
		return file;
	}
	file = ConfigReader::split(line, std::string(" \n\t"));
 	return file;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:30:01 by user42            #+#    #+#             */
/*   Updated: 2020/11/05 17:57:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

 parseMap Config::parsingMap = init_map();

Config::Config(void) {
	return ;
}

Config::Config(Config const &src) {
	if (this != &src)
		*this = src;
	return ;
}

Config::~Config(void) {
	return ;
}

Config	&Config::operator=(Config const &src) {
	if (this != &src)
		*this = src;
	return (*this);
}

int     Config::parse(char * const filename) {
	ConfigReader               fileReader(filename);
	fileVector				   file;
	unsigned int               fileSize;

	fileReader.readFile();
	fileReader.getFile();
	fileReader.getFileOneLine(file);
	fileSize = file.size();
	for (unsigned int i = 0 ; i < fileSize; i++) {
		if (file[i] == "server") {
			ConfigServer  server;

			++i;
			if (file[i] != "{")
				std::cerr << "Error: expecter '{' after server directive" << std::endl;
			++i;
			if (!server.parse(i, file))
				std::cerr << "Error: error in config file " << filename << std::endl;
			else
				this->_servers.push_back(server);
		}
		else {
			std::cerr << "Error: unknown directive " << file[i] << std::endl;
			return 0;
		}
	}
	return 0;
}

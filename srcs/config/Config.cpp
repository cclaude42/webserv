/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:30:01 by user42            #+#    #+#             */
/*   Updated: 2020/11/07 17:05:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

parseMap Config::init_map() {
		    parseMap     myMap;
		    myMap["listen"] = &ConfigServer::addListen;
		    myMap["root"] = &ConfigServer::addRoot;
		    myMap["server_name"] = &ConfigServer::addServerName;
		    myMap["error_page"] = &ConfigServer::addErrorPage;
		    myMap["client_body_buffer_size"] = &ConfigServer::addClientBodyBufferSize;
		    return myMap;
}

 parseMap Config::parsingMap = Config::init_map();

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
	fileVector				   file;
	unsigned int               fileSize;

	file = ConfigReader::readFile(filename);
	fileSize = file.size();
	std::cout << "in Config::Parse " << file[0] << std::endl;
	for (unsigned int i = 0 ; i < fileSize; i++) {
		if (file[i] == "server") {
			std::cout << "AA" << std::endl;
			ConfigServer  server;
			++i;
			if (file[i] != "{")
				std::cerr << "Error: expecter '{' after server directive" << std::endl;
			++i;
			if (!server.parse(i, file))
				std::cerr << "Error: error in config file " << filename << std::endl;
			else {
				std::cout << server << std::endl;
				this->_servers.push_back(server);
			}
		}
		else {
			std::cerr << "Error: unknown directive " << file[i] << std::endl;
			return 0;
		}
	}
	return 0;
}

std::ostream	&operator<<(std::ostream &out, const Config &config) {
	for (size_t index = 0; index < config._servers.size(); index++) {
		out << "server " << index << std::endl;
		out << config._servers[0] << std::endl << std::endl;
	}
	return out;
}
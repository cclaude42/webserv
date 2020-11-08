/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:30:01 by user42            #+#    #+#             */
/*   Updated: 2020/11/08 02:00:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

parseMap Config::initServerMap() {
		    parseMap     myMap;
		    myMap["listen"] = &ConfigServer::addListen;
		    myMap["root"] = &ConfigServer::addRoot;
		    myMap["server_name"] = &ConfigServer::addServerName;
		    myMap["error_page"] = &ConfigServer::addErrorPage;
		    myMap["client_body_buffer_size"] = &ConfigServer::addClientBodyBufferSize;
			myMap["cgi_param"] = &ConfigServer::addCgiParam;
		    return myMap;
}

 parseMap Config::serverParsingMap = Config::initServerMap();

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
	for (unsigned int i = 0 ; i < fileSize; i++) {
		if (file[i] == "server") {
			ConfigServer  server;
			++i;
			if (file[i] != "{")
				std::cerr << "Error: expecter '{' after server directive" << std::endl;
			++i;
			if (!server.parse(i, file))
				std::cerr << "Error: error in config file " << filename << std::endl;
			else {
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
		out << "SERVER " << index << std::endl;
		out << config._servers[index] << std::endl;
	}
	return out;
}
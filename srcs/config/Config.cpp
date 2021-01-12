/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:30:01 by user42            #+#    #+#             */
/*   Updated: 2021/01/12 13:23:51 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config::Config(void) {
	return ;
}

Config::Config(Config const &src) {
	if (this != &src)
		this->_servers = src._servers;
	return ;
}

Config::~Config(void) {
	return ;
}

Config	&Config::operator=(Config const &src) {
	if (this != &src)
		this->_servers = src._servers;
	return (*this);
}

std::vector<ConfigServer>		Config::getServers() const {
	return this->_servers;
}
	
int     Config::parse(const char *filename) {
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
			if (!server.parseServer(i, file)) {
				std::cerr << "Error: error in config file \"" << filename << "\"" <<  std::endl;
				return 0;			
			}
			this->_servers.push_back(server);
		}
		else {
			std::cerr << "Error: unknown directive " << file[i] << std::endl;
			return 0;
		}
	}
	return 0;
}

RequestConfig	Config::getConfigForRequest(t_listen const address,\
					std::string const uri, std::string const hostName) const {
	ConfigServer	server;
	std::string		locationPath;

	this->getServerForRequest(server, address, hostName);
	server = server.getLocationForRequest(uri, locationPath);
	
	RequestConfig config(server, uri, locationPath);
	return config;
}

bool		Config::getServerForRequest(ConfigServer &ret, t_listen const address, std::string const hostName) const {
	std::vector<ConfigServer>	possibleServers;

	for (std::vector<const ConfigServer>::iterator serversIter = this->_servers.begin() ; serversIter != this->_servers.end(); serversIter++) {
		std::vector<t_listen>	listens = serversIter->getListen();
		for (std::vector<t_listen>::iterator listenIter = listens.begin(); listenIter != listens.end(); listenIter++) {
			if (address.host == (*listenIter).host && address.port == (*listenIter).port) {
				possibleServers.push_back((*serversIter));
			}
		}
	}
	if (possibleServers.empty())
		return false;
	for (std::vector<ConfigServer>::iterator serversIter = possibleServers.begin() ; serversIter != possibleServers.end(); serversIter++) {
		std::vector<std::string>	serverNames = serversIter->getServerName();
		for (fileVector::iterator servNameIter = serverNames.begin() ; servNameIter != serverNames.end(); servNameIter++) {
			if (*servNameIter == hostName) {
				ret = *serversIter;
				return true;
			}
		}
	}
	ret = possibleServers[0];
	return true;
}

std::ostream	&operator<<(std::ostream &out, const Config &config) {
	for (size_t index = 0; index < config._servers.size(); index++) {
		out << "SERVER " << index << std::endl;
		out << config._servers[index] << std::endl;
	}
	return out;
}

std::vector<t_listen>				Config::getAllListens() const {
	std::vector<t_listen>	ret;
	
	for (std::vector<const ConfigServer>::iterator server = this->_servers.begin(); server != this->_servers.end(); server++) {
		std::vector<t_listen>	listenVec = server->getListen();
		for (std::vector<t_listen>::iterator listen = listenVec.begin(); listen != listenVec.end(); listen++) {
			std::vector<t_listen>::iterator i = ret.begin();
			for ( ; i != ret.end(); i++)
				if (listen->host == i->host && listen->port == i->port)
					break ;
			if (i == ret.end())
				ret.push_back(*listen);
		}
	}
	return ret;
}

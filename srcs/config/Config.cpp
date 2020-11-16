/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franciszer <franciszer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:30:01 by user42            #+#    #+#             */
/*   Updated: 2020/11/16 21:57:11 by franciszer       ###   ########.fr       */
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
			if (!server.parse(i, file)) {
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
	
	std::cout << "location: " << locationPath << "|" << std::endl;
	RequestConfig config(server, uri, locationPath);
	return config;
}

bool		Config::getServerForRequest(ConfigServer &ret, t_listen const address, std::string const hostName) const {
	std::vector<ConfigServer>	possibleServers;

	for (auto serversIter = this->_servers.begin() ; serversIter != this->_servers.end(); serversIter++) {
		std::vector<t_listen>	listens = serversIter->getListen();
		for (auto listenIter = listens.begin(); listenIter != listens.end(); listenIter++) {
			if (address.host == (*listenIter).host && address.port == (*listenIter).port) {
				possibleServers.push_back((*serversIter));
			}
		}
	}
	if (possibleServers.empty())
		return false;
	for (auto serversIter = possibleServers.begin() ; serversIter != possibleServers.end(); serversIter++) {
		std::vector<std::string>	serverNames = serversIter->getServerName();
		for (auto servNameIter = serverNames.begin() ; servNameIter != serverNames.end(); servNameIter++) {
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
	for (unsigned int i = 3 ; i != UINT32_MAX; i--) {
		sep = strIp.find_first_of(".", sep);
		std::string str = strIp.substr(start, sep);
		n = std::stoi(str);
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
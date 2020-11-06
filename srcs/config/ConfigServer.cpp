/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 15:28:08 by user42            #+#    #+#             */
/*   Updated: 2020/11/06 16:11:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigServer.hpp"

bool isDigits(const std::string &str) {
	return str.find_first_not_of("0123456789") == std::string::npos;
}

ConfigServer::ConfigServer(void):
_client_body_buffer_size(8000)
{
	return ;
}

ConfigServer::ConfigServer(ConfigServer const &src) {
	if (this != &src)
		*this = src;
	return ;
}

ConfigServer::~ConfigServer(void) {
	return ;
}

ConfigServer	&ConfigServer::operator=(ConfigServer const &src) {
	if (this != &src)
		*this = src;
	return *this;
}

int     ConfigServer::parse(unsigned int &index, fileVector &file) {
	fileVector                  args;
	parseMap::iterator          iter;
	std::string                 directive = "";

	//	calling the function that corresponds to a directive with its args as parameters
	for ( ; index < file.size() && file[index] != "}"; index++) {
		if ((iter = Config::parsingMap.find(file[index])) == Config::parsingMap.end()) {
			if (directive == "")
				return file[index] == "}" ? 1 : 0;
			args.push_back(file[index]);
		}
		else
		{
			(this->*Config::parsingMap[directive])(args);
			args.clear();
			directive = iter->first;
		}
	}

	if (directive != "")
		(this->*Config::parsingMap[directive])(args);
	//  set up default values if they were not set by the config file
	if (file[index] == "}") {
		if (this->_listen.size() == 0) {
			args.push_back("localhost:80");
			(this->*Config::parsingMap["listen"])(args);
		}
		if (this->_root == "") {
			args.clear();
			args.push_back("/");
			(this->*Config::parsingMap["root"])(args);
		}
		++index;
		return 1;
	}
	return 0;
}

void        ConfigServer::addListen(std::vector<std::string> args) {
	t_listen    listen;
	size_t      separator;
	
	if (args.size() != 1)
		throw ConfigServer::ExceptionInvalidArguments();

	if ((separator = args[0].find(";")) == std::string::npos)
		throw ConfigServer::ExceptionInvalidArguments();
	
	listen.host = args[0].substr(0, separator);
	separator++;

	std::string	strPort = args[0].substr(separator);
	if (isDigits(strPort) == false)
		throw ConfigServer::ExceptionInvalidArguments();
	listen.port = std::stoi(strPort);
	this->_listen.push_back(listen);
}

void        ConfigServer::addRoot(std::vector<std::string> args) {
	if (args.size() != 1 || this->_root.size() != 0)
		throw ConfigServer::ExceptionInvalidArguments();
	this->_root = args[0];
}

void        ConfigServer::addServerName(std::vector<std::string> args) {
	if (args.size() == 0)
		throw ConfigServer::ExceptionInvalidArguments();
	for (unsigned int i = 0; i < args.size(); i++)
		this->_server_name.push_back(args[i]);
}

void        ConfigServer::addErrorPage(std::vector<std::string> args) {
	bool	codeFound = false;
	t_error_page	error_page;
	size_t			len = args.size();
	
	for (size_t i = 0; i < len; i++) {
		if (isDigits(args[i])) {
			error_page.errorCodes.push_back(std::stoi(args[i]));
			codeFound = true;
		}
		else if (!codeFound)
			throw ConfigServer::ExceptionInvalidArguments();
		else if (i == len - 1)
			error_page.uri = args[i];
		else
			throw ConfigServer::ExceptionInvalidArguments();		
	}
}

void        ConfigServer::addClientBodyBufferSize(std::vector<std::string> args) {
	if (args.size() != 1 || !isDigits(args[0]))
		throw ConfigServer::ExceptionInvalidArguments();
	this->_client_body_buffer_size = std::stoi(args[0]);
}

std::ostream	&operator<<(std::ostream &out, const ConfigServer &server) {
	out << "Listen:" << std::endl;
	for (size_t i = 0; i < server._listen.size(); i++) {
		out << "\thost: " << server._listen[i].host << " port: " << server._listen[i].port << std::endl;
	}
	out << "root: " << server._root << std::endl;
	out << "server_name: ";
	for (size_t i = 0; i < server._server_name.size(); i++) {
		out << server._server_name[i];
		if (i != server._server_name.size() - 1)
			out << " ";
	}
	out << "error_page:" << std::endl;
	for (size_t i = 0; i < server._error_page.size(); i++) {
		out << "\t";
		for (size_t j = 0; j < server._error_page[i].errorCodes.size(); j++) {
			out << server._error_page[i].errorCodes[j] << " ";
		}
		out << server._error_page[i].uri << std::endl;
	}
	out << "client_body_buffer_size: " << server._client_body_buffer_size << std::endl;
	return out;
}

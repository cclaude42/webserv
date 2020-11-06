/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 15:28:08 by user42            #+#    #+#             */
/*   Updated: 2020/11/06 15:25:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigServer.hpp"

ConfigServer::ConfigServer(void):
_root("/"),
_client_body_buffer_size(8000)
{
	t_listen    listenDefault;

	listenDefault.host = "localhost";
	listenDefault.port = 80;
	this->_listen.push_back(listenDefault);

	//  maybe set default error pages
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

	for (index ; index < file.size() && file[index] != "}"; index++) {
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
	//  if listen is not set, listen to port 80 on localhost by default
	if (file[index] == "}") {
		if (this->_listen.size() == 0) {
			args.push_back("localhost:80");
			(this->*Config::parsingMap["listen"])(args);
		}
		++index;
		return 1;
	}
	return 0;
}

const char		*ConfigReader::CannotOpenFileException::what() const throw() {
	return "Exception: invalid arguments";
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
	for (int i = 0; i < args.size(); i++)
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

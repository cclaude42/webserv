/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 15:28:08 by user42            #+#    #+#             */
/*   Updated: 2020/11/08 03:29:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigServer.hpp"

bool isDigits(const std::string &str) {
	return str.find_first_not_of("0123456789") == std::string::npos;
}

ConfigServer::ConfigServer(void):
_root(""),
_client_body_buffer_size(8000)
{
	return ;
}

ConfigServer::ConfigServer(ConfigServer const &src) {
	if (this != &src) {
		this->_listen = src._listen;		
		this->_root = src._root;		
		this->_server_name = src._server_name;		
		this->_error_page = src._error_page;		
		this->_client_body_buffer_size = src._client_body_buffer_size;		
	}
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
	std::string                 directive;

	//	calling the function that corresponds to a directive with its args as parameters
	if ((iter = Config::serverParsingMap.find(file[index])) == Config::serverParsingMap.end())
		return 0;
	directive = iter->first;
	index++;
	for ( ; index < file.size() && file[index].compare("}") ; index++) {
		if ((iter = Config::serverParsingMap.find(file[index])) == Config::serverParsingMap.end()) {
			if (!directive.compare(""))
				return file[index] == "}" ? 1 : 0;
			args.push_back(file[index]);
		}
		// else if (file[index] == "location") {
		// 	ConfigServer::Location	location(*this);
			
		// 	index++;
		// 	if (!location.parse(index, file))
		// 		return 0;
		// 	this->_locations.push_back(location);
		// }
		else
		{
			(this->*Config::serverParsingMap[directive])(args);
			args.clear();
			directive = iter->first;
		}
	}

	if (directive != "")
		(this->*Config::serverParsingMap[directive])(args);
	//  set up default values if they were not set by the config file
	if (!file[index].compare("}")) {
		if (this->_listen.size() == 0) {
			args.push_back("localhost:80");
			(this->*Config::serverParsingMap["listen"])(args);
		}
		if (this->_root == "") {
			args.clear();
			args.push_back("/");
			(this->*Config::serverParsingMap["root"])(args);
		}
		std::cout << this->_cgi_param["hello"] << std::endl;
		return 1;
	}
	return 0;
}

// int			ConfigServer::Location::parse(unsigned int &index, fileVector &file) {
	
// }

// ADDING MEMBER VALUES

void        ConfigServer::addListen(std::vector<std::string> args) {
	t_listen    listen;
	size_t      separator;
	
	// std::cout << "in addListen" << std::endl;
	if (args.size() != 1)
		throw ConfigServer::ExceptionInvalidArguments();
	if ((separator = args[0].find(":")) == std::string::npos) {
		if (isDigits(args[0])) {
			listen.host = "localhost";
			listen.port = std::stoi(args[0]);
			return ;
		}
		throw ConfigServer::ExceptionInvalidArguments();
	}
	listen.host = args[0].substr(0, separator);
	separator++;

	std::string	strPort = args[0].substr(separator);
	if (isDigits(strPort) == false)
		throw ConfigServer::ExceptionInvalidArguments();
	listen.port = std::stoi(strPort);
	this->_listen.push_back(listen);
}

void        ConfigServer::addRoot(std::vector<std::string> args) {
	// std::cout << "in addRoot" << std::endl;
	if (args.size() != 1 || this->_root != "")
		throw ConfigServer::ExceptionInvalidArguments();
	this->_root = args[0];
}

void        ConfigServer::addServerName(std::vector<std::string> args) {
	// std::cout << "in addServerName" << std::endl;
	if (args.size() == 0)
		throw ConfigServer::ExceptionInvalidArguments();
	for (unsigned int i = 0; i < args.size(); i++)
		this->_server_name.push_back(args[i]);
}

void        ConfigServer::addErrorPage(std::vector<std::string> args) {
	// std::cout << "in addErrorPage" << std::endl;
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
	this->_error_page.push_back(error_page);
}

void        ConfigServer::addClientBodyBufferSize(std::vector<std::string> args) {
	// std::cout << "in addBodySize" << std::endl;
	if (args.size() != 1 || !isDigits(args[0]))
		throw ConfigServer::ExceptionInvalidArguments();
	this->_client_body_buffer_size = std::stoi(args[0]);
}

void		ConfigServer::addCgiParam(std::vector<std::string> args) {
	if (args.size() != 2)
		throw ConfigServer::ExceptionInvalidArguments();
	this->_cgi_param.insert({args[0], args[1]});
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
	out << std::endl<< "error_page:" << std::endl;
	for (size_t i = 0; i < server._error_page.size(); i++) {
		out << "\t";
		for (size_t j = 0; j < server._error_page[i].errorCodes.size(); j++) {
			out << server._error_page[i].errorCodes[j] << " ";
		}
		out << server._error_page[i].uri << std::endl;
	}
	out << "client_body_buffer_size: " << server._client_body_buffer_size << std::endl;
	out << "cgi_param:" << std::endl;
	for (auto i = server._cgi_param.begin(); i != server._cgi_param.end(); i++)
		std::cout << "\t" << i->first << " = " << i->second << std::endl;
	
	if (server._cgi_param.find("hello") == server._cgi_param.end())
		std::cout << "WTF" << std::endl;
	return out;
}

const char		*ConfigServer::ExceptionInvalidArguments::what() const throw() {
	return "Exception: invalid arguments in configuration file";
}
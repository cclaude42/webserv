/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:40:39 by user42            #+#    #+#             */
/*   Updated: 2020/11/13 18:15:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"

Location::Location(void):
ConfigServer()
{
	return ;
}

Location::Location(Location const &src):
ConfigServer(src)
{
	if (this != &src) {
		return ;
	}
	return ;
}

Location::~Location(void) {
	return ;
}

Location	&Location::operator=(Location const &src) {
	if (this != &src) {
		this->_listen = src._listen;		
		this->_root = src._root;		
		this->_server_name = src._server_name;		
		this->_error_page = src._error_page;		
		this->_client_body_buffer_size = src._client_body_buffer_size;
		this->_cgi_param = src._cgi_param;
		this->_cgi_pass = src._cgi_pass;
		this->_location = src._location;
	}
	return *this;
}

locationParseMap Location::initLocationMap() {
			locationParseMap     myMap;
			myMap["root"] = &Location::addRoot;
			myMap["error_page"] = &Location::addErrorPage;
			myMap["client_body_buffer_size"] = &Location::addClientBodyBufferSize;
			myMap["cgi_param"] = &Location::addCgiParam;
			myMap["cgi_pass"] = &Location::addCgiPass;
			return myMap;
}

locationParseMap Location::parsingMap = Location::initLocationMap();

int     Location::parse(unsigned int &index, fileVector &file) {
	fileVector                  args;
	locationParseMap::iterator          iter;
	std::string                 directive = "";

	// std::cout << "IN LOCATION::PARSE" << std::endl;
	if (file[index++] != "{")
		return 0;
	// std::cout << "index: " << file[index] << std::endl;
	//	calling the function that corresponds to a directive with its args as parameters
	for ( ; index < file.size() && file[index] != "}" ; index++) {
		if ((iter = Location::parsingMap.find(file[index])) == Location::parsingMap.end()) {
			if (file[index] == "location") {
				Location	location;
				std::string	locationName;
				
				if (directive != "") {
					(this->*Location::parsingMap[directive])(args);
					args.clear();
					directive = "";
				}
				index++;
				if (file[index] == "{" || file[index] == "}")
					return 0;
				locationName = file[index];
				index++;
				if (!location.parse(index, file))
					return 0;
				this->_location[locationName] = location;
				if (file[index] == "}")
					continue ;
			}
			else if (directive == "")
				return file[index] == "}" ? 1 : 0;
			else
				args.push_back(file[index]);
		}
		else
		{
			if (directive != "") {
				(this->*Location::parsingMap[directive])(args);
				args.clear();
			}
			directive = iter->first;
		}
	}
	if (directive != "")
		(this->*Location::parsingMap[directive])(args);
	//  set up default values if they were not set by the config file
	if (!file[index].compare("}"))
		return 1;
	return 0;
}

std::ostream	&operator<<(std::ostream &out, const Location &server) {
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
	for (auto i = server._error_page.begin(); i != server._error_page.end(); i++) {
		out << "\t" << i->first << " " << i->second << std::endl;
	}
	out << "client_body_buffer_size: " << server._client_body_buffer_size << std::endl;
	out << "cgi_param:" << std::endl;
	for (auto i = server._cgi_param.begin(); i != server._cgi_param.end(); i++)
		out << "\t" << i->first << " = " << i->second << std::endl;
	out << "cgi_pass:	" << server._cgi_pass.address.host << ":" << server._cgi_pass.address.port << std::endl;
	for (auto i = server._location.begin(); i != server._location.end(); i++) {
		out << std::endl << "location " << i->first << std::endl;
		out << i->second << std::endl;
	}
	return out;
	return out;
}

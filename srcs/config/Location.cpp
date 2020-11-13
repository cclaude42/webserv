/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:40:39 by user42            #+#    #+#             */
/*   Updated: 2020/11/13 11:48:42 by user42           ###   ########.fr       */
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

	std::cout << "IN LOCATION::PARSE" << std::endl;
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
			else if (directive == "") {
				std::cout << "HERE" << std::endl;
				return file[index] == "}" ? 1 : 0;
			}
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

std::ostream	&operator<<(std::ostream &out, const Location &location) {
	out << "root: " << location._root << std::endl;
	out << std::endl<< "error_page:" << std::endl;
	for (size_t i = 0; i < location._error_page.size(); i++) {
		out << "\t";
		for (size_t j = 0; j < location._error_page[i].errorCodes.size(); j++) {
			out << location._error_page[i].errorCodes[j] << " ";
		}
		out << location._error_page[i].uri << std::endl;
	}
	out << "client_body_buffer_size: " << location._client_body_buffer_size << std::endl;
	out << "cgi_param:" << std::endl;
	for (auto i = location._cgi_param.begin(); i != location._cgi_param.end(); i++)
		out << "\t" << i->first << " = " << i->second << std::endl;
	
	return out;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:40:39 by user42            #+#    #+#             */
/*   Updated: 2020/11/12 15:21:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"

Location::Location(void):
_root(""),
_client_body_buffer_size(8000)
{
	return ;
}

Location::Location(Location const &src) {
	if (this != &src) {
		this->_root = src._root;		
		this->_error_page = src._error_page;		
		this->_client_body_buffer_size = src._client_body_buffer_size;
		this->_cgi_param = src._cgi_param;
		this->_cgi_pass = src._cgi_pass;
		this->_location = src._location;
		
	}
	return ;
}

Location::~Location(void) {
	return ;
}

Location	&Location::operator=(Location const &src) {
	if (this != &src) {
		this->_root = src._root;		
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

locationParseMap Location::locationParsingMap = Location::initLocationMap();

int     Location::parse(unsigned int &index, fileVector &file) {
	fileVector                  args;
	locationParseMap::iterator          iter;
	std::string                 directive;

	// std::cout << "in Location::parse" << std::endl;
	if (file[index++] != "{")
		return 0;
	//	calling the function that corresponds to a directive with its args as parameters
	for ( ; index < file.size() && file[index] != "}" ; index++) {
		if ((iter = Location::locationParsingMap.find(file[index])) == Location::locationParsingMap.end()) {
			if (file[index] == "location") {
				Location	location;
				std::string	locationName;
				
				if (directive != "") {
					(this->*Location::locationParsingMap[directive])(args);
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
			else if (!directive.compare(""))
				return file[index] == "}" ? 1 : 0;
			else
				args.push_back(file[index]);
		}
		else
		{
			if (directive != "") {
				(this->*Location::locationParsingMap[directive])(args);
				args.clear();
			}
			directive = iter->first;
		}
	}
	if (directive != "")
		(this->*Location::locationParsingMap[directive])(args);
	//  set up default values if they were not set by the config file
	if (!file[index].compare("}")) {
		if (this->_root == "") {
			args.clear();
			args.push_back("/");
			(this->*Location::locationParsingMap["root"])(args);
		}
		return 1;
	}
	return 0;
}

void        Location::addRoot(std::vector<std::string> args) {
	// std::cout << "in addroot" << std::endl;
	if (args.size() != 1 || this->_root != "")
		throw Location::ExceptionInvalidArguments();
	// std::cout << "addRoot end" << std::endl;
	this->_root = args[0];
}

void        Location::addErrorPage(std::vector<std::string> args) {
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
			throw Location::ExceptionInvalidArguments();
		else if (i == len - 1)
			error_page.uri = args[i];
		else
			throw Location::ExceptionInvalidArguments();		
	}
	this->_error_page.push_back(error_page);
}

void        Location::addClientBodyBufferSize(std::vector<std::string> args) {
	// std::cout << "in addBodySize" << std::endl;
	if (args.size() != 1 || !isDigits(args[0]))
		throw Location::ExceptionInvalidArguments();
	this->_client_body_buffer_size = std::stoi(args[0]);
}

void		Location::addCgiParam(std::vector<std::string> args) {
	if (args.size() != 2)
		throw Location::ExceptionInvalidArguments();
	this->_cgi_param.insert({args[0], args[1]});
}

void    	Location::addCgiPass(std::vector<std::string> args) {
	t_listen    address;
	size_t      separator;
	
	// std::cout << "in addCgiPass" << std::endl;
	if (args.size() != 1 || this->_cgi_pass.set == true)
		throw ConfigServer::ExceptionInvalidArguments();
	if ((separator = args[0].find(":")) == std::string::npos) {
		throw ConfigServer::ExceptionInvalidArguments();
	}
	address.host = strToIp(args[0].substr(0, separator));
	separator++;
	std::string	strPort = args[0].substr(separator);
	if (isDigits(strPort) == false)
		throw ConfigServer::ExceptionInvalidArguments();
	address.port = std::stoi(strPort);
	this->_cgi_pass.address.port = address.port;
	this->_cgi_pass.address.host = address.host;
	this->_cgi_pass.set = true;
	// std::cout << "addCgiPass END" << std::endl;
}

const char		*Location::ExceptionInvalidArguments::what() const throw() {
	return "Exception: invalid arguments in location block";
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

std::string							Location::getRoot() const {
	return this->_root;
}

std::vector<t_error_page>			Location::getErrorPage() const {
	return this->_error_page;
}

int									Location::getClientBodyBufferSize() const {
	return this->_client_body_buffer_size;
}

std::map<std::string, std::string>	Location::getCgiParam() const {
	return this->_cgi_param;
}

t_cgi_pass							Location::getCgiPass() const {
	return this->_cgi_pass;
}
std::map<std::string, Location>		Location::getLocation() const {
	return this->_location;
}


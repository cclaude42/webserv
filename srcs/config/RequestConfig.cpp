/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestConfig.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:58:53 by franciszer        #+#    #+#             */
/*   Updated: 2020/11/20 17:32:03 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestConfig.hpp"

RequestConfig::RequestConfig(void) {
	return ;
}

RequestConfig::RequestConfig(ConfigServer &config, std::string path, std::string locationName):
_error_page(config.getErrorPage()),
_client_body_buffer_size(config.getClientBodyBufferSize()),
_cgi_param(config.getCgiParam()),
_cgi_pass(config.getCgiPass()),
_allowed_methods(config.getAllowedMethods()),
_index(config.getIndex()),
_autoindex(config.getAutoIndex())
{
	std::string	alias = config.getAlias();
	std::string	root = config.getRoot();
	std::string	ret;
	if (locationName != "" && alias != "") {
		ret = root + alias + path.substr(locationName.length());
	}
	else
		ret = root + path;
	this->_path = removeAdjacentSlashes(ret);
}

RequestConfig::RequestConfig(RequestConfig const &src) {
	if (this != &src) {
		this->_path = src._path;
		this->_error_page = src._error_page;
		this->_client_body_buffer_size = src._client_body_buffer_size;
		this->_cgi_param = src._cgi_param;
		this->_cgi_pass = src._cgi_pass;
		this->_allowed_methods = src._allowed_methods;
		this->_autoindex = src._autoindex;
		this->_index = src._index;
	}
	return ;
}

RequestConfig::~RequestConfig(void) {
	return ;
}

RequestConfig	&RequestConfig::operator=(RequestConfig const &src) {
	if (this != &src) {
		this->_path = src._path;
		this->_error_page = src._error_page;
		this->_client_body_buffer_size = src._client_body_buffer_size;
		this->_cgi_param = src._cgi_param;
		this->_cgi_pass = src._cgi_pass;
		this->_allowed_methods = src._allowed_methods;
		this->_autoindex = src._autoindex;
		this->_index = src._index;
	}
	return *this;
}

// GETER FUNCTIONS
std::string							RequestConfig::getPath() const {
	return this->_path;
}

std::map<int, std::string>			RequestConfig::getErrorPage() const {
	return this->_error_page;
}

int									RequestConfig::getClientBodyBufferSize() const {
	return this->_client_body_buffer_size;
}

std::map<std::string, std::string>	RequestConfig::getCgiParam() const {
	return this->_cgi_param;
}

t_cgi_pass							RequestConfig::getCgiPass() const {
	return this->_cgi_pass;
}

std::set<std::string>				RequestConfig::getAllowedMethods() const {
	return this->_allowed_methods;
}

//SETTERS

void								RequestConfig::setPath(int code)
{
	//default value hardcoded because at the moment I can't get access to values from config file
	this->_path = "/home/hannibal/Documents/Cursus42/webserv_v2/utils_tests/error/";
	this->_path += std::to_string(code) + ".html";
	// this->_path = this->_error_page[code];
}

void								RequestConfig::setPath(std::string path)
{
	this->_path = path;
}

std::ostream	&operator<<(std::ostream &out, RequestConfig &request) {
	out << "path: " << request._path << std::endl;
	out << "error_page:" << std::endl;
	for (auto i = request._error_page.begin(); i != request._error_page.end(); i++) {
		out << "\t" << i->first << " " << i->second << std::endl;
	}
	out << "client_body_buffer_size: " << request._client_body_buffer_size << std::endl;
	out << "cgi_param:" << std::endl;
	for (auto i = request._cgi_param.begin() ; i != request._cgi_param.end(); i++)
		out << "\t" << i->first << "=" << i->second << std::endl;
	if (request._cgi_pass.set)
		out << "cgi_pass: " << request._cgi_pass.address.host << ":" << request._cgi_pass.address.port << std::endl;
	out << "allowed_methods:" << std::endl;
	for (auto i = request._allowed_methods.begin(); i != request._allowed_methods.end(); i++)	
		out << "\t" << *i << std::endl;
	out << "index:" << std::endl;
	for (auto i = request._index.begin(); i != request._index.end(); i++)
		out << "\t" << *i << std::endl;
	out << "autoindex: " << (request._autoindex ? "on" : "off") << std::endl;
	return out;
}

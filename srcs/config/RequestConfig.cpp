/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestConfig.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:20:34 by frthierr          #+#    #+#             */
/*   Updated: 2021/03/15 09:10:02 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "RequestConfig.hpp"

RequestConfig::RequestConfig(void) {
	return ;
}

RequestConfig::RequestConfig(ConfigServer &config, const std::string &path, const std::string &method, const std::string &locationName):
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
	if (locationName[0] != '*' && config.getAliasSet()) {
		ret = root + alias + path.substr(locationName.length());
		this->_contentLocation = alias + removeAdjacentSlashes(path.substr(locationName.length()));
	}
	else {
		ret = root + path;
		this->_contentLocation = removeAdjacentSlashes(path);
	}
	this->_path = removeAdjacentSlashes(ret);
	// std::cout << "path : " << this->_path << "\n";
	// std::cout << "method : " << method << "\n";
	if (!pathIsFile(this->_path) && method == "GET" )
		this->addIndex();
}

RequestConfig::RequestConfig(RequestConfig const &src) {
	if (this != &src) {
		this->_contentLocation = src._contentLocation;
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
		this->_contentLocation = src._contentLocation;
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
const std::string							&RequestConfig::getContentLocation() const {
	return this->_contentLocation;
}

const std::string							&RequestConfig::getPath() const {
	return this->_path;
}

const std::map<int, std::string>			&RequestConfig::getErrorPage() const {
	return this->_error_page;
}

const int									&RequestConfig::getClientBodyBufferSize() const {
	return this->_client_body_buffer_size;
}

const std::map<std::string, std::string>	&RequestConfig::getCgiParam() const {
	return this->_cgi_param;
}

const std::string							&RequestConfig::getCgiPass() const {
	return this->_cgi_pass;
}

const std::set<std::string>				&RequestConfig::getAllowedMethods() const {
	return this->_allowed_methods;
}

const t_listen							&RequestConfig::getHostPort() const {
	return this->_hostPort;
}

const std::string						&RequestConfig::getRequestedPath() const {
	return this->_requestedPath;
}


//SETTERS

void								RequestConfig::setPath(int code)
{
	//default value hardcoded because at the moment I can't get access to values from config file
	this->_path = "./test_us/error/error/";
	this->_path += to_string(code) + ".html";
	// this->_path = this->_error_page[code];
}

void								RequestConfig::setPath(const std::string &path)
{
	this->_path = path;
}

void								RequestConfig::setContentLocation(const std::string &path)
{
	this->_contentLocation = path;
}

void								RequestConfig::setHostPort(const t_listen hostPort){
	this->_hostPort= hostPort;
}

void								RequestConfig::addIndex()
{
	std::vector<std::string>::iterator	it;
	std::string							path;

	it = this->_index.begin();
	while(it != this->_index.end())
	{
		path = this->_path;
		path += "/"  + *it;
		std::cout << "Testing path ; " << path << '\n';
		if (pathIsFile(path))
		{
			this->_path = path;
			this->_contentLocation += "/" + *it;
			std::cout << "Path |" << this->_path << "| valid\n";
			return ;
		}
		it++;
	}
	std::cout << "No valid index to add\n";
}


std::ostream	&operator<<(std::ostream &out, RequestConfig &request) {
	out << "path: " << request._path << std::endl;
	out << "error_page:" << std::endl;
	for (std::map<int, std::string>::iterator i = request._error_page.begin(); i != request._error_page.end(); i++) {
		out << "\t" << i->first << " " << i->second << std::endl;
	}
	out << "client_body_buffer_size: " << request._client_body_buffer_size << std::endl;
	out << "cgi_param:" << std::endl;
	for (std::map<std::string, std::string>::iterator i = request._cgi_param.begin() ; i != request._cgi_param.end(); i++)
		out << "\t" << i->first << "=" << i->second << std::endl;
	out << "cgi_pass: " << request._cgi_pass << std::endl;
	out << "allowed_methods:" << std::endl;
	for (std::set<std::string>::iterator i = request._allowed_methods.begin(); i != request._allowed_methods.end(); i++)
		out << "\t" << *i << std::endl;
	out << "index:" << std::endl;
	for (std::vector<std::string>::iterator i = request._index.begin(); i != request._index.end(); i++)
		out << "\t" << *i << std::endl;
	out << "autoindex: " << (request._autoindex ? "on" : "off") << std::endl;
	return out;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestConfig.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:20:34 by frthierr          #+#    #+#             */
/*   Updated: 2021/03/24 17:48:16 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestConfig.hpp"

RequestConfig::RequestConfig(void) {
	return ;
}

RequestConfig::RequestConfig(ConfigServer &config, Request &request, const std::string &path,  const std::string &method, const std::string &locationName):
_error_page(config.getErrorPage()),
_client_body_buffer_size(config.getClientBodyBufferSize()),
_cgi_param(config.getCgiParam()),
_cgi_pass(config.getCgiPass()),
_allowed_methods(config.getAllowedMethods()),
_lang(""),
_index(config.getIndex()),
_autoindex(config.getAutoIndex())
{
	std::string	alias = config.getAlias();
	std::string	root = config.getRoot();
	std::string	ret;

	for (std::map<std::string, std::string>::const_iterator it = request.getEnv().begin();\
		it != request.getEnv().end(); it++) {
			_cgi_param[it->first] = it->second;
		}
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
	if (!pathIsFile(this->_path) && method == "GET")
		this->addIndex(request);
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
		this->_hostPort.host = src._hostPort.host;
		this->_hostPort.port = src._hostPort.port;
	}
	return *this;
}

// GETER FUNCTIONS
const std::string&							RequestConfig::getContentLocation() const {
	return this->_contentLocation;
}

const std::string&							RequestConfig::getPath() const {
	return this->_path;
}

const std::map<int, std::string>			&RequestConfig::getErrorPage() const {
	return this->_error_page;
}

const unsigned long							&RequestConfig::getClientBodyBufferSize() const {
	return this->_client_body_buffer_size;
}

const std::map<std::string, std::string>	&RequestConfig::getCgiParam() const {
	return this->_cgi_param;
}

const std::string&							RequestConfig::getCgiPass() const {
	return this->_cgi_pass;
}

const std::string&							RequestConfig::getLang() const {
	return this->_lang;
}

const std::set<std::string>				&RequestConfig::getAllowedMethods() const {
	return this->_allowed_methods;
}

const t_listen							&RequestConfig::getHostPort() const {
	return this->_hostPort;
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
	this->_hostPort.port = hostPort.port;
	this->_hostPort.host = hostPort.host;
}

void								RequestConfig::addIndex(Request& request)
{
	std::vector<std::string>::iterator							it;
	std::list<std::pair<std::string, float> >::const_iterator	lang;
	std::string													path;

	it = this->_index.begin();
	while(it != this->_index.end()) // Check with language prefs
	{
		for (lang = request.getLang().begin(); lang != request.getLang().end(); lang++)
		{
			path = this->_path;
			if (path[path.size() - 1] != '/')
				path += "/";
			// path += "/"  + *it;
			path += (*it).substr(0, (*it).find_last_of('.') + 1) + lang->first + (*it).substr((*it).find_last_of('.'));
			if (pathIsFile(path))
			{
				this->_path = path;
				if (this->_contentLocation[this->_contentLocation.size() - 1] != '/')
					this->_contentLocation += "/";
				this->_contentLocation += (*it).substr(0, (*it).find_last_of('.') + 1) + lang->first + (*it).substr((*it).find_last_of('.'));
				// std::cout << "Path |" << this->_path << "| valid\n";
				return ;
			}
		}
		it++;
	}
	it = this->_index.begin();
	while(it != this->_index.end()) // check with index file only
	{
		path = this->_path;
		if (path[path.size() - 1] != '/')
			path += "/";
		path += *it;
		if (pathIsFile(path))
		{
			this->_path = path;
			if (this->_contentLocation[this->_contentLocation.size() - 1] != '/')
				this->_contentLocation += "/";
			this->_contentLocation += *it;
			return ;
		}
		it++;
	}
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

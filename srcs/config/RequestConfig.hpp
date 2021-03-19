/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestConfig.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisz <francisz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:41:01 by francisz          #+#    #+#             */
/*   Updated: 2021/03/18 20:06:53 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_CONFIG_HPP

# define REQUEST_CONFIG_HPP

#include "webserv.hpp"
#include "Request.hpp"
# include "Config.hpp"
# include "fstream"
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>


class RequestConfig {
	public:
		RequestConfig(void);
		RequestConfig(ConfigServer &config, Request request, const std::string &path,  const std::string &method, const std::string &locationName = "");
		RequestConfig(RequestConfig const &src);
		virtual ~RequestConfig(void);

		// OPERATORS
		RequestConfig   &operator=(RequestConfig const &src);
		friend std::ostream	&operator<<(std::ostream &out, RequestConfig &request);

		// GETERS
		const std::string							&getContentLocation() const;
		const std::string							&getPath() const;
		const std::map<int, std::string>			&getErrorPage() const;
		const unsigned long							&getClientBodyBufferSize() const;
		const std::map<std::string, std::string>	&getCgiParam() const;
		const std::string							&getCgiPass() const;
		const std::set<std::string>				&getAllowedMethods() const;
		const t_listen							&getHostPort() const;

		//SETTERS
		void								setPath(int code);
		void								setPath(const std::string&);
		void								setContentLocation(const std::string&);
		void								setHostPort(const t_listen hostPort);

		// HELPERS
		void								addIndex();

	private:
		std::string							_contentLocation; // public part of the path
		std::string							_path; // local path for request
		std::map<int, std::string>			_error_page; // error page redirections
		unsigned long						_client_body_buffer_size; // max size for the client body, defaults to 8 000
		std::map<std::string, std::string>	_cgi_param;
		std::string							_cgi_pass;
		std::set<std::string>				_allowed_methods; // allowed http methods for request
		t_listen							_hostPort;
		// THE NEXT TWO MEMBERS ONLY APPLY IF REQUEST IS A DIRECTORY, MEANING _PATH ENDS WITH A '/'
		// IF USED, NEW REQUEST IS MADE TO FETCH THE FILES
		std::vector<std::string>			_index; // THE SERVER WILL SEARCH FOR THESE FILE IN THE _path DIRECTORIES AND FETCH THE FIRST ONE FOUND
		bool								_autoindex; // THE SERVER WILL GENERATE A LIST OF ALL THE FILES IN THE DIRECTORY, MUCH LIKE THE NGINX DIRECTIVE
};

#endif

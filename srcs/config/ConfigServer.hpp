/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 15:27:44 by user42            #+#    #+#             */
/*   Updated: 2021/03/25 14:21:53 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_SERVER_HPP

# define CONFIG_SERVER_HPP

//  listen struct with host and port: default host: localhost; default port:80
//      host an either be an IP address or a domain name
//  server_name, default = ""
//  error_page ERR_CODE URI
//  client_body_buffer_size = 8k (bytes): max size of client body request
//  location (BLOCK) prefix:
//  root    URI: where the file will be fetched on the host machine
	// sends all request starting with prefix to the path specified by the root directive
//  add_header [http methods]: list all of the allowed http methods for a certain route, separated by whitespace
//      by default, all methods should be allowed

# include "webserv.hpp"

# include "Config.hpp"

class ConfigServer {
	public:
		ConfigServer(void);
		ConfigServer(ConfigServer const &src);
		virtual ~ConfigServer(void);

		ConfigServer						&operator=(ConfigServer const &src);
		int									parseServer(unsigned int &i, std::vector<std::string> &file);
		void								passMembers(ConfigServer &server) const;

		class	ExceptionInvalidArguments: public std::exception {
			virtual const char	*what() const throw();
		};

		static ConfigServer					_initDefaultServer(const char *filename);

		// GETERS
		std::vector<t_listen>				getListen() const;
		std::string							getRoot() const;
		std::vector<std::string>   			getServerName() const;
		std::map<int, std::string>			getErrorPage() const;
		int									getClientBodyBufferSize() const;
		std::map<std::string, std::string>	getCgiParam() const;
		std::string							getCgiPass() const;
		std::map<std::string, ConfigServer> getLocation() const;
		std::set<std::string>				getAllowedMethods() const;
		std::vector<std::string>			getIndex() const;
		bool								getAutoIndex() const;
		std::string							getAlias() const;
		bool								getAliasSet() const;
		static ConfigServer					&getDefaultServer();

		// RETURN CONFIG ACCORDING TO URI
		ConfigServer						getLocationForRequest(std::string const path, std::string &locationPath);

		friend	std::ostream &operator<<(std::ostream &out, const ConfigServer &server);

	private:
		int				parseLocation(unsigned int &i, std::vector<std::string> &file);
		// ADD MEMBER FUNCTIONS
		void    							addListen(std::vector<std::string> args);
		void    							addRoot(std::vector<std::string> args);
		void    							addServerName(std::vector<std::string> args);
		void    							addErrorPage(std::vector<std::string> args);
		void    							addClientBodyBufferSize(std::vector<std::string> args);
		void								addCgiParam(std::vector<std::string> args);
		void    							addCgiPass(std::vector<std::string> args);
		void								addAllowedMethods(std::vector<std::string> args);
		void								addIndex(std::vector<std::string> args);
		void								addAutoIndex(std::vector<std::string> args);
		void								addAlias(std::vector<std::string> args);

		// MEMBERS
		std::vector<t_listen>				_listen;
		std::string							_root;


		std::vector<std::string>   			_server_name;
		std::map<int, std::string>			_error_page; // error page redirections
		int									_client_body_buffer_size; // max size for the client body, defaults to 8 000
		std::map<std::string, std::string>	_cgi_param;
		std::string							_cgi_pass;
		std::map<std::string, ConfigServer>_location;
		std::set<std::string>				_allowed_methods;
		std::vector<std::string>			_index;
		bool								_autoindex;
		std::string							_alias;
		bool								_aliasSet;
		static  ConfigServer				_defaultServer;
		static	parseMap					serverParsingMap;
		static	parseMap					locationParsingMap;
		static parseMap 					_initServerMap();
		static parseMap 					_initLocationMap();


};

#endif

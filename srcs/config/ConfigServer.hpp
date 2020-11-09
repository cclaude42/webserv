/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 15:27:44 by user42            #+#    #+#             */
/*   Updated: 2020/11/09 17:38:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_SERVER_HPP

# define CONFIG_SERVER_HPP

# include "Location.hpp"

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


// TODO:
// -	ADD getters
// -	
bool isDigits(const std::string &str);

# define parseMap std::map<std::string, void (ConfigServer::*)(fileVector)>

class	Location;

class ConfigServer {
	public:
		ConfigServer(void);
		ConfigServer(ConfigServer const &src);
		virtual ~ConfigServer(void);

		ConfigServer	&operator=(ConfigServer const &src);
		int		parse(unsigned int &i, std::vector<std::string> &file);
        
		class	ExceptionInvalidArguments: public std::exception {
			virtual const char	*what() const throw();
		};

		// GETERS
		std::vector<t_listen>				getListen() const;
		std::string							getRoot() const;
		std::vector<std::string>   			getServerName() const;
		std::vector<t_error_page>			getErrorPage() const;
		int									getClientBodyBufferSize() const;
		std::map<std::string, std::string>	getCgiParam() const;
		t_cgi_pass							getCgiPass() const;
		std::map<std::string, Location>		getLocation() const;
		
		friend	std::ostream &operator<<(std::ostream &out, const ConfigServer &server);
	private:

		// PARSING FUNCTIONS
		void    addListen(std::vector<std::string> args);
        void    addRoot(std::vector<std::string> args);
        void    addServerName(std::vector<std::string> args);
        void    addErrorPage(std::vector<std::string> args);
        void    addClientBodyBufferSize(std::vector<std::string> args);
		void	addCgiParam(std::vector<std::string> args);
		void    addCgiPass(std::vector<std::string> args);
		static	parseMap					serverParsingMap;
		static parseMap 					initServerMap();
		
		// MEMBERS
		std::vector<t_listen>				_listen;
		std::string							_root;
		std::vector<std::string>   			_server_name;
		std::vector<t_error_page>			_error_page; // error page redirections
		int									_client_body_buffer_size; // max size for the client body, defaults to 8 000
		std::map<std::string, std::string>	_cgi_param;
		t_cgi_pass							_cgi_pass;
		std::map<std::string, Location>		_location;

};

#endif

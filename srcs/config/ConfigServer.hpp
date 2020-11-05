/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 15:27:44 by user42            #+#    #+#             */
/*   Updated: 2020/11/05 12:34:42 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_SERVER_HPP

# define CONFIG_SERVER_HPP

# include "webserv.hpp"
# include "ConfigReader.hpp"

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

typedef struct	s_listen {
	std::string	host;
	int			port;
}				t_listen;

typedef struct  s_error_page {
	std::vector<int>    errorCodes; // all of the codes that will be redirected
	std::string         uri;		// uri to which they are redirected
}               t_error_page;

class ConfigServer {
	public:
		ConfigServer(void);
		ConfigServer(ConfigServer const &src);
		virtual ~ConfigServer(void);

		ConfigServer	&operator=(ConfigServer const &src);
		int		parse(unsigned int &i, std::vector<std::string> &file);
	private:
		std::vector<t_listen>		_listen;
		std::string					_root;
		std::vector<std::string>    _server_name;
		std::vector<t_error_page>	_error_page; // error page redirections
		int							_client_body_buffer_size; // max size for the client body, defaults to 8 000

};

#endif

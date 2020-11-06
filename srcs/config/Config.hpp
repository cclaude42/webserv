/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:29:38 by user42            #+#    #+#             */
/*   Updated: 2020/11/05 17:56:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP

# define CONFIG_HPP

# include "ConfigServer.hpp"
# include "ConfigReader.hpp"
# include <map>
# include <vector>

#define parseMap std::map<std::string, void (ConfigServer::*)(fileVector)>

class Config {
	public:
		Config(void);
		Config(Config const &src);
		virtual ~Config(void);

		Config      &operator=(Config const &src);
		int         parse(char * const filename);
		static  parseMap parsingMap;
	private:
		static parseMap init_map() {
		    parseMap     myMap;
		    myMap["listen"] = ConfigServer::addListen;
		    myMap["root"] = ConfigServer::addRoot;
		    myMap["server_name"] = ConfigServer::addServerName;
		    myMap["error_page"] = ConfigServer::addErrorPage;
		    myMap["client_body_buffer_size"] = ConfigServer::addClientBodyBufferSize;
		    return myMap;
		}
		std::vector<ConfigServer>  _servers;    
};

#endif

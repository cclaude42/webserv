/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:29:38 by user42            #+#    #+#             */
/*   Updated: 2020/11/12 21:27:30 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP

# define CONFIG_HPP

# include "ConfigServer.hpp"
# include "ConfigReader.hpp"
# include <map>
# include <vector>

# define parseMap std::map<std::string, void (ConfigServer::*)(fileVector)>
# define lParseMap std::map<std::string, void (ConfigServer::Location::*)(fileVector)>
class	ConfigServer;

class Config {
	public:
		Config(void);
		Config(Config const &src);
		virtual ~Config(void);

		Config     			&operator=(Config const &src);
		int         		parse(const char * filename);
		static	parseMap	serverParsingMap;
		// static	lParseMap	locationParsingMap;

		friend	std::ostream	&operator<<(std::ostream &out, const Config &config);

		// Cesar's getter
		std::vector<ConfigServer> & getServers(void) { return _servers ; }

	private:
		static parseMap 			initServerMap();
		std::vector<ConfigServer> 	_servers;
};

std::ostream	&operator<<(std::ostream &out, const Config &config);

#endif

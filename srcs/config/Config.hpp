/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:29:38 by user42            #+#    #+#             */
/*   Updated: 2020/11/14 14:54:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP

# define CONFIG_HPP


# include "ConfigReader.hpp"

# define parseMap std::map<std::string, void (ConfigServer::*)(fileVector)>
# define locationParseMap std::map<std::string, void (Location::*)(fileVector)>

bool isDigits(const std::string &str);
unsigned int	strToIp(std::string strIp);

# include "ConfigServer.hpp"

# define DEFAULT_PATH "./files/default"

class ConfigServer;

class Config {
	public:
		Config();
		Config(Config const &src);
		virtual ~Config(void);

		Config     			&operator=(Config const &src);
		int         		parse(const char *filename);
		std::vector<ConfigServer>			getServers() const;
		friend	std::ostream	&operator<<(std::ostream &out, const Config &config);
	private:
		std::vector<ConfigServer> 	_servers;
};

std::ostream	&operator<<(std::ostream &out, const Config &config);

#endif

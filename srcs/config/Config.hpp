/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:29:38 by user42            #+#    #+#             */
/*   Updated: 2020/11/17 14:21:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP

# define CONFIG_HPP


# include "ConfigReader.hpp"

# define parseMap std::map<std::string, void (ConfigServer::*)(fileVector)>
# define locationParseMap std::map<std::string, void (Location::*)(fileVector)>

bool isDigits(const std::string &str);
unsigned int	strToIp(std::string strIp);
std::string		removeAdjacentSlashes(std::string &str);

# include "ConfigServer.hpp"

# define DEFAULT_PATH "./files/default"

class ConfigServer;
class RequestConfig;

class Config {
	public:
		Config();
		Config(Config const &src);
		virtual ~Config(void);

		Config     			&operator=(Config const &src);
		int         		parse(const char *filename);
		std::vector<ConfigServer>			getServers() const;
		RequestConfig						getConfigForRequest(t_listen const address,\
												std::string const uri, std::string const hostName) const;
		friend	std::ostream	&operator<<(std::ostream &out, const Config &config);
		
		// RETURN LIST OF ADDRESSES AND PORT WITH NO DUPLICATES
		std::vector<t_listen>				getAllListens() const;
	private:
		bool								getServerForRequest(ConfigServer &ret, t_listen const address, std::string const hostName) const;
	
		std::vector<ConfigServer> 	_servers;
};

std::ostream	&operator<<(std::ostream &out, const Config &config);

#endif

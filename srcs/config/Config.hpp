/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:29:38 by user42            #+#    #+#             */
/*   Updated: 2020/11/06 16:04:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP

# define CONFIG_HPP

# include "ConfigServer.hpp"
# include "ConfigReader.hpp"
# include <map>
# include <vector>

#define parseMap std::map<std::string, void (ConfigServer::*)(fileVector)>

class	ConfigServer;

class Config {
	public:
		Config(void);
		Config(Config const &src);
		virtual ~Config(void);

		Config      &operator=(Config const &src);
		int         parse(char * const filename);
		static  parseMap parsingMap;
		
		friend	std::ostream	&operator<<(std::ostream &out, const Config &config);
	private:
		static parseMap init_map();
		std::vector<ConfigServer>  _servers;    
};

std::ostream	&operator<<(std::ostream &out, const Config &config);

#endif

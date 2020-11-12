/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:29:38 by user42            #+#    #+#             */
/*   Updated: 2020/11/12 22:39:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP

# define CONFIG_HPP

# include "ConfigReader.hpp"
# include "ConfigServer.hpp"


# define lParseMap std::map<std::string, void (ConfigServer::Location::*)(fileVector)>

class	ConfigServer;

class Config {
	public:
		Config(void);
		Config(Config const &src);
		virtual ~Config(void);

		Config     			&operator=(Config const &src);
		int         		parse(char * const filename);
		
		friend	std::ostream	&operator<<(std::ostream &out, const Config &config);
	private:
		std::vector<ConfigServer> 	_servers;
};

std::ostream	&operator<<(std::ostream &out, const Config &config);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:29:38 by user42            #+#    #+#             */
/*   Updated: 2021/01/19 12:40:20 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP

# define CONFIG_HPP


# include "ConfigDataStructures.hpp"
# include "ConfigHelperFunctions.hpp"
# include "ConfigReader.hpp"
# include "ConfigServer.hpp"
# include "RequestConfig.hpp"
# include "webserv.hpp"

# define DEFAULT_PATH "./files/default"

class Config {
	public:
		Config();
		Config(Config const &src);
		virtual ~Config(void);

		Config     							&operator=(Config const &src);
		int         						parse(const char *filename);
		std::vector<ConfigServer>			getServers() const;
		RequestConfig						getConfigForRequest(t_listen const address,\
												std::string const uri, std::string const hostName) const;
		friend	std::ostream				&operator<<(std::ostream &out, const Config &config);

		// RETURN LIST OF ADDRESSES AND PORT WITH NO DUPLICATES
		std::vector<t_listen>				getAllListens() const;
	private:
		bool								getServerForRequest(ConfigServer &ret, t_listen const address, std::string const hostName) const;

		std::vector<ConfigServer> 			_servers;
};

std::ostream	&operator<<(std::ostream &out, const Config &config);

#endif

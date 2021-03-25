/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:29:38 by user42            #+#    #+#             */
/*   Updated: 2021/03/25 14:22:12 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP

# define CONFIG_HPP

# include "webserv.hpp"

# include "ConfigDataStructures.hpp"
# include "ConfigHelperFunctions.hpp"
# include "ConfigReader.hpp"
# include "ConfigServer.hpp"
# include "RequestConfig.hpp"

class Config {
	public:
		Config(std::string defaultServerPath = DEFAULT_CONFIG);
		Config(Config const &src);
		virtual ~Config(void);

		Config     							&operator=(Config const &src);
		int         						parse(const char *filename);
		std::vector<ConfigServer>			getServers() const;
		RequestConfig						getConfigForRequest(t_listen const address,\
												std::string const uri, std::string const hostName, const std::string& method,\
												Request &request) const;
		friend	std::ostream				&operator<<(std::ostream &out, const Config &config);

		// RETURN LIST OF ADDRESSES AND PORT WITH NO DUPLICATES
		std::vector<t_listen>				getAllListens() const;
	private:
		bool								getServerForRequest(ConfigServer &ret, t_listen const address, std::string const hostName) const;

		std::vector<ConfigServer> 			_servers;
};

std::ostream	&operator<<(std::ostream &out, const Config &config);

#endif

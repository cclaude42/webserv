/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 16:53:41 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/12 21:17:05 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLUSTER_HPP
# define CLUSTER_HPP

# include "webserv.hpp"
# include "Server.hpp"
# include "Config.hpp"
# include "Response.hpp"
# include "Request.hpp"

class Cluster {
public:
	Cluster(void);
	Cluster(const Cluster & src);
	~Cluster(void);

	Cluster & operator=(const Cluster & src);

	void	config(std::string fileconf);
	void	setup(void);
	void	run(void);
	void	clean(void);
private:
	Config						_config;
 	std::vector<Server>			_servers;
};

#endif

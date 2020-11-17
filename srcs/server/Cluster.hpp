/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 16:53:41 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/17 19:06:28 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLUSTER_HPP
# define CLUSTER_HPP

# include "webserv.hpp"
# include "Server.hpp"
# include "Config.hpp"

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
	Config					_config;
	std::map<int, Server>	_map;
	fd_set					_fd_set;
	unsigned int			_fd_size;
	long					_max_fd;
};

#endif
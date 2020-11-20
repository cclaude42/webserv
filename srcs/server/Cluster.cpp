/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 16:53:41 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/19 18:22:58 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cluster.hpp"

// Member functions

void	Cluster::config(std::string fileconf)
{
	_config.parse(fileconf.c_str());
}

void	Cluster::setup(void)
{
	// std::vector<t_listen>	vect = _config.getListen();
//
	std::vector<t_listen>	vect;
	t_listen				listen;

	listen.host = INADDR_ANY;
	listen.port = 8080;
	vect.push_back(listen);

	listen.host = INADDR_ANY;
	listen.port = 8081;
	vect.push_back(listen);

	listen.host = INADDR_ANY;
	listen.port = 8082;
	vect.push_back(listen);

	listen.host = INADDR_ANY;
	listen.port = 8083;
	vect.push_back(listen);
//

	_fd_size = vect.size();
	ft_memset(&_fd_set, 0, sizeof(fd_set));
	_max_fd = 0;

	for ( std::vector<t_listen>::const_iterator lstn = vect.cbegin() ; lstn != vect.cend() ; lstn++ )
	{
		Server		serv(*lstn);
		long		fd;

		serv.setup();
		fd = serv.getFD();
		_fd_set.fds_bits[fd / 64] |= (long)(1UL << fd % 64);
		_map.insert(std::make_pair(serv.getFD(), serv));
		if (serv.getFD() > _max_fd)
			_max_fd = serv.getFD();
	}
}

void	Cluster::run(void)
{
	// Testing with different pages
	std::map<int, Server>::iterator mit = _map.begin();
	(mit++)->second.setTmpRoot("root/index.html");
	(mit++)->second.setTmpRoot("root/index1.html");
	(mit++)->second.setTmpRoot("root/index2.html");
	(mit++)->second.setTmpRoot("root/index3.html");
	//
	while (1)
	{
		fd_set		working_set;
		struct timeval	timeout;
		int				ret;

		ft_memcpy(&working_set, &_fd_set, sizeof(_fd_set));
		timeout.tv_sec  = 5;
		timeout.tv_usec = 0;

		std::cout << "Waiting on a connection..." << std::endl;
		ret = select(_max_fd + 1, &working_set, NULL, NULL, &timeout);
		if (ret > 0)
			std::cout << "Received a connection !" << std::endl << std::endl;

		for ( std::map<int, Server>::iterator it = _map.begin() ; it != _map.end() ; it++ )
		{
			long	fd;

			fd = it->first;
			if (working_set.fds_bits[fd / 64] & (long)(1UL << fd % 64))
				it->second.run(this->_config);
		}
	}
}

void	Cluster::clean(void)
{
	for ( std::map<int, Server>::iterator it = _map.begin() ; it != _map.end() ; it++ )
		it->second.clean();
}

// Overloaders

Cluster & Cluster::operator=(const Cluster & src)
{
	_config = src._config;
	_map = src._map;
	_fd_set = src._fd_set;
	_fd_size = src._fd_size;
	_max_fd = src._max_fd;
	return (*this);
}

// Constructors and destructors

Cluster::Cluster(void)
{
}

Cluster::Cluster(const Cluster & src)
{
	*this = src;
}

Cluster::~Cluster(void)
{
}

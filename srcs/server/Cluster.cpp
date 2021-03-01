/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 16:53:41 by cclaude           #+#    #+#             */
/*   Updated: 2021/03/01 11:48:25 by hbaudet          ###   ########.fr       */
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
	std::vector<t_listen>	vect = _config.getAllListens();

	_fd_size = vect.size();
	ft_memset(&_fd_set, 0, sizeof(fd_set));
	_max_fd = 0;

	for ( std::vector<t_listen>::const_iterator lstn = vect.begin() ; lstn != vect.end() ; lstn++ )
	{
		Server		serv(*lstn);
		long		fd;

		std::cout << "Setting up " << lstn->host << ":" << lstn->port << "..." << std::endl;
		serv.setup();
		fd = serv.getFD();
		_fd_set.fds_bits[fd / 64] |= (long)(1UL << fd % 64);
		_map.insert(std::make_pair(serv.getFD(), serv));
		if (serv.getFD() > _max_fd)
			_max_fd = serv.getFD();
		std::cout << "Set up " << lstn->host << ":" << lstn->port << " on FD " << fd << std::endl;
	}
}

void	Cluster::run(void)
{
	std::string	dot[3] = {".  ", ".. ", "..."};
	int			n = 0;

	while (1)
	{
		fd_set		working_set;
		struct timeval	timeout;
		int				ret = 0;

		std::cout << std::endl;

		while (ret == 0)
		{
			ft_memcpy(&working_set, &_fd_set, sizeof(_fd_set));
			timeout.tv_sec  = 1;
			timeout.tv_usec = 0;

			std::cout << "\rWaiting on a connection" << dot[n++] << std::flush;
			if (n == 3)
				n = 0;

			ret = select(_max_fd + 1, &working_set, NULL, NULL, &timeout);
		}

		if (ret > 0)
		{
			std::cout << std::endl << "\rReceived a connection !   " << std::endl;

			for ( std::map<int, Server>::iterator it = _map.begin() ; it != _map.end() && ret ; it++ )
			{
				long	fd;

				fd = it->first;
				if (working_set.fds_bits[fd / 64] & (long)(1UL << fd % 64))
				{
					std::cout << "Reading from : " << fd << std::endl;
					it->second.run(_config);
					ret--;
				}
			}
		}
		else
			std::cout << RED << "Problem with select !" << RESET << std::endl;

		n = 0;
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

Cluster::Cluster(void) : _config(DEFAULT_CONFIG)
{
}

Cluster::Cluster(const Cluster & src) : _config(DEFAULT_CONFIG)
{
	*this = src;
}

Cluster::~Cluster(void)
{
}

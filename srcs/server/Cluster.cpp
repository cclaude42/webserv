/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 16:53:41 by cclaude           #+#    #+#             */
/*   Updated: 2021/03/17 15:33:10 by frthierr         ###   ########.fr       */
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

	FD_ZERO(&_fd_set);
	_fd_size = vect.size();
	_max_fd = 0;

	for ( std::vector<t_listen>::const_iterator lstn = vect.begin() ; lstn != vect.end() ; lstn++ )
	{
		Server		serv(*lstn);
		long		fd;

		std::cout << "Setting up " << lstn->host << ":" << lstn->port << "..." << std::endl;
		serv.setup();
		fd = serv.getFD();
		FD_SET(fd, &_fd_set);
		_servers.insert(std::make_pair(fd, serv));
		if (fd > _max_fd)
			_max_fd = fd;
		// std::cout << "Set up " << lstn->host << ":" << lstn->port << " on FD " << fd << std::endl;
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
			std::cout << "\rReceived a connection !   " << std::endl;

			for ( std::map<long, Server *>::iterator it = _accepts.begin() ; it != _accepts.end() && ret ;)
			{
				// CEASAR CHECK SI ON A PAS FOUTU LE BORDEL AVEC TON ITERATEUR
				long	fd;

				fd = it->first;
				if (FD_ISSET(fd, &working_set))
				{
					// std::cout << "Reading from : " << fd << std::endl;
					if (it->second->run(_config, fd) == -1)
					{
						FD_CLR(fd, &_fd_set);
						it++;
						_accepts.erase(fd);
					}
					else
						it++;
				}
				else
					it++;
			}

			for ( std::map<long, Server>::iterator it = _servers.begin() ; it != _servers.end() && ret ; it++ )
			{
				long	fd;

				fd = it->first;
				if (FD_ISSET(fd, &working_set))
				{
					long	retfd;

					// std::cout << "Reading from : " << fd << std::endl;
					retfd = it->second.run(_config, 0);

					if (ret != -1)
					{
						// std::cout << "adding fd " << retfd << std::endl;
						FD_SET(retfd, &_fd_set);
						_accepts.insert(std::make_pair(retfd, &(it->second)));
						if (retfd > _max_fd)
							_max_fd = retfd;
					}

					ret--;
				}
			}
		}
		else
			std::cerr << RED << "Problem with select !" << RESET << std::endl;

		n = 0;
	}
}

void	Cluster::clean(void)
{
	for ( std::map<long, Server>::iterator it = _servers.begin() ; it != _servers.end() ; it++ )
		it->second.clean();
}

// Overloaders

Cluster & Cluster::operator=(const Cluster & src)
{
	_config = src._config;
	_servers = src._servers;
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

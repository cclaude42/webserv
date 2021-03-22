/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 16:53:41 by cclaude           #+#    #+#             */
/*   Updated: 2021/03/22 16:31:18 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cluster.hpp"

// Member functions

void	Cluster::config(std::string fileconf)
{
	_config.parse(fileconf.c_str());
}

int		Cluster::setup(void)
{
	std::vector<t_listen>	vect = _config.getAllListens();

	FD_ZERO(&_fd_set);
	_fd_size = vect.size();
	_max_fd = 0;

	for ( std::vector<t_listen>::const_iterator lstn = vect.begin() ; lstn != vect.end() ; lstn++ )
	{
		Server		serv(*lstn);
		long		fd;

		if (serv.setup() != -1)
		{
			fd = serv.getFD();
			FD_SET(fd, &_fd_set);
			_servers.insert(std::make_pair(fd, serv));
			if (fd > _max_fd)
				_max_fd = fd;
			std::cout << "Setting up " << lstn->host << ":" << lstn->port << "..." << std::endl;
		}
	}

	if (_max_fd == 0)
	{
		std::cerr << RED << "Could not setup cluster !" << RESET << std::endl;
		return (-1);
	}
	else
		return (0);
}

void	Cluster::run(void)
{
	std::string	dot[3] = {".  ", ".. ", "..."};
	int			n = 0;
	int			counter = 0;

	while (1)
	{
		counter++;
		if (counter == 150000)
			break ;
		else if (counter % 10000 == 0)
			std::cerr << RED << "10000 rounds have passed\n" << RESET;
		fd_set		reading_set;
		fd_set		writing_set;
		struct timeval	timeout;
		int				ret = 0;

		while (ret == 0)
		{
			timeout.tv_sec  = 1;
			timeout.tv_usec = 0;
			ft_memcpy(&reading_set, &_fd_set, sizeof(_fd_set));
			FD_ZERO(&writing_set);
			for (std::vector<int>::iterator it = _ready.begin() ; it != _ready.end() ; it++)
				FD_SET(*it, &writing_set);

			std::cout << "\rWaiting on a connection" << dot[n++] << std::flush;
			if (n == 3)
				n = 0;

			if (_ready.empty())
				ret = select(_max_fd + 1, &reading_set, NULL, NULL, &timeout);
			else
				ret = select(_max_fd + 1, &reading_set, &writing_set, NULL, &timeout);
		}

		if (ret > 0)
		{
			for (std::vector<int>::iterator it = _ready.begin() ; ret && it != _ready.end() ; it++)
			{
				if (FD_ISSET(*it, &writing_set))
				{
					_sockets[*it]->send(*it);
					_ready.erase(it);
					ret = 0;
					break;
				}
			}

			if (ret)
				std::cout << "\rReceived a connection !   " << std::flush;

			for (std::map<long, Server *>::iterator it = _sockets.begin() ; ret && it != _sockets.end() ; it++)
			{
				long	socket = it->first;

				if (FD_ISSET(socket, &reading_set))
				{
					long	ret = it->second->recv(socket);

					if (ret == 0)
					{
						it->second->process(socket, _config);
						_ready.push_back(socket);
					}
					else if (ret == -1)
					{
						FD_CLR(socket, &_fd_set);
						FD_CLR(socket, &reading_set);
						_sockets.erase(socket);
						it = _sockets.begin();
					}
					ret = 0;
					break;
				}
			}

			for (std::map<long, Server>::iterator it = _servers.begin() ; ret && it != _servers.end() ; it++)
			{
				long	fd = it->first;

				if (FD_ISSET(fd, &reading_set))
				{
					long	socket = it->second.accept();

					if (socket != -1)
					{
						FD_SET(socket, &_fd_set);
						_sockets.insert(std::make_pair(socket, &(it->second)));
						if (socket > _max_fd)
							_max_fd = socket;
					}
					ret = 0;
					break;
				}
			}
		}
		else
			std::cerr << RED << "Problem with select !" << RESET << std::endl;

		n = 0;
	}
	std::cout << "End of loop, counter: " << counter << '\n';
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

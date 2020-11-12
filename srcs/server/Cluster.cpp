/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 16:53:41 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/12 21:34:00 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cluster.hpp"

// Member functions

void	Cluster::config(std::string fileconf)
{
	_config.parse(fileconf.c_str());

	std::vector<ConfigServer>	vect = _config.getServers();

	for ( std::vector<ConfigServer>::const_iterator conf = vect.cbegin() ; conf != vect.cend() ; conf++ )
	{
		std::cout << "In loop" << std::endl;
		Server		serv(*conf);
		_servers.push_back(serv);
	}
}

void	Cluster::setup(void)
{
	for ( std::vector<Server>::iterator serv = _servers.begin() ; serv != _servers.end() ; serv++ )
		serv->setup();
}

void	Cluster::run(void)
{
	// while (1)
	// {
		for ( std::vector<Server>::iterator serv = _servers.begin() ; serv != _servers.end() ; serv++ )
		{
			Request		request;
			Response	response;
			std::string	received;
			// std::string	filename;

			serv->accept();
			received = serv->recv();

			request.parse(received.c_str());

			response.setFilename("root/index.html");
			response.make();

			serv->send(response.getResponse());

			serv->close();
		}
	// }
}

void	Cluster::clean(void)
{
	for ( std::vector<Server>::iterator serv = _servers.begin() ; serv != _servers.end() ; serv++ )
		serv->clean();
}

// Overloaders

Cluster & Cluster::operator=(const Cluster & src)
{
	_config = src._config;
	_servers = src._servers;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:40:00 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/12 20:20:50 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include "Server.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Cluster.hpp"

int		main(int ac, char **av)
{
	if (ac == 2)
	{
		Cluster		cluster;

		cluster.config(av[1]);
		cluster.setup();
		cluster.run();
		cluster.clean();
	}
	else
	{
		std::cerr << "Invalid number of argument." << std::endl;
		return (1);
	}
	return (0);
}

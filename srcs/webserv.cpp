/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:40:00 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/16 17:48:27 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include "Server.hpp"
#include "Request.hpp"
#include "Response.hpp"

int	g_counter;

void	run(Server & serv)
{
	std::cout << "============ REQUEST " << g_counter << " ============\n";

	serv.accept();
	std::string request = serv.recv();

	std::cout << "Request " << g_counter << " received, gonna parse it now\n";
	std::cout << request << '\n';
	Request	req(request);
	std::cout << "Request has been parsed\n" << req;
	
	serv.send(serv.answer(req.getMethod(), req));

	serv.close();
	g_counter++;
	std::cout << "===================================\n";
}

int		main(int ac, char *av[])
{
	Server		serv;
	int			port;

	g_counter = 0;
	port = 8080;
	if (ac > 1)
		port = ft_atoi(av[1]);
	serv.setup(port);
	while (1)
		run(serv);
	serv.end();

	return (0);
}

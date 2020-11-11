/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:40:00 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/11 18:51:25 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include "Server.hpp"
#include "Request.hpp"
#include "Response.hpp"

void	run(Server & serv)
{
	Request		req;
	Response	resp;

	serv.accept();
	std::string request = serv.recv();

	req.parse(request);

	std::cout << req << "End of Request\n"; // if you see this, remove this line
	std::cout << "Port : " << req.getPort() << '\n'; // if you see this, remove this line
	std::cout << "\n________________________\n"; // if you see this, remove this line

	resp.setFilename("root/index.html");
	resp.make();

	serv.send(resp.getResponse());

	serv.close();
}

int		main(int ac, char *av[])
{
	Server		serv;
	int			port;

	port = 8080;
	if (ac > 1)
		port = ft_atoi(av[1]);
	serv.setup(port);
	while (1)
		run(serv);
	serv.end();

	return (0);
}

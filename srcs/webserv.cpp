/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:40:00 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/10 18:04:22 by hbaudet          ###   ########.fr       */
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

	std::cout << "Headers :\n" << req << "\nEnd of Headers\n"; // if you see this, remove this line
	std::cout << "Port : " << req.getPort() << '\n'; // if you see this, remove this line

	resp.setFilename("root/index.html");
	resp.make();

	serv.send(resp.getResponse());

	serv.close();
}

int		main(void)
{
	Server		serv;

	serv.setup();
	while (1)
		run(serv);
	serv.end();

	return (0);
}

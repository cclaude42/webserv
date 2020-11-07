/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:40:00 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/07 18:47:54 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include "Server.hpp"
#include "Response.hpp"

void	run(Server & serv)
{
	Response	resp;

	serv.accept();
	std::string request = serv.recv();

	// parse request

	resp.setFilename("index.html");
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

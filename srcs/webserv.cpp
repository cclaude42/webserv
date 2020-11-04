/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:40:00 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/04 16:24:38 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include "classes.hpp"

void	run(Server serv)
{
	Response	resp;

	serv.accept();
	std::string request = serv.recv();

	// parse request
	resp.setFilename("index.html");
	resp.make();

	serv.send("RESPONSE");
	// should be resp.getResponse()

	serv.close();
}

int		main(void)
{
	Server		serv;

	serv.setup();
	while (1)
		run(serv);

	return (0);
}

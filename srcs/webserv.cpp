/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:40:00 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/08 12:51:32 by cclaude          ###   ########.fr       */
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

	req.parse(request.c_str());

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

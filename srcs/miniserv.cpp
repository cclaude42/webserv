/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniserv.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:40:00 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/01 16:54:44 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniserv.hpp"

int		setup_server(void)
{
	int					server_fd;
	struct sockaddr_in	address;

	ft_memset((char *)&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = ft_htonl(INADDR_ANY);
	address.sin_port = ft_htons(8080);

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	bind(server_fd, (struct sockaddr *)&address, sizeof(address));
	listen(server_fd, 10);
	return (server_fd);
}

void	accept_request(int server_fd)
{
	int					socket_fd;
	struct sockaddr_in	address;
	unsigned int		addrlen;
	char				buffer[50000];

	socket_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen);
	ft_memset(buffer, 0, 50000);
	recv(socket_fd, buffer, 50000, 0);
	make_header(buffer, "index.html");
	printf("Sending index.html...\n");
	send(socket_fd, buffer, ft_strlen(buffer), 0);
	close(socket_fd);
}

int		main(void)
{
	int		server_fd;

	server_fd = setup_server();
	while (1)
		accept_request(server_fd);

	return (0);
}

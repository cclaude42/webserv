/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:29:28 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/11 18:34:42 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "webserv.hpp"

class Server {
public:
	Server(void);
	Server(const Server & src);
	~Server(void);

	Server & operator=(const Server & src);

	void		setup(int port = 8080);
	void		setAddr(int port = 8080);
	void		accept(void);
	std::string	recv(void);
	void		send(std::string resp);
	void		close(void);
	void		end(void);

private:
	int					_fd;
	int					_socket;
	std::string			_request;
	struct sockaddr_in	_addr;

};

#endif

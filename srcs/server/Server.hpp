/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:29:28 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/12 21:20:44 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "webserv.hpp"
# include "ConfigServer.hpp"

class Server {
public:
	Server(const ConfigServer & config);
	Server(const Server & src);
	~Server(void);

	Server & operator=(const Server & src);

	// void		run(void);
	void		setup(void);
	void		setAddr(void);
	void		accept(void);
	std::string	recv(void);
	void		send(std::string resp);
	void		close(void);
	void		clean(void);

private:
	int					_fd;
	int					_socket;
	std::string			_request;
	struct sockaddr_in	_addr;
	ConfigServer		_config;

	Server(void);

};

#endif

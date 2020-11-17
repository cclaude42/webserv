/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:29:28 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/17 19:38:28 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "webserv.hpp"
# include "ConfigServer.hpp"
# include "Response.hpp"
# include "Request.hpp"

class Request;

class Server {
public:
	Server(const t_listen & listen);
	Server(const Server & src);
	~Server(void);

	Server & operator=(const Server & src);

	long		getFD(void);

	void		setTmpRoot(std::string root);

	void		run(void);
	void		setup(void);
	void		setAddr(void);
	void		accept(void);
	std::string	recv(void);
	void		send(std::string resp);
	void		close(void);
	void		clean(void);

private:
	long				_fd;
	long				_socket;
	std::string			_request;
	struct sockaddr_in	_addr;
	t_listen			_listen;
	std::string			_tmp_root;

	Server(void);
};

#endif

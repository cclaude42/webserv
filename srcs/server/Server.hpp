/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:29:28 by cclaude           #+#    #+#             */
/*   Updated: 2021/02/25 10:36:34 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "webserv.hpp"

# include "ConfigReader.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "Config.hpp"
# include "RequestConfig.hpp"
# include "CgiHandler.hpp"

class Server {
public:
	Server(const t_listen & listen);
	Server(const Server & src);
	~Server(void);

	Server & operator=(const Server & src);

	long		getFD(void);

	void		run(Config & conf);
	void		setup(void);
	void		setAddr(void);
	void		accept(void);
	std::string	recv(void);
	void		send(std::string resp);
	void		close(void);
	void		clean(void);

private:
	t_listen			_listen;
	long				_fd;
	long				_socket;
	struct sockaddr_in	_addr;

	Server(void);

};

#endif

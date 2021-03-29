/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:29:28 by cclaude           #+#    #+#             */
/*   Updated: 2021/03/29 15:46:43 by cclaude          ###   ########.fr       */
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

	long	getFD(void);

	int		setup(void);
	void	setAddr(void);
	long	accept(void);
	void	process(long socket, Config & conf);
	void	processChunk(long socket);
	int		recv(long socket);
	int		send(long socket);
	void	close(int socket);
	void	clean(void);

private:
	std::map<long, std::string>	_requests;
	t_listen					_listen;
	long						_fd;
	struct sockaddr_in			_addr;

	Server(void);

};

#endif

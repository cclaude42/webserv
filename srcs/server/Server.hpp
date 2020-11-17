/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:29:28 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/16 19:48:42 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "webserv.hpp"

class Request;

class Server {
public:

	Server(void);
	Server(const Server & src);
	~Server(void);

	Server & operator=(const Server & src);

	void			setup(int port = 8080);
	void			setAddr(int port = 8080);
	void			setRequest(Request& req);
	const Request&	getRequest() const;
	void			accept(void);
	std::string		recv(void);
	void			send(std::string resp);
	std::string		answer(std::string method, Request& req);
	void			close(void);
	void			end(void);

private:
	
	int					_fd;
	int					_socket;
	struct sockaddr_in	_addr;
//	std::string			_request;
	std::string			_rootPath;
	std::string			readContent(std::string path);


	//HTTP METHODS
	std::string			get_head(Request& req);
	std::string			post(Request& req);
	std::string			put(Request& req);
	std::string			ft_delete(Request& req);
	std::string			connect(Request& req);
	std::string			options(Request& req);
	std::string			trace(Request& req);
};

#endif

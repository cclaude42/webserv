/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:18:58 by cclaude           #+#    #+#             */
/*   Updated: 2021/03/24 18:04:15 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "webserv.hpp"

# include "ResponseHeader.hpp"
# include "Request.hpp"
# include "RequestConfig.hpp"
# include "CgiHandler.hpp"
# include "../config/Autoindex/AutoIndexGenerator.hpp"


class Response {
public:
	Response(void);
	Response(const Response & src);
	~Response(void);

	Response & operator=(const Response & src);

	// Getter functions
	std::string		getResponse(void);

	// Member functions
	void			call(Request & request, RequestConfig & requestConf);

	void			getMethod(Request & request, RequestConfig & requestConf);
	void			headMethod(RequestConfig & requestConf);
	void			postMethod(Request & request, RequestConfig & requestConf);
	void			putMethod(std::string content, RequestConfig & requestConf);
	void			deleteMethod(RequestConfig & requestConf);
	void			connectMethod(RequestConfig & requestConf);
	void			optionsMethod(RequestConfig & requestConf);
	void			traceMethod(Request & request, RequestConfig & requestConf);

	int				readContent(void);
	int				writeContent(std::string content);
	int				fileExists(std::string path);

private:
	std::string			_response;
	std::string			_path;
	int					_code;
	std::string			_type;
	bool				_isAutoIndex;
	t_listen			_hostPort;
};

#endif

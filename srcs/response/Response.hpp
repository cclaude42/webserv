/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:18:58 by cclaude           #+#    #+#             */
/*   Updated: 2021/03/25 10:46:25 by hbaudet          ###   ########.fr       */
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
	void			headMethod(Request & request, RequestConfig & requestConf);
	void			postMethod(Request & request, RequestConfig & requestConf);
	void			putMethod(Request & request, RequestConfig & requestConf);
	void			deleteMethod(Request & request, RequestConfig & requestConf);
	void			connectMethod(Request & request, RequestConfig & requestConf);
	void			optionsMethod(Request & request, RequestConfig & requestConf);
	void			traceMethod(Request & request, RequestConfig & requestConf);

	int				readContent(void);
	int				writeContent(std::string content);
	int				fileExists(std::string path);
	std::string		readHtml(const std::string& path);

private:
	std::string					_response;
	std::string					_path;
	int							_code;
	std::string					_type;
	bool						_isAutoIndex;
	t_listen					_hostPort;
	std::map<int, std::string>	_errorMap;

	static std::map<std::string, void (Response::*)(Request &, RequestConfig &)>	_method;
	static std::map<std::string, void (Response::*)(Request &, RequestConfig &)>	initMethods();
};

#endif

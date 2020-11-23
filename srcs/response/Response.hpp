/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:18:58 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/23 17:40:25 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include <set>

# include "webserv.hpp"

# include "ResponseHeader.hpp"
# include "Request.hpp"
# include "RequestConfig.hpp"


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
	void			fillContent(std::string);
	void			getMethod(RequestConfig & requestConf);
	void			headMethod(RequestConfig & requestConf);
	void			postMethod(void);
	void			putMethod(void);
	void			deleteMethod(void);
	void			connectMethod(void);
	void			optionsMethod(void);
	void			traceMethod(void);



private:
	std::string			_response;
	std::string			_content;
	int					_code;
};

//HTP Methods
std::string		get(Request& req, RequestConfig& conf);
std::string		head(Request& req, RequestConfig& conf);
std::string		post(Request& req, RequestConfig& conf);
std::string		put(Request& req, RequestConfig& conf);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:18:58 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/19 15:22:19 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

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

private:
	Request &			_request;
	RequestConfig &		_requestConf;
	std::string			_response;
	std::string			_content;
	int					_code;
};

#endif

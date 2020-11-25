/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:18:58 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/25 17:04:54 by cclaude          ###   ########.fr       */
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

	void			getMethod(void);
	void			headMethod(void);
	void			postMethod(void);
	void			putMethod(void);
	void			deleteMethod(void);
	void			connectMethod(void);
	void			optionsMethod(void);
	void			traceMethod(Request & request);

	int				readContent(void);
	int				writeContent(void);
	int				fileExists(std::string path);

private:
	std::string			_response;
	std::string			_content;
	std::string			_path;
	int					_code;
};

#endif

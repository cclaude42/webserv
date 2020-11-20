/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:18:58 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/20 17:21:14 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include <set>

# include "webserv.hpp"

# include "ResponseHeader.hpp"
# include "RequestConfig.hpp"
# include "Request.hpp"

class Response {
public:
	Response(void);
	Response(const Response & src);
	~Response(void);

	Response & operator=(const Response & src);

	// Setter functions
	void			setFilename(std::string filename);

	// Getter functions
	std::string		getResponse(void);

	// Member functions
	void			make(Request& req, RequestConfig& conf);
	void			fillContent(void);



private:
	std::string			_response;
	std::string			_content;
	std::string			_filename;
	int					_code;
};

//HTP Methods
std::string		get(Request& req, RequestConfig& conf);
std::string		head(Request& req, RequestConfig& conf);
std::string		post(Request& req, RequestConfig& conf);
std::string		put(Request& req, RequestConfig& conf);

#endif

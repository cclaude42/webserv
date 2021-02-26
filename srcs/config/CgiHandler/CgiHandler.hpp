/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 15:08:57 by frthierr          #+#    #+#             */
/*   Updated: 2021/02/25 10:36:38 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HANDLER_HPP

# define CGI_HANDLER_HPP


# include "webserv.hpp"
# include "Config.hpp"
# include "Request.hpp"
# include "webserv.hpp"
# include "RequestConfig.hpp"

class CgiHandler {
	public:
		CgiHandler(Request &request, RequestConfig &config); // sets up env according to the request
		CgiHandler(CgiHandler const &src);
		virtual ~CgiHandler(void);

		CgiHandler   	&operator=(CgiHandler const &src);
		std::string		executeCgi(std::string scriptName) const;	// executes cgi and returns body
	private:
		CgiHandler(void);
		void								_initEnv(Request &request, RequestConfig &config);
		char								**_getEnvAsCstrArray() const;
		std::map<std::string, std::string>	_env;
		std::string							_body;
};

// ENV TO IMPLEMENT
// AUTH_TYPE
// CONTENT_LENGTH
// CONTENT_TYPE
// GATEWAY_INTERFACE
// PATH_INFO
// PATH_TRANSLATED
// QUERY_STRING˜

#endif

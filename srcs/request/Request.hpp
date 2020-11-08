/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:27:33 by hbaudet           #+#    #+#             */
/*   Updated: 2020/11/08 12:58:34 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "webserv.hpp"

#ifdef DEBUG
# define PRINT 1
#else
# define PRINT 0
#endif

/* USAGE :

-	char * constructor turns the output of a read call into a map of strings

-	Method and version are stored separtely in a string.
	Any version other than 1.0 or 1.1 is considered invalid
	if the method or the HTTP version is invalid, ret is set to 400 (BAD Request)
	otherwise it stays at its default 200 value

-	Implemented headers are parsed as follows : "KEY:[OWS]VALUE[OWS]"
	and stored in a map<string, string> as (KEY, VALUE)
	OWS = optionnal whitespace

-	An empty line ended by CRLF is considered to be the end of the header section
	anything that follows is stored in a single string labelled "_body"

-	Calling 'reset' and 'parse' methods would have the same effect as
	calling the char * constructor

*/


class Request
{
		private:
			std::string							_method;
			std::string							_version;
			std::map<std::string, std::string>	_headers;
			int									_ret;
			std::string							_body;

			/*** PARSING ***/
			void	readFirstLine(char *line);
			void	checkMethod();

			/*** AVAILABLE HTTP METHODS ***/
			static	std::vector<std::string>	methods;

		public:
			Request();
			Request(const char *str);
			Request(const Request&);
			~Request();
			Request&	operator=(const Request&);

			/*** GETTERS ***/
			const	std::map<std::string, std::string>&	getHeaders() const;
			const	std::string&						getMethod() const;
			const	std::string&						getVersion() const;
			int											getRet() const;
			const	std::string&						getBody() const;

			/*** SETTERS **/
//			void	setHeader(const std::string& key, const std::string& value); //not needed as of now
			void	setBody(char **line, int i);

			/*** UTILS ****/
			void	displayHeaders();
			void	resetHeaders();
			int		parse(const char *str);
};

std::ostream&	operator<<(std::ostream& os, const Request& re);

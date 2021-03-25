/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:27:33 by hbaudet           #+#    #+#             */
/*   Updated: 2021/03/25 21:19:35 by hbaudet          ###   ########.fr       */
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
			std::string									_method;
			std::string									_version;
			std::map<std::string, std::string>			_headers;
			std::map<std::string, std::string>			_env_for_cgi;
			int											_ret;
			std::string::const_iterator					_bodBeg;
			std::string::const_iterator					_bodEnd;
			std::string									_body;
			int											_port;
			std::string									_path;
			std::string									_query;
			std::string									_raw;
			std::list<std::pair<std::string, float> >	_lang;

			/*** PARSING ***/
			int			readFirstLine(const std::string& line);
			int			readPath(const std::string& line, size_t i);
			int			readVersion(const std::string& line, size_t i);
			int			checkMethod();
			int			checkPort();
			std::string	findQuery(const std::string& path);
			std::string formatHeaderForCGI(std::string& key);
			std::string	nextLine(const std::string &str, size_t& i);
			void		setLang();
			void		queryToEnv();


			/*** AVAILABLE HTTP METHODS ***/
			static	std::vector<std::string>	methods;

		public:
			Request();
			Request(const std::string& str);
			Request(const Request&);
			~Request();
			Request&	operator=(const Request&);

			/*** GETTERS ***/
			const	std::map<std::string, std::string>&			getHeaders() const;
			const	std::map<std::string, std::string>&			getEnv() const;
			const	std::string&								getMethod() const;
			const	std::string&								getVersion() const;
			int													getRet() const;
			const	std::string&								getBody() const;
			int													getPort() const;
			const std::string&									getPath() const;
			const std::string&									getQuery() const;
			const std::string&									getRaw() const;
			const std::list<std::pair<std::string, float> >&	getLang() const;

			/*** SETTERS **/
		//	void	setHeader(const std::string& key, const std::string& value);
													//not needed as of now
			void	setBody(const std::string& line);
			void	setRet(int);
			void	setMethod(const std::string &method);

			/*** UTILS ****/
			int		parse(const std::string& str);
			void	resetHeaders();
			void	stripAll();
			void	displayHeaders() const;
			static std::vector<std::string>		initMethods();

};

std::ostream&	operator<<(std::ostream& os, const Request& re);

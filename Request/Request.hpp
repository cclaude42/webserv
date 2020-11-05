/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:27:33 by hbaudet           #+#    #+#             */
/*   Updated: 2020/11/05 18:09:02 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

extern "C" {
#include "libft.h"
}

#include "Strings.hpp"

#ifdef DEBUG
# define PRINT 1
#else
# define PRINT 0
#endif

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

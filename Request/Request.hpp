/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:27:33 by hbaudet           #+#    #+#             */
/*   Updated: 2020/11/05 16:38:30 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>
#include <map>

extern "C" {
#include "libft.h"
}

#ifdef DEBUG
# define PRINT 1
#else
# define PRINT 0
#endif

class Request
{
		private:
			std::string							method;
			std::string							version;
			std::map<std::string, std::string>	headers;
			int									ret;

			void	readFirstLine(char *line);

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
			const	int									getRet() const;

			/*** SETTERS **/
			void	setHeader(const std::string& key, const std::string& value);
			
			/*** UTILS ****/
			void	displayHeaders();
			void	resetHeaders();
			int		parse(const char *str);
};

std::ostream&	operator<<(std::ostream& os, const Request& re);

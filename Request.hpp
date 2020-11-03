/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:27:33 by hbaudet           #+#    #+#             */
/*   Updated: 2020/11/03 23:33:36 by hbaudet          ###   ########.fr       */
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
			std::map<std::string, std::string>	headers;
			int									ret;

		public:
			Request();
			Request(const char *str);
			Request(const Request&);
			~Request();
			Request&	operator=(const Request&);

			/*** GETTERS ***/
			const std::map<std::string, std::string>&	getHeaders() const;

			/*** SETTERS **/
			void	setHeader(const std::string& key, const std::string& value);
			
			/*** UTILS ****/
			void	displayHeaders();
			void	resetHeaders();
			int		parse(const char *str);
};

std::ostream&	operator<<(std::ostream& os, const Request& re);

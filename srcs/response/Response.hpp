/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:18:58 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/04 16:22:25 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "webserv.hpp"
# include "ResponseHeader.hpp"

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
	void			make(void);
	void			fillContent(void);

private:
	std::string		_response;
	ResponseHeader	_header;
	std::string		_content;
	std::string		_filename;
};

#endif

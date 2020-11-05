/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseHeader.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 15:17:39 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/04 16:06:46 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSEHEADER_HPP
# define RESPONSEHEADER_HPP

# include "webserv.hpp"

class ResponseHeader {
public:
	ResponseHeader(void);
	ResponseHeader(const ResponseHeader & src);
	~ResponseHeader(void);

	ResponseHeader & operator=(const ResponseHeader & src);

	// Setter functions
	void			setAllow(std::string str);
	void			setContentLanguage(std::string str);
	void			setContentLength(std::string str);
	void			setContentLocation(std::string str);
	void			setContentType(std::string str);
	void			setDate(std::string str);
	void			setLastModified(std::string str);
	void			setLocation(std::string str);
	void			setRetryAfter(std::string str);
	void			setServer(std::string str);
	void			setTransferEncoding(std::string str);
	void			setWwwAuthenticate(std::string str);

	// Getter functions
	std::string		getAllow(void);
	std::string		getContentLanguage(void);
	std::string		getContentLength(void);
	std::string		getContentLocation(void);
	std::string		getContentType(void);
	std::string		getDate(void);
	std::string		getLastModified(void);
	std::string		getLocation(void);
	std::string		getRetryAfter(void);
	std::string		getServer(void);
	std::string		getTransferEncoding(void);
	std::string		getWwwAuthenticate(void);

	// Member functions
	std::string		getHeader(void);

private:
	std::string		_allow;
	std::string		_contentLanguage;
	std::string		_contentLength;
	std::string		_contentLocation;
	std::string		_contentType;
	std::string		_date;
	std::string		_lastModified;
	std::string		_location;
	std::string		_retryAfter;
	std::string		_server;
	std::string		_transferEncoding;
	std::string		_wwwAuthenticate;
};

#endif

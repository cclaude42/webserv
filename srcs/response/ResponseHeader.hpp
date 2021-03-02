/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseHeader.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 15:17:39 by cclaude           #+#    #+#             */
/*   Updated: 2021/03/02 11:37:07 by hbaudet          ###   ########.fr       */
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
	void			setAllow(std::set<std::string> methods);
	void			setAllow(void);
	void			setContentLanguage(const std::string& content);
	void			setContentLength(int size);
	void			setContentLocation(const std::string& path, int code);
	void			setContentType(std::string type);
	void			setDate(void);
	void			setLastModified(const std::string& path);
	void			setLocation(int code, const std::string& redirect);
	void			setRetryAfter(int code, int sec);
	void			setServer(void);
	void			setTransferEncoding(void);
	void			setWwwAuthenticate(int code);

	// Member functions
	std::string		getHeader(const std::string& content, const std::string& path, int code, const std::string& contentLocation);
	std::string		notAllowed(std::set<std::string> methods, const std::string& path);
	std::string		writeHeader(void);
	void			setValues(const std::string& content, const std::string& path, int code, const std::string& contentLocation);
	void			resetValues(void);
	std::string		getStatusMessage(int code);

private:
	std::string				_allow;
	std::string				_contentLanguage;
	std::string				_contentLength;
	std::string				_contentLocation;
	std::string				_contentType;
	std::string				_date;
	std::string				_lastModified;
	std::string				_location;
	std::string				_retryAfter;
	std::string				_server;
	std::string				_transferEncoding;
	std::string				_wwwAuthenticate;
};

#endif

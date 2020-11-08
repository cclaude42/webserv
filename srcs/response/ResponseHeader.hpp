/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseHeader.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 15:17:39 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/07 18:45:22 by cclaude          ###   ########.fr       */
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
	void			setAllow(std::string cmd);
	void			setContentLanguage(std::string lang);
	void			setContentLength(int size);
	void			setContentLocation(std::string path);
	void			setContentType(std::string type);
	void			setDate(void);
	void			setLastModified(std::string path);
	void			setLocation(int code, std::string redirect);
	void			setRetryAfter(int code, int sec);
	void			setServer(void);
	void			setTransferEncoding(void);
	void			setWwwAuthenticate(int code);

	// Member functions
	std::string		getHeader(std::string content, std::string filename, int code);
	std::string		writeHeader(void);
	void			setValues(std::string content, std::string filename, int code);
	void			resetValues(void);
	std::string		getStatusMessage(int code);

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseMethods.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:13:39 by hbaudet           #+#    #+#             */
/*   Updated: 2020/11/20 18:00:19 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

Accept-Charsets		Request only
Accept-Language		Request only
Allow				Set in dispatch
Authorization		Request only
Content-Language	nginx does not seem to use it in GET; Parse file to set them up?
Content-Length		Set in ResponseHeader
Content-Location	After content negociation/CGI => full path after content negociation
Content-Type		Set un ResponseHeader
Date				Set un ResponseHeader
Host				Set un ResponseHeader
Last-Modified		Set un ResponseHeader
Location			In case of redirect, set in ResponseHeader
Referer				Request only, useless for this project ?
Retry-After			Set in ResponseHeader
Server				Set in ResponseHeader
Transfer-Encoding	No encoding and problem solved? Check with cgi though
User-Agent			Request only, useless for this project ?
WWW-Authenticate	Only for 401 Unauthorized


*/


#include "Response.hpp"

std::string		get(Request& req, RequestConfig& conf)
{
	std::string			ret;

	ret = head(req, conf);
	ret += req.getBody();
	ret += "\r\n";
	return ret;
}

std::string		head(Request& req, RequestConfig& conf)
{
	ResponseHeader		rh;
	std::fstream		file;
	std::stringstream	stream;

	std::cout << "in HEAD, path : " << conf.getPath() << '\n';
	file.open(conf.getPath());
	if (file.fail()) //can't tell the difference between file does not exist (404) or file can't be oppenned (403)
	{
		file.close();
		req.setRet(404);
		conf.setPath(404);
		return get(req, conf);
	}
	stream << file.rdbuf();
	if (file.bad())
	{
		file.close();
		// implement autoindex here ?
		req.setRet(403);
		conf.setPath(403);
		std::cout << "path after 403 : " << conf.getPath() << '\n';
		return get(req, conf);
	}
	file.close();
	req.setBody(stream.str());
	return (rh.getHeader(stream.str(), conf.getPath(), req.getRet()));
}

std::string		post(Request& req, RequestConfig& conf)
{
	struct stat buff;
	ResponseHeader	rh;

	// std::cout << conf.getPath() << '\n';

	// Do CGI stuff
		// random stuff to do while CGI not implemented
			std::stringstream	content;
			std::fstream		file;

			req.setBody({"THIS IS A TEST", "ANOTHER TEST STRING", "LAST TEST STRING"}, 0);
			if (!(stat(conf.getPath().c_str(), &buff)))
				req.setRet(201);
			file.open("/home/hannibal/Documents/Cursus42/webserv_v2/root/hbaudet_test" + conf.getPath(), std::ios_base::app);
			file << req.getBody();
			content << file.rdbuf();
			file.close();


	return rh.getHeader(content.str(), conf.getPath(), req.getRet());
}

std::string		put(Request& req, RequestConfig& conf)
{
	ResponseHeader		rh;
	std::fstream		file;

	file.open(conf.getPath(), std::fstream::trunc);
	if (file.fail())
		file.open(conf.getPath(), std::fstream::out | std::fstream::trunc);
	file << req.getBody();

	if (file.fail())
	{
		req.setRet(405);
		conf.setPath(405);
		return (get(req, conf));
	}
	file.close();
	return (rh.getHeader(req.getBody(), conf.getPath(), req.getRet()));
}

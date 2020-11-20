/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:18:58 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/20 17:36:22 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

// Global map to call HTTP methods, could/should be part of Response ?

std::map<std::string, std::string (*)(Request& req, RequestConfig& conf)> g_map = {
	{"GET", get},
	{"HEAD", head},
	{"POST", post},
	{"PUT", put}
};

// Tests validity, and calls the right method

static std::string	dispatch(Request& req, RequestConfig& conf)
{
	std::string		ret = "";

	std::cout << "in dispatch, req.getPath() : " << req.getPath() << '\n';
	conf.setPath("/home/hannibal/Documents/Cursus42/webserv_v2/root" + req.getPath()); // to be deleted when path is set properly in RequestConfig

	// std::fstream	test;
	// std::fstream	test2;

	// test.open("/home/hannibal/Documents/Cursus42/webserv_v2/exists.txt");
	// if (test.good())
	// 	std::cout << "test exists\n";
	// test2.open("/home/hannibal/Documents/Cursus42/webserv_v2/new.txt");
	// if (test2.good())
	// 	std::cout << "test2 exists\n";
	// else
	// {
	// 	test2.open("/home/hannibal/Documents/Cursus42/webserv_v2/new.txt", std::fstream::out | std::fstream::trunc);
	// 	std::cout << "test2 does not exist\n";
	// }

	// test << "some random stuff for you";
	// test2 << "this is something else\n";

	// test.close();
	// test2.close();

	// std::cout << "end of file testing\n";


	if (req.getRet() != 200)
	{
		//change path in RequestConfig to according error page
		std::cout << "dispatch found an error\n";
		ret += get(req, conf); //send error page
	}
	/* allowedMethods not fully implemented yet
	else if (!(conf.getAllowedMethods().count(req.getMethod())))
	{
		std::cout << "Method not allowed\n";
		//change path in RequestConfig to according error page
		req.setRet(405);
		//set Allow header accordingly
		ret += get(req, conf);
	}
	*/
	else
		ret += g_map[req.getMethod()](req, conf);
	return ret;
}

// Member functions

void			Response::make(Request& req, RequestConfig& conf)
{
	ResponseHeader	head;

	fillContent();
	// Set header accordingly

	_response = dispatch(req, conf);
	
	// _response = head.getHeader(_content, _filename, _code) + _content;
}

void			Response::fillContent(void)
{
	int		fd = open(_filename.c_str(), O_RDONLY);
	char	buffer[4096];
	int		ret = 4095;

	_content = "";
	while (ret == 4095)
	{
		ft_memset(buffer, 0, 4096);
		ret = read(fd, buffer, 4095);
		_content += std::string(buffer);
	}

	close(fd);
}

// Setter functions

void			Response::setFilename(std::string filename)
{
	_filename = filename;
}

// Getter functions

std::string		Response::getResponse(void)
{
	return (_response);
}

// Overloaders

Response & Response::operator=(const Response & src)
{
	(void)src;
	return (*this);
}

// Constructors and destructors

Response::Response(void)
{
	_code = 200;
}

Response::Response(const Response & src)
{
	(void)src;
}

Response::~Response(void)
{
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:18:58 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/25 17:04:45 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

// Global map to call HTTP methods, could/should be part of Response ?

// std::map<std::string, std::string (*)(Request& req, RequestConfig& conf)> g_map = {
// 	{"GET", getMethod},
// 	{"HEAD", headMethod},
// 	{"POST", postMethod},
// 	{"PUT", putMethod}
// };

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

// void			Response::call(Request& req, RequestConfig& conf)
// {
// 	ResponseHeader	head;
//
// 	fillContent(conf.getPath());
// 	// Set header accordingly
//
// 	_response = dispatch(req, conf);
//
// 	// _response = head.getHeader(_content, _filename, _code) + _content;
// }

void			Response::call(Request & request, RequestConfig & requestConf)
{
	_code = 200;
	_path = requestConf.getPath();

	if (request.getMethod() == "GET")
		getMethod();
	else if (request.getMethod() == "HEAD")
		headMethod();
	else if (request.getMethod() == "POST")
		postMethod();
	else if (request.getMethod() == "PUT")
		putMethod();
	else if (request.getMethod() == "DELETE")
		deleteMethod();
	else if (request.getMethod() == "CONNECT")
		connectMethod();
	else if (request.getMethod() == "OPTIONS")
		optionsMethod();
	else if (request.getMethod() == "TRACE")
		traceMethod(request);
}

// Methods

void			Response::getMethod(void)
{
	ResponseHeader	head;

	_code = readContent();
	_response = head.getHeader(_content, _path, _code) + _content;
}

void			Response::headMethod(void)
{
	ResponseHeader	head;

	_code = readContent();
	_response = head.getHeader(_content, _path, _code);
}

void			Response::postMethod(void)
{
	// NEED CGI ?
}

void			Response::putMethod(void)
{
	ResponseHeader	head;

	_code = writeContent();
	_response = head.getHeader(_content, _path, _code);
}

void			Response::deleteMethod(void)
{
	ResponseHeader	head;

	if (fileExists(_path))
	{
		if (remove(_path) == 0)
			_code = 204;
		else
			_code = 403;
	}
	else
		_code = 404;

	_response = head.getHeader(_content, _path, _code);
}

void			Response::connectMethod(void)
{
	// LINK TO OTHER SERVER ?
}

void			Response::optionsMethod(void)
{
	ResponseHeader	head;

	_code = readContent();
	_response = head.getHeader(_content, _path, _code);

}

void			Response::traceMethod(Request & request)
{
	_response = request.getRaw();
}

// Utils

int				Response::readContent(void)
{
	std::ifstream	file;

	_content = "";

	if (fileExists(_path) == 0)
		return (404);

	file.open(_path, std::ifstream::in);
	if (file.is_open() == false)
		return (403);

	_content << file;
	file.close();

	return (200);
}

int				Response::writeContent(void)
{
	std::ofstream	file;
	int				ret = 204;

	if (fileExists(_path) == 0)
		ret = 201;

	file.open(_path, std::ofstream::out | std::ofstream::trunc);

	if (file.is_open() == false)
		return (403);

	file << _content;
	file.close();

	return (ret);
}

int				Response::fileExists(std::string path)
{
	struct stat		stats;

	if (stat(_path.c_str(), &stats) == 0)
		return (1);
	return (0);
}

// Getter functions

std::string		Response::getResponse(void)
{
	return (_response);
}

// Overloaders

Response & Response::operator=(const Response & src)
{
	_response = src._response;
	_content = src._content;
	_path = src._path;
	_code = src._code;
	return (*this);
}

// Constructors and destructors

Response::Response(void)
{
}

Response::Response(const Response & src)
{
	*this = src;
}

Response::~Response(void)
{
}

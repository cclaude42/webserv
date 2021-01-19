/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 15:07:29 by frthierr          #+#    #+#             */
/*   Updated: 2021/01/19 11:19:07 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CgiHandler.hpp"

CgiHandler::CgiHandler(Request &request, RequestConfig &config):
_body(request.getBody())
{
	this->_initEnv(request, config);
}

CgiHandler::CgiHandler(CgiHandler const &src) {
	if (this != &src) {
		this->_body = src._body;
		this->_env = src._env;
	}
	return ;
}

CgiHandler::~CgiHandler(void) {
	return ;
}

CgiHandler	&CgiHandler::operator=(CgiHandler const &src) {
	if (this != &src) {
		this->_body = src._body;
		this->_env = src._env;
	}
	return *this;
}

void		CgiHandler::_initEnv(Request &request, RequestConfig &config) {
	// this->_env["AUTH_TYPE"] = ; // 	header field of http request that hannibal needs to add
	this->_env["CONTENT_LENGTH"] = this->_body.length();

	std::string	method = request.getMethod();
	if (method == "PUT" || method == "POST") {
		this->_env["CONTENT_TYPE"] = method;		
	}
	else
		this->_env["CONTENT_TYPE"] = "";
	
	this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	this->_env["PATH_INFO"] = request.getPath();
	this->_env["PATH_TRANSLATED"] = request.getPath();
	this->_env["QUERY_STRING"] = request.getQuerry();
	// this->_env["REMOTE_ADDR"] = ;
	// this->_env["REMOTE_IDENT"] = ;
	// this->_env["REMOTE_USER"] = ;
	this->_env["REQUEST_METHOD"] = request.getMethod();
	this->_env["REQUEST_URI"] = request.getPath();
	// this->_env["SCRIPT_NAME"] = ;
	
	// std::string	serverName = request.getHost(); // hannibal need to add host field getter function
	// if (serverName == "")
	// 	this->_env["SERVER_NAME"] = config.getHostPort().host;
	// else
	// 	this->_env["SERVER_NAME"] = serverName;
	this->_env["SERVER_PORT"] = config.getHostPort().port;
	this->_env["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->_env["SERVER_SOFTWARE"] = "WEEBSERV";

}

char					**CgiHandler::_getEnvAsCstrArray() const {
	char	**env = new char*[this->_env.size() + 1];
	int	j = 0;
	for (std::map<std::string, std::string>::const_iterator i = this->_env.begin(); i != this->_env.end(); i++) {
		std::string	element = i->first + "=" + i->second;
		env[j] = ft_strdup(element.c_str());
	}
	env[j] = NULL;
	return env;
}

std::string		CgiHandler::executeCgi(std::string scriptName) const {
pid_t	id;
	int		fds[2];
	int		saveStdin;
	int		saveStdout;
	int		status;
	ssize_t	ret;
	char	buffer[512] = {0};
	std::string	io;
	char		**env;

	// GETTING ENV VARIABLES
	try {
		env = this->_getEnvAsCstrArray();
	}
	catch (std::bad_alloc &e) {
		std::cout << e.what() << std::endl;
	}
	// SAVING STDIN AND STDOUT IN ORDER TO TURN THEM BACK TO NORMAL LATER
	saveStdin = dup(STDIN_FILENO);
	saveStdout = dup(STDOUT_FILENO);
	
	pipe(fds);
	id = fork();
	
	// REPLACING STDIN AND STDOUT WITH PIPE
	dup2(fds[0], STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
	if (!id) {	
		execve(scriptName.c_str(), NULL, env);
		close(fds[0]);
		close(fds[1]);
		return 0;
	}
	else
	{
		// WAITING FOR THE CHILD PROCESS TO FINISH
		waitpid(id, &status, 0);
		// READING CHILD PROCESS' OUTPUT
		do {
			ret = read(fds[0], buffer, 512);
			for (int i = 0; i < ret ; i++)
				io += buffer[i];
		} while (ret == 512);
		// RESETING STDIN AND STDOUT BACK TO NORMAL
		dup2(saveStdin, STDIN_FILENO);
		dup2(saveStdout, STDOUT_FILENO);
		
		close(fds[0]);
		close(fds[1]);
		//	RESET BACK TO NORMAL
		std::cout << io << std::endl;
		return 0;		
	}
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 15:07:29 by frthierr          #+#    #+#             */
/*   Updated: 2021/03/01 16:13:35 by hbaudet          ###   ########.fr       */
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
	std::map<std::string, std::string>	headers = request.getHeaders();
	if (headers.find("auth-scheme") != headers.end())
		this->_env["AUTH_TYPE"] = headers["Authorization"]; // 	header field of http request that hannibal needs to add

	this->_env["CONTENT_LENGTH"] = this->_body.length();

	// std::string	method = request.getMethod();

	// if (method == "PUT" || method == "POST") {
	// 	this->_env["CONTENT_TYPE"] = method;
	// }
	// else
	// 	this->_env["CONTENT_TYPE"] = "";
	this->_env["CONTENT_TYPE"] = headers["Content-Type"];
	this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	this->_env["PATH_INFO"] = request.getPath(); //might need some change, using config path/contentLocation
	this->_env["PATH_TRANSLATED"] = request.getPath(); //might need some change, using config path/contentLocation
	this->_env["QUERY_STRING"] = request.getQuerry();
	this->_env["REMOTE_ADDR"] = config.getHostPort().host;
	this->_env["REMOTE_IDENT"] = headers["Authorization"];
	this->_env["REMOTE_USER"] = headers["Authorization"];
	this->_env["REQUEST_METHOD"] = request.getMethod();
	this->_env["REQUEST_URI"] = request.getPath();
	this->_env["SCRIPT_NAME"] = "default-cgi-script";

	if (headers.find("hostname") != headers.end())
		this->_env["SERVER_NAME"] = headers["hostname"];
	else
		this->_env["SERVER_NAME"] = this->_env["REMOTE_ADDR"];
	this->_env["SERVER_PORT"] = to_string(config.getHostPort().port);
	this->_env["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->_env["SERVER_SOFTWARE"] = "Weebserv/1.0";

}

char					**CgiHandler::_getEnvAsCstrArray() const {
	char	**env = new char*[this->_env.size() + 1];
	int	j = 0;
	for (std::map<std::string, std::string>::const_iterator i = this->_env.begin(); i != this->_env.end(); i++) {
		std::string	element = i->first + "=" + i->second;
		env[j] = ft_strdup(element.c_str());
		j++;
	}
	env[j] = NULL;
	return env;
}

std::string		CgiHandler::executeCgi(const std::string& scriptName) {
	pid_t	id;
	int		fds[4];
	int		saveStdin;
	int		saveStdout;
	int		status;
	ssize_t	ret;
	char	buffer[512] = {0};
	std::string	io;
	char		**env;

	// GETTING ENV VARIABLES
	this->_env["SCRIPT_NAME"] = scriptName;
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
	pipe(fds + 2);
	id = fork();

	// REPLACING STDIN AND STDOUT WITH PIPE
	if (!id) {
		dup2(fds[2], STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		char * const *nll = NULL;

		execve(scriptName.c_str(), nll, env);
		dup2(saveStdout, STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		close(fds[2]);
		close(fds[3]);
		return "cgi execve crashed, oopsy\n";
	}
	else
	{
		dup2(fds[0], STDIN_FILENO);
		dup2(fds[3], STDOUT_FILENO);
		// SEND RQUEST BODY THROUGH PIPE TO CGI
		std::cout << _body << "\r\n";
		// WAITING FOR THE CHILD PROCESS TO FINISH
		waitpid(id, &status, 0);
		// READING CHILD PROCESS' OUTPUT
		do {
			ret = read(STDIN_FILENO, buffer, 512);
			for (int i = 0; i < ret ; i++)
				io += buffer[i];
		} while (ret == 512);
		// RESETING STDIN AND STDOUT BACK TO NORMAL
		dup2(saveStdin, STDIN_FILENO);
		dup2(saveStdout, STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		close(fds[2]);
		close(fds[3]);
		//	RESET BACK TO NORMAL
		for (int j = 0; env[j]; j++)
			free(env[j]);
		delete[] env;
		return io;
	}
	close(fds[0]);
	close(fds[1]);
	return "-error-";
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 15:07:29 by frthierr          #+#    #+#             */
/*   Updated: 2021/03/11 14:33:36 by cclaude          ###   ########.fr       */
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
	if (headers.find("Auth-Scheme") != headers.end() && headers["Auth-Scheme"] != "")
		this->_env["AUTH_TYPE"] = headers["Authorization"];

	this->_env["REDIRECT_STATUS"] = "200"; //Security needed to execute php-cgi
	this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	this->_env["SCRIPT_NAME"] = config.getPath();
	this->_env["SCRIPT_FILENAME"] = config.getPath();
	// this->_env["SCRIPT_NAME"] = "default-cgi-script";
	this->_env["REQUEST_METHOD"] = request.getMethod();
	this->_env["CONTENT_LENGTH"] = to_string(this->_body.length());
	this->_env["CONTENT_TYPE"] = headers["Content-Type"];
	this->_env["PATH_INFO"] = config.getPath(); //might need some change, using config path/contentLocation
	// this->_env["PATH_TRANSLATED"] = request.getPath(); //might need some change, using config path/contentLocation
	this->_env["QUERY_STRING"] = request.getQuery();
	// this->_env["REMOTEaddr"] = to_string(config.getHostPort().host);
	// this->_env["REMOTE_IDENT"] = headers["Authorization"];
	// this->_env["REMOTE_USER"] = headers["Authorization"];
	// this->_env["REQUEST_URI"] = request.getPath() + request.getQuery();

	if (headers.find("Hostname") != headers.end())
		this->_env["SERVER_NAME"] = headers["Hostname"];
	// else
		// this->_env["SERVER_NAME"] = this->_env["REMOTEaddr"];
	// this->_env["SERVER_PORT"] = to_string(config.getHostPort().port);
	this->_env["SERVER_PROTOCOL"] = "HTTP/1.1";
	// this->_env["SERVER_SOFTWARE"] = "Weebserv/1.0";

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

int				CgiHandler::_connectSocket(unsigned int port)
{
	long				fd;
	struct sockaddr_in	addr;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
		return (-1);
	memset((char *)&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);
	if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		return (-1);
	return (fd);
}

int				CgiHandler::_getSocket(unsigned int port)
{
	long				fd;
	struct sockaddr_in	addr;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
		return (-1);
	memset((char *)&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);
	if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		return (-1);
	if (listen(fd, 1) == -1)
		return (-1);
	return (fd);
}

std::string		CgiHandler::executeCgi(const std::string& scriptName) {
	pid_t		pid;
	int			saveStdin;
	int			saveStdout;
	char		**env;
	std::string	newBody;

	// GETTING ENV VARIABLES
	// this->_env["SCRIPT_NAME"] = scriptName;
	// std::cout << "Running CGI with : " << scriptName << '\n';
	try {
		env = this->_getEnvAsCstrArray();
	}
	catch (std::bad_alloc &e) {
		std::cout << e.what() << std::endl;
	}

	// SAVING STDIN AND STDOUT IN ORDER TO TURN THEM BACK TO NORMAL LATER
	saveStdin = dup(STDIN_FILENO);
	saveStdout = dup(STDOUT_FILENO);

	long			fdIn = -1;
	long			fdOut = -1;
	long			sockIn;
	long			sockOut;
	unsigned int	portIn;
	unsigned int	portOut;

	// std::cerr << "Before fdIn setup" << std::endl;

	portIn = 3456;
	while (fdIn == -1)
		fdIn = _getSocket(++portIn);

			// std::cerr << "Before fdOut setup" << std::endl;
	portOut = portIn;
	while (fdOut == -1)
		fdOut = _getSocket(++portOut);

			// std::cerr << "Before fork" << std::endl;
	pid = fork();

	if (pid == 0)
	{
		char * const * nll = NULL;
		struct sockaddr_in	addr;
		unsigned int		addrlen;

			// std::cerr << "{exec} before accepting in" << std::endl;
		sockIn = accept(fdIn, (struct sockaddr *)&addr, (socklen_t *)&addrlen);
		if (sockIn == -1)
			std::cerr << RED << "Could not create socket. (Pipe in, exec side)" << RESET << std::endl;
		fcntl(sockIn, F_SETFL, O_NONBLOCK);

			// std::cerr << "{exec} before accepting out" << std::endl;
		sockOut = accept(fdOut, (struct sockaddr *)&addr, (socklen_t *)&addrlen);
		if (sockOut == -1)
			std::cerr << RED << "Could not create socket. (Pipe out, exec side)" << RESET << std::endl;
		fcntl(sockOut, F_SETFL, O_NONBLOCK);

			// std::cerr << "{exec} before duping" << std::endl;
		dup2(sockIn, STDIN_FILENO);
		dup2(sockOut, STDOUT_FILENO);
		// std::cerr << "{exec} before execve" << std::endl;

		execve(scriptName.c_str(), nll, env);
		// (void)scriptName;
		// execve("../webcgi", nll, env);

		std::cerr << "Execve crashed, errno : " << errno << "\n";

		close(sockIn);
		close(sockOut);
		close(fdIn);
		close(fdOut);

		exit(0);
	}
	else
	{
		//REMOVE THIS v
		std::string		tmp;
		while (tmp.size() < 100000000)
			tmp += "n";
		//REMOVE THIS ^

		char	buffer[CGI_BUFSIZE];
		int		ret = 1;

		// std::cerr << "{send} before connecting in" << std::endl;
		sockIn = _connectSocket(portIn);
		if (sockIn == -1)
			std::cerr << RED << "Could not create socket. (Pipe in, sending side)" << RESET << std::endl;

		// std::cerr << "{send} before connecting out" << std::endl;
		sockOut = _connectSocket(portOut);
		if (sockOut == -1)
			std::cerr << RED << "Could not create socket. (Pipe out, sending side)" << RESET << std::endl;

		// std::cerr << "{send} before sending" << std::endl;
		send(sockIn, tmp.c_str(), tmp.size(), 0);
		close(sockIn);

		// std::cerr << "{send} before waitpid" << std::endl;
		waitpid(-1, NULL, 0);

		// std::cerr << "{send} before recving" << std::endl;
		while (ret > 0)
		{
			ft_memset(buffer, 0, CGI_BUFSIZE);
			ret = recv(sockOut, buffer, CGI_BUFSIZE - 1, 0);
			newBody += buffer;
		}

		close(sockOut);
	}

	close(fdIn);
	close(fdOut);
	dup2(saveStdin, STDIN_FILENO);
	dup2(saveStdout, STDOUT_FILENO);

	return (newBody);
}

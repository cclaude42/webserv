// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#include <iostream>
#include <fstream>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

int		choose_port(void)
{
	std::string		choice;

	std::cout << YELLOW << "Choose PORT :" << std::endl;
	std::cout << "(a) 8000" << std::endl;
	std::cout << "(b) 8001" << std::endl;
	std::cout << "(c) 8002" << RESET << std::endl;
	getline(std::cin, choice);

	if (choice == "a")
		return (8000);
	else if (choice == "b")
		return (8001);
	else if (choice == "c")
		return (8002);
	return (8000);
}

std::string		choose_method(void)
{
	std::string		choice;

	std::cout << std::endl << YELLOW << "Choose METHOD :" << std::endl;
	std::cout << "(a) GET" << std::endl;
	std::cout << "(b) HEAD" << std::endl;
	std::cout << "(c) POST" << std::endl;
	std::cout << "(d) PUT" << std::endl;
	std::cout << "(e) DELETE" << std::endl;
	std::cout << "(f) OPTIONS" << std::endl;
	std::cout << "(g) TRACE" << RESET << std::endl;
	getline(std::cin, choice);

	if (choice == "a")
		return ("get/GET");
	else if (choice == "b")
		return ("head/HEAD");
	else if (choice == "c")
		return ("post/POST");
	else if (choice == "d")
		return ("put/PUT");
	else if (choice == "e")
		return ("delete/DELETE");
	else if (choice == "f")
		return ("options/OPTIONS");
	else if (choice == "g")
		return ("trace/TRACE");
	return ("get/GET");
}

std::string		choose_target(int cgi)
{
	std::string		choice;

	std::cout << std::endl << YELLOW << "Choose TARGET FILE :" << std::endl;
	std::cout << "(a) Exists" << std::endl;
	std::cout << "(b) Doesn't exist" << std::endl;
	std::cout << "(c) Wrong permissions" << std::endl;
	std::cout << "(d) Bad request" << RESET << std::endl;
	if (cgi)
		std::cout << YELLOW << "(e) CGI (on)" << RESET << std::endl;

	getline(std::cin, choice);

	if (choice == "a")
		return ("_example");
	else if (choice == "b")
		return ("_nofile");
	else if (choice == "c")
		return ("_permission");
	else if (choice == "d")
		return ("_bad");
	else if (cgi && choice == "e")
		return ("_cgi");
	return ("_example");
}

void	send(int port, std::string filename)
{
	int					sock;
	struct sockaddr_in	serv_addr;
	char				buffer[4096] = {0};
	std::fstream		file;
	std::string			content;

	file.open(filename);
	content.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	file.close();

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cout << std::endl << RED << "< Socket creation error >" << RESET << std::endl << std::endl;
		return ;
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);


	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cout << std::endl << RED << "< Connection failed >" << RESET << std::endl << std::endl;
		return ;
	}

	content += "\r\n";

	std::cout << std::endl << "Sending :" << std::endl;
	std::cout << "[" << RED << content << RESET << "]" << std::endl << std::endl;

	send(sock, content.c_str(), content.size(), 0);
	read(sock, buffer, 4095);

	std::cout << std::endl << "Response :" << std::endl;
	std::cout << "[" << GREEN << std::string(buffer) << RESET << "]" << std::endl << std::endl;

	close(sock);

	return ;
}

int		main(void)
{
	int				port;
	std::string		filename;

	while (true)
	{
		port = choose_port();

		filename = "test_us/request/";

		filename += choose_method();

		if (filename.find("get") != std::string::npos || filename.find("post") != std::string::npos || filename.find("put") != std::string::npos)
			filename += choose_target(1);
		else
			filename += choose_target(0);

		// std::cout << std::endl << "File [" << filename << "] Port " << port << std::endl;

		send(port, filename);
	}

	return (0);
}

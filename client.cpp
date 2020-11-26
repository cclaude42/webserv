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

void	send(int port, std::string filename)
{
	int					sock;
	struct sockaddr_in	serv_addr;
	char				buffer[1024] = {0};
	std::fstream		file;
	std::string			content;

	file.open(filename);
	content.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	file.close();

	// std::cout << "FILE :" << std::endl << content << std::endl;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return ;
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);


	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\n Connection Failed \n");
		return ;
	}

	send(sock, content.c_str(), content.size(), 0);
	read(sock, buffer, 1024);
	printf("\nResponse :\n[%s]\n", buffer);

	close(sock);

	return ;
}

int		main(void)
{
	int				port;
	std::string		filename = "test_files/request/";
	std::string		choice;

	std::cout << "Choose PORT :" << std::endl;
	std::cout << "(a) 8000" << std::endl;
	std::cout << "(b) 8001" << std::endl;
	std::cout << "(c) 8002" << std::endl;
	getline(std::cin, choice);

	if (choice == "a")
		port = 8000;
	else if (choice == "b")
		port = 8001;
	else if (choice == "c")
		port = 8002;


	std::cout << std::endl << "Choose METHOD :" << std::endl;
	std::cout << "(a) GET" << std::endl;
	std::cout << "(b) HEAD" << std::endl;
	std::cout << "(c) POST" << std::endl;
	std::cout << "(d) PUT" << std::endl;
	std::cout << "(e) DELETE" << std::endl;
	std::cout << "(f) CONNECT" << std::endl;
	std::cout << "(g) OPTIONS" << std::endl;
	std::cout << "(h) TRACE" << std::endl;
	getline(std::cin, choice);

	if (choice == "a")
		filename += "get/GET";
	else if (choice == "b")
		filename += "head/HEAD";
	else if (choice == "c")
		filename += "post/POST";
	else if (choice == "d")
		filename += "put/PUT";
	else if (choice == "e")
		filename += "delete/DELETE";
	else if (choice == "f")
		filename += "connect/CONNECT";
	else if (choice == "g")
		filename += "options/OPTIONS";
	else if (choice == "h")
		filename += "trace/TRACE";

	if (choice == "f")
	{
		std::cout << std::endl << "Choose TARGET PORT :" << std::endl;
		std::cout << "(a) 8000" << std::endl;
		std::cout << "(b) 8001" << std::endl;
		std::cout << "(c) 8002" << std::endl;
		getline(std::cin, choice);

		if (choice == "a")
			filename += "_8000";
		else if (choice == "b")
			filename += "_8001";
		else if (choice == "c")
			filename += "_8002";
	}
	else
	{
		std::cout << std::endl << "Choose TARGET FILE :" << std::endl;
		std::cout << "(a) Exists" << std::endl;
		std::cout << "(b) Doesn't exists" << std::endl;
		std::cout << "(c) Wrong permissions" << std::endl;
		getline(std::cin, choice);

		if (choice == "a")
			filename += "_example";
		else if (choice == "b")
			filename += "_nofile";
		else if (choice == "c")
			filename += "_permission";
	}

	// std::cout << std::endl << "File [" << filename << "] Port " << port << std::endl;

	send(port, filename);

	return (0);
}

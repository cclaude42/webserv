#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <iostream> // For cout
#include <fstream>
#include <sstream>
#include <unistd.h> // For read
#define FT_ADDR	9997


int main() {
	// Create a socket (IPv4, TCP)
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		std::cout << "Failed to create socket. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	// Listen to port FT_ADDR on any address
	sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = INADDR_ANY;
	sockaddr.sin_port = htons(FT_ADDR); // htons is necessary to convert a number to
	// network byte order
	if (bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
		std::cout << "Failed to bind to port " << FT_ADDR << ". errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	// Start listening. Hold at most 10 connections in the queue
	if (listen(sockfd, 10) < 0) {
		std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	// Grab a connection from the queue
	auto addrlen = sizeof(sockaddr);
	int connection = accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
	if (connection < 0) {
		std::cout << "Failed to grab connection. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

		// Read from the connection
		char buffer[1000];
		auto bytesRead = read(connection, buffer, 1000);
		std::cout << "The message was: " << buffer;

		// Send a message to the connection
		std::stringstream resp;
		std::ifstream header("header");
		std::ifstream body("body");
		
		resp << header.rdbuf() << "\r\n" << body.rdbuf();

		std::string response = resp.str();
		int len = response.size();

		std::cout << "Answer is :\n";
		std::cout << response << std::endl;
		int ret = send(connection, response.c_str(), len, 0);
		std::cout << "Wrote " << len  << " bytes, sent " << ret << '\n';
	// Close the connections
	close(connection);
	close(sockfd);
}

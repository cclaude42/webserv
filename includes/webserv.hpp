/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 13:44:42 by cclaude           #+#    #+#             */
/*   Updated: 2021/03/22 10:53:15 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

// CPP Includes
# include <iostream>
# include <iomanip>
# include <sstream>
# include <fstream>
# include <string>
# include <limits>
# include <cstdio>

// CPP Containers
# include <map>
# include <set>
# include <vector>
# include <algorithm>
# include <iterator>


// C Includes
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <time.h>
# include <limits.h>
# include <errno.h>

// C System
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/time.h>

// C Network
# include <sys/socket.h>
# include <sys/select.h>
# include <arpa/inet.h>
# include <netinet/in.h>



// C libft
extern "C" {
#include "libft.h"
}



// Define two names ntoh functions
# define ft_htonl ft_ntohl
# define ft_htons ft_ntohs

// Bytes for endian conversion
# define BYTE_0 0xff000000
# define BYTE_1 0x00ff0000
# define BYTE_2 0x0000ff00
# define BYTE_3 0x000000ff

// Default
# define RECV_SIZE 4096
# define CGI_BUFSIZE 4096
# define DEFAULT_CONFIG "test_us/conf/default"

// Colors
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define RESET "\033[0m"

// Output
# ifndef OUT
#  define OUT 0
# endif
# ifndef TIME
#  define TIME 0
# endif



// NTOH / HTON
unsigned short				ft_ntohs(unsigned short s);
unsigned short				ft_htons(unsigned short s);
unsigned int				ft_ntohl(unsigned int l);
unsigned int				ft_htonl(unsigned int l);

// STRINGS
std::string					readKey(char *line); //Deprecated
std::string					readKey(std::string& line);
std::string					readValue(char *line); //Deprecated
std::string					readValue(std::string& line);
std::string&				strip(std::string& str, char c);
std::vector<std::string>	split(const std::string& str, char c);
std::string&				to_lower(std::string& str);
std::string&				to_upper(std::string& str);
std::string&				capitalize(std::string& str);
std::string					to_string(size_t n);
int							checkEnd(std::string & str, std::string end);
int							checkStart(std::string & str, std::string end);
int							countSubstr(std::string & str, std::string sub);
std::string&				pop(std::string& str);


// UTILS
int							pathIsFile(const std::string & path);
void						timeit(std::string breakpoint);


#endif

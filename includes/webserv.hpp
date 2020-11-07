/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 13:44:42 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/07 18:22:12 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

// CPP Includes
# include <iostream>
# include <iomanip>
# include <string>
# include <vector>
# include <sstream>
# include <algorithm>
# include <iterator>

// C Includes
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// Special
# include <fcntl.h>
# include <time.h>
# include <limits.h>

// System
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/socket.h>

// Network
# include <arpa/inet.h>
# include <netinet/in.h>

// Define two names ntoh functions
# define ft_htonl ft_ntohl
# define ft_htons ft_ntohs

// Bytes for endian conversion
# define BYTE_0 0xff000000
# define BYTE_1 0x00ff0000
# define BYTE_2 0x0000ff00
# define BYTE_3 0x000000ff

// HEADER
void			make_header(char *header, const char *file);

// NTOH / HTON
unsigned short	ft_ntohs(unsigned short s);
unsigned short	ft_htons(unsigned short s);
unsigned int	ft_ntohl(unsigned int l);
unsigned int	ft_htonl(unsigned int l);

// TOOLS
char			*ft_memset(char *mem, int c, unsigned int size);
int				ft_strlen(char *str);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniserv.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 13:44:42 by cclaude           #+#    #+#             */
/*   Updated: 2020/10/31 22:10:43 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISERV_HPP
# define MINISERV_HPP

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <time.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in.h>

# define BYTE_0 0xff000000
# define BYTE_1 0x00ff0000
# define BYTE_2 0x0000ff00
# define BYTE_3 0x000000ff

// NTOH / HTON
unsigned short	ft_ntohs(unsigned short s);
unsigned short	ft_htons(unsigned short s);
unsigned int	ft_ntohl(unsigned int l);
unsigned int	ft_htonl(unsigned int l);

// TOOLS
char			*ft_memset(char *mem, int c, unsigned int size);
void			make_header(char *header, const char *file);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ntoh.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:32:12 by cclaude           #+#    #+#             */
/*   Updated: 2020/10/31 20:58:08 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniserv.hpp"

unsigned short	ft_bswap16(unsigned short x)
{
	x = x >> 8 | x << 8;
	return (x);
}

unsigned int	ft_bswap32(unsigned int x)
{
	x = (x & BYTE_0) >> 24 | (x & BYTE_3) << 24 |
		(x & BYTE_1) >> 8  | (x & BYTE_2) << 8;
	return (x);
}

unsigned short	ft_ntohs(unsigned short s)
{
	if (BYTE_ORDER == BIG_ENDIAN)
		return (s);
	else if (BYTE_ORDER == LITTLE_ENDIAN)
		return (ft_bswap16(s));
	return (0);
}

unsigned short	ft_htons(unsigned short s)
{
	if (BYTE_ORDER == BIG_ENDIAN)
		return (s);
	else if (BYTE_ORDER == LITTLE_ENDIAN)
		return (ft_bswap16(s));
	return (0);
}

unsigned int	ft_ntohl(unsigned int l)
{
	if (BYTE_ORDER == BIG_ENDIAN)
		return (l);
	else if (BYTE_ORDER == LITTLE_ENDIAN)
		return (ft_bswap32(l));
	return (0);
}

unsigned int	ft_htonl(unsigned int l)
{
	if (BYTE_ORDER == BIG_ENDIAN)
		return (l);
	else if (BYTE_ORDER == LITTLE_ENDIAN)
		return (ft_bswap32(l));
	return (0);
}

// int		main(void)
// {
// 	srand(time(0));
// 	long	l;
// 	long	a;
// 	long	b;
// 	short	s;
// 	short	c;
// 	short	d;
//
// 	for (int i = 0 ; i < 10000000 ; i++)
// 	{
// 		l = rand();
// 		a = ntohl(l);
// 		b = ft_ntohl(l);
//
// 		if (a != b)
// 			printf("From [%ld] expected [%ld] but got [%ld]\n", l, a, b);
//
// 		l = rand();
// 		a = htonl(l);
// 		b = ft_htonl(l);
//
// 		if (a != b)
// 			printf("From [%ld] expected [%ld] but got [%ld]\n", l, a, b);
//
// 		s = rand();
// 		c = ntohs(s);
// 		d = ft_ntohs(s);
//
// 		if (c != d)
// 			printf("From [%hd] expected [%hd] but got [%hd]\n", s, c, d);
//
// 		s = rand();
// 		c = htons(s);
// 		d = ft_htons(s);
//
// 		if (c != d)
// 			printf("From [%hd] expected [%hd] but got [%hd]\n", s, c, d);
//
//
// 	}
// 	printf("\n");
//
// 	return (0);
// }

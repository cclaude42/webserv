/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ntoh.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:32:12 by cclaude           #+#    #+#             */
/*   Updated: 2021/03/21 19:13:51 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

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

unsigned int	ft_ntohl(unsigned int l)
{
	if (BYTE_ORDER == BIG_ENDIAN)
		return (l);
	else if (BYTE_ORDER == LITTLE_ENDIAN)
		return (ft_bswap32(l));
	return (0);
}

void			timeit(std::string breakpoint)
{
	struct timeval	current;
	gettimeofday(&current, NULL);
	static unsigned long	t_last = current.tv_sec * 1000 + current.tv_usec / 1000;
	unsigned long			t_current = current.tv_sec * 1000 + current.tv_usec / 1000;
	static std::string		prev = "Init";

	if (TIME)
		std::cerr << "Operation [" << prev << " => " << breakpoint << "] took " << t_current - t_last << " milliseconds" << std::endl;

	t_last = t_current;
	prev = breakpoint;
}

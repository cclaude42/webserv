/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstring.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:58:08 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/04 13:53:18 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int		ft_strlen(char *str)
{
	int		i = 0;

	while (str[i])
		i++;

	return (i);
}

char	*ft_memset(char *mem, int c, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < size)
	{
		mem[i] = c;
		i++;
	}
	return (mem);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:58:08 by cclaude           #+#    #+#             */
/*   Updated: 2020/10/31 22:21:14 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniserv.hpp"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_baselen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:22:44 by cclaude           #+#    #+#             */
/*   Updated: 2020/08/22 13:51:02 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_baselen(long n, int base)
{
	int		size;

	size = 0;
	if (base < 2)
		return (0);
	if (n == 0)
		return (1);
	if (n < 0)
		size++;
	while (n != 0)
	{
		n = n / base;
		size++;
	}
	return (size);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:45:11 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/06 15:38:11 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	long	nbr;
	char	*s;
	int		div;
	int		i;

	i = 0;
	nbr = n;
	if (!(s = malloc(sizeof(char) * (ft_nbrlen(nbr) + 1))))
		return (NULL);
	if (nbr < 0)
	{
		s[i++] = '-';
		nbr = -nbr;
	}
	div = ft_power(10, ft_nbrlen(nbr) - 1);
	while (div > 0)
	{
		s[i++] = nbr / div + '0';
		nbr = nbr % div;
		div = div / 10;
	}
	s[i] = '\0';
	return (s);
}

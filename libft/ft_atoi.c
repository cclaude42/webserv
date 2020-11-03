/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 08:39:24 by hbaudet           #+#    #+#             */
/*   Updated: 2019/10/11 10:10:58 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char const	*ft_clean(const char *str, int *signe)
{
	int			i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\t' || str[i] == '\n'
	|| str[i] == '\r' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*signe = -1;
		i++;
	}
	return (str + i);
}

int					ft_atoi(const char *str)
{
	int			i;
	int			resu;
	int			signe;
	const char	*tmp;

	i = 0;
	resu = 0;
	signe = 1;
	tmp = ft_clean(str, &signe);
	while (tmp[i])
	{
		if (ft_isdigit(tmp[i]))
		{
			resu *= 10;
			resu += tmp[i] - 48;
		}
		else
			return (resu * signe);
		i++;
	}
	return (resu * signe);
}

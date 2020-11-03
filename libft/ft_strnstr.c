/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 13:44:53 by hbaudet           #+#    #+#             */
/*   Updated: 2019/10/11 11:23:52 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char const	*ft_findstr(const char *str, const char *to_find, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (str[i] != 0 && i < n)
	{
		if (str[i] == to_find[0])
		{
			j = i;
			while (to_find[j - i] != 0 && j < n)
			{
				if (str[j] != to_find[j - i])
				{
					j = 0;
					break ;
				}
				if (to_find[j - i + 1] == 0)
					return (&str[i]);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}

char				*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	if (to_find[0] != 0)
		return ((char *)ft_findstr(str, to_find, n));
	else
		return ((char *)str);
}

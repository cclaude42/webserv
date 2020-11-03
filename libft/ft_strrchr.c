/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:21:36 by hbaudet           #+#    #+#             */
/*   Updated: 2019/10/07 17:48:29 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	c = (unsigned char)c;
	while (s[i])
		i++;
	while (i)
	{
		if (s[i] == c)
			return ((char *)(s + i));
		i--;
	}
	if (s[i] == c)
		return ((char *)s);
	return (NULL);
}

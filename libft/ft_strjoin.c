/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 18:55:15 by hbaudet           #+#    #+#             */
/*   Updated: 2019/10/14 08:15:23 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	taille(char const *s1, char const *s2)
{
	return (ft_strlen(s1) + ft_strlen(s2));
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = taille(s1, s2) + 1;
	if (!(result = (char *)malloc(sizeof(*result) * size)))
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = 0;
	return (result);
}

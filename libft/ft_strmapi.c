/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:13:57 by hbaudet           #+#    #+#             */
/*   Updated: 2019/10/10 16:35:15 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*resu;
	unsigned int	i;

	i = 0;
	if (!(resu = (char *)malloc(sizeof(*resu) * (ft_strlen(s) + 1))))
		return (NULL);
	while (s[i])
	{
		resu[i] = (*f)(i, s[i]);
		i++;
	}
	resu[i] = 0;
	return (resu);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 14:39:07 by hbaudet           #+#    #+#             */
/*   Updated: 2019/10/10 16:30:56 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	unsigned int	destlen;
	unsigned int	i;
	unsigned int	total;

	destlen = 0;
	i = 0;
	total = 0;
	while (dest[destlen])
		destlen++;
	while (src[total])
		total++;
	if (dstsize > destlen)
		total += destlen;
	else
		total += dstsize;
	while (src[i] && destlen + 1 < dstsize)
	{
		dest[destlen] = src[i];
		destlen++;
		i++;
	}
	dest[destlen] = 0;
	return (total);
}

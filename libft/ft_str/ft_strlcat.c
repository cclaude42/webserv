/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:19:49 by cclaude           #+#    #+#             */
/*   Updated: 2019/10/09 18:20:13 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i;

	srclen = 0;
	dstlen = 0;
	while (src[srclen] != '\0')
		srclen++;
	while (dst[dstlen] != '\0')
		dstlen++;
	if (dstlen >= dstsize)
		return (srclen + dstsize);
	i = 0;
	while (src[i] != '\0' && dstlen + i < dstsize - 1)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (srclen + dstlen);
}

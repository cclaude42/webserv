/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:49:52 by hbaudet           #+#    #+#             */
/*   Updated: 2020/11/03 18:44:27 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dst;
	s = src;
	if ((dst == NULL && src == NULL) || dst == src)
		return (dst);
	if (dst < src)
		return (ft_memcpy(dst, src, len));
	while (len)
	{
		d[len - 1] = s[len - 1];
		len--;
	}
	return (ft_memcpy(dst, src, len));
}

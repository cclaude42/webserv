/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:35:55 by hbaudet           #+#    #+#             */
/*   Updated: 2019/10/10 16:12:04 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int		i;
	const unsigned char	*sbis1;
	const unsigned char	*sbis2;

	i = 0;
	sbis1 = s1;
	sbis2 = s2;
	while (i < n && sbis1[i] == sbis2[i])
		i++;
	if (i == n)
		return (0);
	return ((int)sbis1[i] - (int)sbis2[i]);
}

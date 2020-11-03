/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 18:17:01 by hbaudet           #+#    #+#             */
/*   Updated: 2019/10/10 10:30:57 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char			*ptr;
	unsigned int	size;

	size = ft_strlen(src);
	if (!(ptr = malloc(sizeof(*ptr) * (size + 1))))
		return (NULL);
	return (ft_strcpy(ptr, src));
}

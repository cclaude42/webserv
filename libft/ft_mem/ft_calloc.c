/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:23:38 by cclaude           #+#    #+#             */
/*   Updated: 2019/10/09 14:33:54 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*space;
	size_t	i;

	i = 0;
	if (!(space = malloc(size * count + 1)))
		return (NULL);
	while (i < count * size + 1)
		space[i++] = '\0';
	return (space);
}

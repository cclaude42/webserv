/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 10:20:30 by hbaudet           #+#    #+#             */
/*   Updated: 2019/10/15 10:32:32 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup(const char *src, size_t n)
{
	char			*ptr;

	if (!(ptr = malloc(sizeof(*ptr) * (n + 1))))
		return (NULL);
	ptr[n] = 0;
	return (ft_strncpy(ptr, src, n));
}

static int	is_from_set(const char c, const char *set)
{
	int		j;

	j = 0;
	while (set[j])
	{
		if (c == set[j])
			return (1);
		j++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		size;

	i = 0;
	size = ft_strlen(s1);
	while (is_from_set(s1[i], set))
		i++;
	if (size > 0 && i < size)
	{
		j = size - 1;
		while (is_from_set(s1[j], set))
			j--;
		return (ft_strndup(&s1[i], j - i + 1));
	}
	else
		return (ft_strdup(""));
}

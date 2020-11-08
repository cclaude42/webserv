/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:21:55 by cclaude           #+#    #+#             */
/*   Updated: 2019/10/16 14:32:00 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == (char)set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	alloc_size(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	while (s1[len] != '\0')
		len++;
	while (is_set(s1[i], set) && s1[i] != '\0')
	{
		i++;
		j++;
	}
	if (j == len)
		return (0);
	i = len - 1;
	while (is_set(s1[i], set) && i != 0)
	{
		i--;
		j++;
	}
	return (len - j);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	int		i;
	int		j;
	int		alloc_len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	j = 0;
	alloc_len = alloc_size(s1, set);
	if (!(new = malloc(sizeof(char) * alloc_len + 1)))
		return (NULL);
	while (is_set(s1[i], set))
		i++;
	while (j < alloc_len)
		new[j++] = s1[i++];
	new[alloc_len] = '\0';
	return (new);
}

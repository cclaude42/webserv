/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 08:28:09 by hbaudet           #+#    #+#             */
/*   Updated: 2019/10/14 14:57:16 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*ft_fill_da_str(int *i, char const *str, char c)
{
	char	*dest;
	int		j;
	int		k;

	j = *i;
	k = 0;
	while (str[*i] && str[*i] != c)
		(*i)++;
	if (!(dest = malloc(sizeof(*dest) * (*i - j + 1))))
		return (0);
	while (j + k < *i)
	{
		dest[k] = str[j + k];
		k++;
	}
	dest[k] = 0;
	return (dest);
}

static char	**ft_fill_da_tab(char const *str, char c, int size)
{
	char	**result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(result = malloc(sizeof(result) * (size + 1))))
		return (0);
	while (str[i] == c)
		i++;
	while (j < size)
	{
		result[j] = ft_fill_da_str(&i, str, c);
		while (str[i] && str[i] == c)
			i++;
		j++;
	}
	result[j] = NULL;
	return (result);
}

char		**ft_split(char const *s, char c)
{
	int	i;
	int nb_words;

	i = 0;
	nb_words = 0;
	while (s[i])
	{
		if ((s[i + 1] == c || s[i + 1] == 0) && s[i] != c)
			nb_words++;
		i++;
	}
	return (ft_fill_da_tab(s, c, nb_words));
}

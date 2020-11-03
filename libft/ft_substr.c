/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 09:35:50 by hbaudet           #+#    #+#             */
/*   Updated: 2019/10/14 09:41:39 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup(const char *src, size_t n)
{
	char			*ptr;
	unsigned int	size;

	size = ft_strlen(src);
	if (size > n)
		size = n;
	if (!(ptr = malloc(sizeof(*ptr) * (size + 1))))
		return (NULL);
	ft_strncpy(ptr, src, size);
	ptr[size] = 0;
	return (ptr);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;

	i = start;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	while (s[start])
		start++;
	if (start - i + 1 < len)
		len = start - i + 1;
	return (ft_strndup(&s[i], len));
}

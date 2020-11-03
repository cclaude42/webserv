/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:31:13 by hbaudet           #+#    #+#             */
/*   Updated: 2019/10/16 09:47:27 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_rev_tab(char *tab, int j)
{
	int		i;
	char	buff;

	i = 0;
	while (i < j / 2)
	{
		buff = tab[i];
		tab[i] = tab[j - (i + 1)];
		tab[j - (i + 1)] = buff;
		i++;
	}
	return (tab);
}

static char	*ft_rev_fill(long n, int count, int *j)
{
	char	*tmp;
	long	buff;

	buff = n;
	if (!n)
		return (ft_strdup("0"));
	while (buff)
	{
		buff /= 10;
		count++;
	}
	if (!(tmp = (char *)malloc(sizeof(char) * (count + 1))))
		return (NULL);
	while (n != 0)
	{
		tmp[*j] = n % 10 + 48;
		n /= 10;
		(*j)++;
	}
	tmp[*j] = 0;
	return (tmp);
}

char		*ft_itoa(int n)
{
	char	*tmp;
	int		signe;
	long	p;
	int		j;

	j = 0;
	signe = 0;
	p = n;
	if (n < 0)
	{
		signe = 1;
		p *= -1;
	}
	if (!(tmp = ft_rev_fill(p, signe, &j)))
		return (NULL);
	if (signe == 1)
	{
		tmp[j] = '-';
		tmp[++j] = 0;
	}
	return (ft_rev_tab(tmp, j));
}

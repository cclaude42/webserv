/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zero.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:26:48 by hbaudet           #+#    #+#             */
/*   Updated: 2019/10/14 17:41:49 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_zero(int n)
{
	char	*ret;

	if (n == 0)
	{
		if (!(ret = (char *)malloc(sizeof(char) * 2)))
			return (NULL);
		ret[0] = 48;
		ret[1] = 0;
		return (ret);
	}
	else
		return (ft_strdup("-2147483648"));
}

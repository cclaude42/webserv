/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 16:20:59 by hbaudet           #+#    #+#             */
/*   Updated: 2020/11/03 18:44:53 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_print(unsigned int toprint, int fd)
{
	if (toprint >= 10)
		ft_print(toprint / 10, fd);
	ft_putchar_fd(toprint % 10 + 48, fd);
}

void		ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb_posi;

	if (n < 0)
	{
		write(fd, "-", 1);
		nb_posi = (unsigned int)(n * -1);
	}
	else
		nb_posi = (unsigned int)n;
	ft_print(nb_posi, fd);
}

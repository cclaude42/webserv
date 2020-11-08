/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put_c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:51:01 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/27 12:32:33 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_putchar_minwid(struct s_flgs *flags, char c, int width)
{
	int	count;

	count = 0;
	buf_write(flags->buffer, c, &flags->index);
	while (count++ < width - 1)
		buf_write(flags->buffer, ' ', &flags->index);
	return (width);
}

int		pf_putchar_zerowid(struct s_flgs *flags, char c, int width)
{
	int	count;

	count = 0;
	while (count++ < width - 1)
		buf_write(flags->buffer, '0', &flags->index);
	buf_write(flags->buffer, c, &flags->index);
	return (width);
}

int		pf_putchar_wid(struct s_flgs *flags, char c, int width)
{
	int	count;

	count = 0;
	while (count++ < width - 1)
		buf_write(flags->buffer, ' ', &flags->index);
	buf_write(flags->buffer, c, &flags->index);
	return (width);
}

int		pf_putchar(struct s_flgs *flags, char c)
{
	buf_write(flags->buffer, c, &flags->index);
	return (1);
}

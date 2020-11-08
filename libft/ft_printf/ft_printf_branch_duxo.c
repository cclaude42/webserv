/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_branch_duxo.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 20:02:00 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/27 12:32:26 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_print_nbr(long n, struct s_flgs *flags)
{
	int	i;

	i = 0;
	if (flags->dot == 1 && flags->precision == 0 && n == 0)
	{
		while (i++ < flags->width)
			buf_write(flags->buffer, ' ', &flags->index);
		return (flags->width);
	}
	else if (flags->width > 0 && flags->dot == 1)
		return (pf_putnbr_prewid(n, flags));
	else if (flags->width > 0 && flags->zero == 0)
		return (pf_putnbr_wid(n, flags));
	else if (flags->width > 0 && flags->zero == 1 && flags->minus == 1)
		return (pf_putnbr_wid(n, flags));
	else if (flags->dot == 1 || (flags->width > 0 && flags->zero == 1))
		return (pf_putnbr_pre(n, flags));
	else
		return (pf_putnbr(flags, n));
}

int		pf_print_hex(unsigned int n, struct s_flgs *flags, char c)
{
	int	i;
	int	cap;

	i = 0;
	cap = (c == 'X') ? 1 : 0;
	if (flags->dot == 1 && flags->precision == 0 && n == 0)
	{
		while (i++ < flags->width)
			buf_write(flags->buffer, ' ', &flags->index);
		return (flags->width);
	}
	else if (flags->width > 0 && flags->dot == 1)
		return (pf_puthex_prewid(n, flags, cap));
	else if (flags->width > 0 && flags->zero == 0)
		return (pf_puthex_wid(n, flags, cap));
	else if (flags->width > 0 && flags->zero == 1 && flags->minus == 1)
		return (pf_puthex_wid(n, flags, cap));
	else if (flags->dot == 1 || (flags->width > 0 && flags->zero == 1))
		return (pf_puthex_pre(n, flags, cap));
	else
		return (pf_puthex(flags, n, cap));
}

int		pf_print_oct(unsigned int n, struct s_flgs *flags)
{
	int	i;

	i = 0;
	if (flags->dot == 1 && flags->precision == 0 && n == 0)
	{
		while (i++ < flags->width)
			buf_write(flags->buffer, ' ', &flags->index);
		return (flags->width);
	}
	else if (flags->width > 0 && flags->dot == 1)
		return (pf_putoct_prewid(n, flags));
	else if (flags->width > 0 && flags->zero == 0)
		return (pf_putoct_wid(n, flags));
	else if (flags->width > 0 && flags->zero == 1 && flags->minus == 1)
		return (pf_putoct_wid(n, flags));
	else if (flags->dot == 1 || (flags->width > 0 && flags->zero == 1))
		return (pf_putoct_pre(n, flags));
	else
		return (pf_putoct(flags, n));
}

int		pf_print_other(char c, struct s_flgs *flags)
{
	int	padding;

	padding = flags->width - 1;
	if (c == '\0')
		return (0);
	while (flags->minus == 0 && flags->zero == 0 && padding-- > 0)
		buf_write(flags->buffer, ' ', &flags->index);
	while (flags->minus == 0 && flags->zero == 1 && padding-- > 0)
		buf_write(flags->buffer, '0', &flags->index);
	buf_write(flags->buffer, c, &flags->index);
	while (flags->minus == 1 && padding-- > 0)
		buf_write(flags->buffer, ' ', &flags->index);
	if (flags->width > 0)
		return (flags->width);
	else
		return (1);
}

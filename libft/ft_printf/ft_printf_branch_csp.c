/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_branch_csp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:20:23 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/27 12:32:22 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_print_char(char c, struct s_flgs *flags)
{
	if (flags->width > 0 && flags->minus == 1)
		return (pf_putchar_minwid(flags, c, flags->width));
	else if (flags->width > 0 && flags->zero == 1)
		return (pf_putchar_zerowid(flags, c, flags->width));
	else if (flags->width > 0)
		return (pf_putchar_wid(flags, c, flags->width));
	else
		return (pf_putchar(flags, c));
}

int		pf_print_str(char *s, struct s_flgs *flags)
{
	if (s == NULL)
	{
		if (flags->width > 0 && flags->dot == 1)
			return (pf_putstr_prewid("(null)", flags));
		else if (flags->width > 0)
			return (pf_putstr_wid("(null)", flags));
		else if (flags->dot == 1)
			return (pf_putstr_pre(flags, "(null)", flags->precision));
		else
			return (pf_putstr(flags, "(null)"));
	}
	else
	{
		if (flags->width > 0 && flags->dot == 1)
			return (pf_putstr_prewid(s, flags));
		else if (flags->width > 0)
			return (pf_putstr_wid(s, flags));
		else if (flags->dot == 1)
			return (pf_putstr_pre(flags, s, flags->precision));
		else
			return (pf_putstr(flags, s));
	}
}

int		pf_print_mem(unsigned long n, struct s_flgs *flags)
{
	int	i;

	i = 0;
	if (flags->dot == 1 && flags->precision == 0 && n == 0)
	{
		while (flags->minus == 0 && i++ < flags->width - 2)
			buf_write(flags->buffer, ' ', &flags->index);
		buf_write(flags->buffer, '0', &flags->index);
		buf_write(flags->buffer, 'x', &flags->index);
		while (flags->minus == 1 && i++ < flags->width - 2)
			buf_write(flags->buffer, ' ', &flags->index);
		return (i + 1);
	}
	if (flags->width > 0 && flags->dot == 1)
		return (pf_putmem_prewid(n, flags));
	if (flags->width > 0 && flags->zero == 0)
		return (pf_putmem_wid(n, flags));
	else if (flags->dot == 1 || (flags->width > 0 && flags->zero == 1))
		return (pf_putmem_pre(n, flags));
	else
		return (pf_putmem(flags, n, 1));
}

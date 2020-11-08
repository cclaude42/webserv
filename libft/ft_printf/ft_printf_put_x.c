/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put_x.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:21:24 by cclaude           #+#    #+#             */
/*   Updated: 2020/04/20 19:39:03 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_hexlen(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 16;
		len++;
	}
	return (len);
}

int		pf_puthex_prewid(unsigned int n, struct s_flgs *flags, int cap)
{
	int		printed;
	int		count;
	int		padding;

	printed = 0;
	count = flags->precision - pf_hexlen(n);
	count = (count > 0) ? count : 0;
	padding = flags->width - pf_hexlen(n) - count;
	padding = (padding > 0) ? padding : 0;
	printed += padding + count + pf_hexlen(n);
	while (flags->minus == 0 && padding-- > 0)
		buf_write(flags->buffer, ' ', &flags->index);
	while (count-- > 0)
		buf_write(flags->buffer, '0', &flags->index);
	pf_puthex(flags, n, cap);
	while (flags->minus == 1 && padding-- > 0)
		buf_write(flags->buffer, ' ', &flags->index);
	return (printed);
}

int		pf_puthex_pre(unsigned int n, struct s_flgs *flags, int cap)
{
	int		printed;
	int		count;

	printed = 0;
	count = (flags->dot == 1) ? flags->precision : flags->width;
	count -= pf_hexlen(n);
	while (count-- > 0)
	{
		buf_write(flags->buffer, '0', &flags->index);
		printed++;
	}
	printed += pf_puthex(flags, n, cap);
	return (printed);
}

int		pf_puthex_wid(unsigned int n, struct s_flgs *flags, int cap)
{
	int		printed;
	int		padding;

	printed = 0;
	padding = flags->width - pf_hexlen(n);
	while (flags->minus == 0 && padding-- > 0)
	{
		buf_write(flags->buffer, ' ', &flags->index);
		printed++;
	}
	printed += pf_puthex(flags, n, cap);
	while (flags->minus == 1 && padding-- > 0)
	{
		buf_write(flags->buffer, ' ', &flags->index);
		printed++;
	}
	return (printed);
}

int		pf_puthex(struct s_flgs *flags, unsigned int n, int cap)
{
	char	*set;
	int		printed;
	int		i;

	if (cap == 1)
		set = "0123456789ABCDEF";
	else
		set = "0123456789abcdef";
	printed = 0;
	if (n / 16 > 0)
		printed += pf_puthex(flags, n / 16, cap);
	i = n % 16;
	buf_write(flags->buffer, set[i], &flags->index);
	printed++;
	return (printed);
}

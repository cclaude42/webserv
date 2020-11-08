/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put_o.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 19:56:57 by cclaude           #+#    #+#             */
/*   Updated: 2020/04/20 19:38:23 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_octlen(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 8;
		len++;
	}
	return (len);
}

int		pf_putoct_prewid(unsigned int n, struct s_flgs *flags)
{
	int		printed;
	int		count;
	int		padding;

	printed = 0;
	count = flags->precision - pf_octlen(n);
	count = (count > 0) ? count : 0;
	padding = flags->width - pf_octlen(n) - count;
	padding = (padding > 0) ? padding : 0;
	printed += padding + count + pf_octlen(n);
	while (flags->minus == 0 && padding-- > 0)
		buf_write(flags->buffer, ' ', &flags->index);
	while (count-- > 0)
		buf_write(flags->buffer, '0', &flags->index);
	pf_putoct(flags, n);
	while (flags->minus == 1 && padding-- > 0)
		buf_write(flags->buffer, ' ', &flags->index);
	return (printed);
}

int		pf_putoct_pre(unsigned int n, struct s_flgs *flags)
{
	int		printed;
	int		count;

	printed = 0;
	count = (flags->dot == 1) ? flags->precision : flags->width;
	count -= pf_octlen(n);
	while (count-- > 0)
	{
		buf_write(flags->buffer, '0', &flags->index);
		printed++;
	}
	printed += pf_putoct(flags, n);
	return (printed);
}

int		pf_putoct_wid(unsigned int n, struct s_flgs *flags)
{
	int		printed;
	int		padding;

	printed = 0;
	padding = flags->width - pf_octlen(n);
	while (flags->minus == 0 && padding-- > 0)
	{
		buf_write(flags->buffer, ' ', &flags->index);
		printed++;
	}
	printed += pf_putoct(flags, n);
	while (flags->minus == 1 && padding-- > 0)
	{
		buf_write(flags->buffer, ' ', &flags->index);
		printed++;
	}
	return (printed);
}

int		pf_putoct(struct s_flgs *flags, unsigned int n)
{
	char	*set;
	int		printed;
	int		i;

	set = "01234567";
	printed = 0;
	if (n / 8 > 0)
		printed += pf_putoct(flags, n / 8);
	i = n % 8;
	buf_write(flags->buffer, set[i], &flags->index);
	printed++;
	return (printed);
}

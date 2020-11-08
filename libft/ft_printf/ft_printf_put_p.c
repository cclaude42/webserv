/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put_p.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:50:49 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/27 12:32:44 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_memlen(unsigned long n)
{
	int	len;

	len = 0;
	if (n / 16 > 0)
		len += pf_memlen(n / 16);
	len++;
	return (len);
}

int		pf_putmem_prewid(unsigned long n, struct s_flgs *flags)
{
	int		printed;
	int		padding;
	int		count;

	count = flags->precision - pf_memlen(n);
	count = (count > 0) ? count : 0;
	padding = flags->width - count - pf_memlen(n) - 2;
	padding = (padding > 0) ? padding : 0;
	printed = 2 + padding + count;
	while (flags->minus == 0 && padding-- > 0)
		buf_write(flags->buffer, ' ', &flags->index);
	buf_write(flags->buffer, '0', &flags->index);
	buf_write(flags->buffer, 'x', &flags->index);
	while (count-- > 0)
		buf_write(flags->buffer, '0', &flags->index);
	printed += pf_putmem(flags, n, 0);
	while (flags->minus == 1 && padding-- > 0)
		buf_write(flags->buffer, ' ', &flags->index);
	return (printed);
}

int		pf_putmem_wid(unsigned long n, struct s_flgs *flags)
{
	int		printed;
	int		padding;

	printed = 0;
	padding = (flags->dot == 1) ? flags->precision : flags->width - 2;
	padding -= pf_memlen(n);
	while (flags->minus == 0 && padding-- > 0)
	{
		buf_write(flags->buffer, ' ', &flags->index);
		printed++;
	}
	printed += pf_putmem(flags, n, 1);
	while (flags->minus == 1 && padding-- > 0)
	{
		buf_write(flags->buffer, ' ', &flags->index);
		printed++;
	}
	return (printed);
}

int		pf_putmem_pre(unsigned long n, struct s_flgs *flags)
{
	char	*set;
	int		i;
	int		printed;
	int		count;

	buf_write(flags->buffer, '0', &flags->index);
	buf_write(flags->buffer, 'x', &flags->index);
	printed = 2;
	count = (flags->dot == 1) ? flags->precision : flags->width - 2;
	count -= pf_memlen(n);
	while (count-- > 0)
	{
		buf_write(flags->buffer, '0', &flags->index);
		printed++;
	}
	set = "0123456789abcdef";
	if (n / 16 > 0)
		printed += pf_putmem(flags, n / 16, 0);
	i = n % 16;
	buf_write(flags->buffer, set[i], &flags->index);
	printed++;
	return (printed);
}

int		pf_putmem(struct s_flgs *flags, unsigned long n, int start)
{
	char	*set;
	int		i;
	int		printed;

	printed = 0;
	if (start)
	{
		buf_write(flags->buffer, '0', &flags->index);
		buf_write(flags->buffer, 'x', &flags->index);
		printed += 2;
	}
	set = "0123456789abcdef";
	if (n / 16 > 0)
		printed += pf_putmem(flags, n / 16, 0);
	i = n % 16;
	buf_write(flags->buffer, set[i], &flags->index);
	printed++;
	return (printed);
}

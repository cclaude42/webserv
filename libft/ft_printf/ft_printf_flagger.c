/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flagger.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:18:32 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/27 12:32:29 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_end_flag(const char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i')
		return (1);
	if (c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

int		is_valid_flag(const char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i')
		return (1);
	if (c == 'u' || c == 'x' || c == 'X' || c == '%' || c == ' ')
		return (1);
	if (c == '-' || c == '.' || c == '*')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int		pf_atoi_star(const char *s, int *i, va_list args)
{
	int	num;

	num = 0;
	if (s[*i] == '.')
		(*i)++;
	if (s[*i] == '*')
	{
		num = va_arg(args, unsigned int);
		return (num);
	}
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		num = num * 10 + (s[*i] - 48);
		(*i)++;
	}
	(*i)--;
	return (num);
}

void	pf_neg_star(struct s_flgs *flags)
{
	if (flags->precision < 0)
	{
		flags->dot = 0;
		flags->precision = 0;
	}
	else if (flags->width < 0)
	{
		flags->minus = 1;
		flags->width = -flags->width;
	}
	return ;
}

void	flagger(const char *s, int *i, struct s_flgs *flags, va_list args)
{
	flags->minus = 0;
	flags->zero = 0;
	flags->dot = 0;
	flags->precision = 0;
	flags->width = 0;
	while (is_end_flag(s[*i]) == 0 && is_valid_flag(s[*i]))
	{
		if (s[*i] == '-')
			flags->minus = 1;
		else if (s[*i] == '0')
			flags->zero = 1;
		else if (s[*i] == '.')
		{
			flags->dot = 1;
			flags->precision = pf_atoi_star(s, i, args);
		}
		else if (s[*i] == '*' || (s[*i] >= '1' && s[*i] <= '9'))
			flags->width = pf_atoi_star(s, i, args);
		if (flags->precision < 0 || flags->width < 0)
			pf_neg_star(flags);
		(*i)++;
	}
}

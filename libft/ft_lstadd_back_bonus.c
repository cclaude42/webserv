/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:58:43 by hbaudet           #+#    #+#             */
/*   Updated: 2019/10/15 12:22:37 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *ptr;

	if (!alst)
		return ;
	ptr = *alst;
	if (ptr != NULL)
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	else
		*alst = new;
}

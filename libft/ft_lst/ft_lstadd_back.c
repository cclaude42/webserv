/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:48:45 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/08 12:54:57 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *newt)
{
	t_list	*temp;

	if (!alst)
		return ;
	if (*alst != NULL)
	{
		temp = *alst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newt;
	}
	else
		*alst = newt;
}

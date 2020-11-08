/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:49:22 by cclaude           #+#    #+#             */
/*   Updated: 2019/10/16 16:06:20 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	temp = NULL;
	if (lst == NULL)
		return (temp);
	else
		temp = lst;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:34:53 by hbaudet           #+#    #+#             */
/*   Updated: 2019/10/16 14:11:10 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*))
{
	t_list	*ptr;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	ptr = ft_lstnew((*f)(lst->content));
	tmp = ptr;
	lst = lst->next;
	while (lst)
	{
		ft_lstadd_back(&ptr, ft_lstnew((*f)(lst->content)));
		if (!ptr)
			return (NULL);
		ptr = ft_lstlast(ptr);
		lst = lst->next;
	}
	return (tmp);
}

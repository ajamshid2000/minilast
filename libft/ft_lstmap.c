/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:40:01 by ajamshid          #+#    #+#             */
/*   Updated: 2023/12/12 16:36:47 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list_new;
	t_list	*first_node;

	if (!lst || !f || !del)
		return (0);
	list_new = ft_lstnew(f(lst->content));
	if (!list_new)
		return (0);
	first_node = list_new;
	lst = lst->next;
	while (lst)
	{
		list_new->next = ft_lstnew(f(lst->content));
		if (!list_new->next)
		{
			ft_lstclear(&first_node, del);
			return (0);
		}
		list_new = list_new->next;
		lst = lst->next;
	}
	list_new->next = NULL;
	return (first_node);
}

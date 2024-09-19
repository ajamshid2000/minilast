/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:44:49 by ajamshid          #+#    #+#             */
/*   Updated: 2023/12/11 11:45:55 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		counter;
	t_list	*var;

	counter = 0;
	if (lst == NULL)
		return (counter);
	var = lst;
	while (var != NULL)
	{
		var = var->next;
		counter++;
	}
	return (counter);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 07:33:44 by famana            #+#    #+#             */
/*   Updated: 2023/11/13 12:27:33 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
/*
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
int	ft_isalpha(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return (1);
	}
	if (c >= 'a' && c <= 'z')
	{
		return (2);
	}
	return (0);
}

#include <stdio.h>

int	main(void){
	printf("c=%d\n",ft_alnum('c'));
	printf("1=%d\n",ft_alnum('1'));
	printf(" =%d\n",ft_alnum(' '));
}
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:54:01 by famana            #+#    #+#             */
/*   Updated: 2023/11/23 07:50:05 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	if (f == 0 || s == 0)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
#include <stdio.h>

void	print_with_index(unsigned int index, char *character) {
	printf("Index: %u, Character: %c\n", index, *character);
}

int	main(void) {

	char str[] = "Hello, World!";

	ft_striteri(str, &print_with_index);

	return (0);
}*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:32:23 by famana            #+#    #+#             */
/*   Updated: 2023/11/15 07:37:10 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s_ptr;
	size_t				i;

	s_ptr = s;
	i = 0;
	while (i < n)
	{
		if (s_ptr[i] == (unsigned char)c)
		{
			return ((void *)(s_ptr + i));
		}
		i++;
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void) {
	char str[] = "Hello, World!";
	char character = 'o';

	// Search for the first occurrence of 'o' in 'str'
	char *result = ft_memchr(str, character, strlen(str));

	if (result != NULL) {
		printf("Character '%c' found at position %ld\n", character, result
			- str);
	} else {
		printf("Character '%c' not found in the string\n", character);
	}

	return (0);
}*/
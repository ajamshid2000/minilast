/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:43:21 by famana            #+#    #+#             */
/*   Updated: 2023/11/14 07:08:53 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return ((char *)s + i);
	return (0);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void) {
	const char *str = "Hello, World!";
	char character = 'o';
	char *result = ft_strchr(str, character);

	if (result != NULL) {
		printf("Character '%c' found at position %ld\n", character, result
			- str);
	} else {
		printf("Character '%c' not found in the string\n", character);
	}

	return (0);
}*/
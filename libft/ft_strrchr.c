/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:12:55 by famana            #+#    #+#             */
/*   Updated: 2023/11/14 07:11:22 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*current;

	i = 0;
	current = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
		{
			current = (char *)s + i;
		}
		i++;
	}
	if (s[i] == (unsigned char)c)
	{
		current = (char *)s + i;
	}
	return (current);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void) {
	const char *str = "Hello, World!";
	char character = 'o';

	char *result = ft_strrchr(str, character);

	if (result != NULL) {
		printf("Character '%c' found at position %ld (from the end)\n",
			character, strlen(str) - (result - str) - 1);
	} else {
		printf("Character '%c' not found in the string\n", character);
	}

	return (0);
}
*/

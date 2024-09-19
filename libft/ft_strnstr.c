/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:42:40 by famana            #+#    #+#             */
/*   Updated: 2023/11/23 08:28:00 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	if (len == 0)
		return (0);
	while (big[i] != '\0')
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j) < len)
		{
			if (big[i + j] == '\0' && little[j] == '\0')
				return ((char *)&big[i]);
			j++;
		}
		if (little[j] == '\0')
			return ((char *)big + i);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>m
#include <string.h>

int	main(void)
{
	const char *haystack = "Hello, World!";
	const char *needle = "";
	size_t length = 0;
	char *result = ft_strnstr(haystack, needle, length);

	if (result != NULL)
	{
		printf("Substring found: %s\n", result);
	}
	else
	{
		printf("Substring not found\n");
	}

	return (0);
}*/
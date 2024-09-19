/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:27:54 by famana            #+#    #+#             */
/*   Updated: 2023/11/13 09:07:09 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_ptr = s1;
	const unsigned char	*s2_ptr = s2;
	size_t				i;

	i = 0;
	while (i < n)
	{
		if (s1_ptr[i] != s2_ptr[i])
		{
			return (s1_ptr[i] - s2_ptr[i]);
		}
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void) {
	char str1[] = "Hello, World!";
	char str2[] = "Hello, World!";
	char str3[] = "Hello, Coder!";

	// Compare str1 and str2
	int result1 = memcmp(str1, str2, sizeof(str1));

	// Compare str1 and str3
	int result2 = memcmp(str1, str3, sizeof(str1));

	if (result1 == 0) {
		printf("str1 and str2 are equal\n");
	} else if (result1 < 0) {
		printf("str1 is lexicographically less than str2\n");
	} else {
		printf("str1 is lexicographically greater than str2\n");
	}

	if (result2 == 0) {
		printf("str1 and str3 are equal\n");
	} else if (result2 < 0) {
		printf("str1 is lexicographically less than str3\n");
	} else {
		printf("str1 is lexicographically greater than str3\n");
	}

	return (0);
}*/
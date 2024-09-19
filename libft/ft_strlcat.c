/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:36:49 by famana            #+#    #+#             */
/*   Updated: 2023/11/15 07:56:41 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (size == 0)
	{
		while (src[j])
			j++;
		return (j);
	}
	while (dst[i] && i < size)
		i++;
	while (src[j] && i + j + 1 < size)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < size)
		dst[i + j] = '\0';
	while (src[j])
		j++;
	return (i + j);
}
/*
#include <stdio.h>

int	main(void)
{
	char dest[20] = "Hello, ";
	const char *source = "World!";

	printf("Before concatenation: %s\n", dest);

	size_t result = ft_strlcat(dest, source, sizeof(dest));

	printf("After concatenation: %s\n", dest);
	printf("Total characters: %lu\n", result);

	return (0);
}*/
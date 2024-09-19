/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:01:03 by famana            #+#    #+#             */
/*   Updated: 2023/11/13 12:52:58 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (src[len])
	{
		len++;
	}
	if (size <= 0)
		return (len);
	i = 0;
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}
/*
#include <stdio.h>

int	main(void) {
	char dest[20];
	const char *source = "Hello, World!";

	size_t result = ft_strlcpy(dest, source, sizeof(dest));

	printf("Copied string: %s\n", dest);
	printf("Total characters copied: %lu\n", result);

	return (0);
}*/
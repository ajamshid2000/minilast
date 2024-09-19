/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 08:31:03 by famana            #+#    #+#             */
/*   Updated: 2023/11/13 09:07:19 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dest_ptr;
	const unsigned char	*src_ptr;

	dest_ptr = dest;
	src_ptr = src;
	if (dest_ptr > src_ptr)
	{
		i = n;
		while (i > 0)
		{
			dest_ptr[i - 1] = src_ptr[i - 1];
			i--;
		}
	}
	else if (dest_ptr < src_ptr)
	{
		i = 0;
		while (i < n)
		{
			dest_ptr[i] = src_ptr[i];
			i++;
		}
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>


int	main(void) {
	char str1[] = "Hello, World!";
	char str2[] = "Hello, World!";

	ft_memmove(str1 + 7, str1, 5);
	printf("ft_memmove result: %s\n", str1);

	memmove(str2 + 7, str2, 5);
	printf("memmove result: %s\n", str2);

	return (0);
}*/
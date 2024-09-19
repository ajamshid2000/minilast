/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:40:49 by famana            #+#    #+#             */
/*   Updated: 2023/11/23 08:42:57 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (0);
	mem = malloc(nmemb * size);
	if (mem != 0)
		ft_memset(mem, 0, nmemb * size);
	return (mem);
}
/*
#include <stdio.h>

int	main(void)
{
	int *arr;
	int i = 0;
	size_t num_elements = 5;
	arr = (int *)ft_calloc(num_elements, sizeof(int));

	if (arr == NULL)
	{
		printf("Memory allocation failed.\n");
		return (1);
	}
	while (i < num_elements)
	{
		printf("arr[%d] = %d\n", i, arr[i]);
		i++;
	}
	free(arr);

	return (0);
}*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:45:58 by famana            #+#    #+#             */
/*   Updated: 2023/11/14 15:18:30 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *origin)
{
	int			i;
	char		*result;
	const int	len = ft_strlen((char *)origin);

	result = (char *)malloc((len + 1) * sizeof(char));
	if (result == 0)
	{
		return (0);
	}
	i = 0;
	while (i < len + 1)
	{
		result[i] = origin[i];
		i++;
	}
	return (result);
}

/*

#include <stdio.h>
#include <string.h>






int	main(void) {
	const char *original = "Hello, World!";
	char *duplicate;
	duplicate = ft_strdup(original);

	if (duplicate == NULL) {
		printf( "Memory allocation failed.\n");
		return (1);
	}

	printf("Original: %s\n", original);
	printf("Duplicate: %s\n", duplicate);

	free(duplicate);

	return (0);
}*/
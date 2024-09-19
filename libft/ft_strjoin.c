/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:56:47 by famana            #+#    #+#             */
/*   Updated: 2023/11/23 07:55:27 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen_safe(const char *s)
{
	size_t	i;

	if (s == 0)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int			i;
	char		*result;
	const int	s1_len = ft_strlen_safe(s1);
	const int	s2_len = ft_strlen_safe(s2);

	result = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (result == 0)
		return (0);
	i = 0;
	while (i < s1_len)
	{
		result[i] = s1[i];
		i++;
	}
	while (i < s1_len + s2_len)
	{
		result[i] = s2[i - s1_len];
		i++;
	}
	result[i] = '\0';
	return (result);
}

/*
#include <stdio.h>

int	main(void) {
	const char *str1 = "Hello, ";
	const char *str2 = "World!";

	char *result = ft_strjoin(str1, str2);

	if (result != NULL) {
		printf("Concatenated string: %s\n", result);
		free(result);
	} else {
		printf("Memory allocation failed.\n");
	}

	return (0);
}*/
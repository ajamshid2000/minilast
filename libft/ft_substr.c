/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:06:20 by famana            #+#    #+#             */
/*   Updated: 2023/11/23 07:38:41 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*result;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (start >= s_len)
		start = s_len;
	if (s_len - start < len)
		len = s_len - start;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (result == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		result[i] = s[i + start];
		i++;
	}
	result[i] = '\0';
	return (result);
}

/*
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new;
	unsigned int	i;

	if (start >= ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (start + i < ft_strlen(s) && i < len)
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}*/

/*
#include <stdio.h>


int	main(void) {
	const char *str = "Hello, World!";
	unsigned int start = 7;
	size_t length = 5;

	char *substring = ft_substr(str, start, length);

	if (substring != NULL) {
		printf("Substring: %s\n", substring);
		free(substring);
	} else {
		printf("Substring is NULL\n");
	}

	return (0);
}*/
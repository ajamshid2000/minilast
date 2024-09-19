/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/09 10:08:06 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/** Corrected version of ft_strcpy */
size_t	my_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (i);
}

char	*clone_string(const char *str)
{
	char	*clone;

	if (str == NULL)
	{
		return (NULL);
	}
	clone = (char *)malloc(ft_strlen(str) + 1);
	if (clone == NULL)
	{
		printf("Memory allocation failed!\n");
		return (NULL);
	}
	my_strcpy(clone, str);
	return (clone);
}

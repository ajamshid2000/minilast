/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 07:19:38 by famana            #+#    #+#             */
/*   Updated: 2023/11/20 08:07:29 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	new_len;
	size_t	i;
	char	*trimmed_str;
	char	*end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (*s1 && is_in_set(*s1, set))
		s1++;
	end = (char *)(s1 + ft_strlen(s1) - 1);
	while (end > s1 && is_in_set(*end, set))
		end--;
	new_len = (size_t)(end - s1 + 1);
	trimmed_str = (char *)malloc(new_len + 1);
	if (trimmed_str == NULL)
		return (NULL);
	i = 0;
	while (i < new_len)
	{
		trimmed_str[i] = s1[i];
		i++;
	}
	trimmed_str[new_len] = '\0';
	return (trimmed_str);
}

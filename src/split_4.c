/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/12 08:46:52 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Main Function: Reallocate String with Spaces */
char	*realloc_with_spaces(const char *input)
{
	size_t			new_len;
	char			*new_str;
	size_t			j;
	size_t			i;
	const size_t	len = ft_strlen(input);

	new_len = len * 2;
	new_str = malloc(new_len + 1);
	if (!new_str)
		return (NULL);
	j = 0;
	i = 0;
	while (i < len)
	{
		new_str = reallocate_if_necessary(new_str, &new_len, j);
		if (!new_str)
			return (NULL);
		j = copy_or_process_char(new_str, input, &i, j);
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

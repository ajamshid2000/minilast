/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/12 08:24:12 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	free_all_from(char **result, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(result[j]);
		j++;
	}
	free(result);
}

int	ft_count_split(char *s, char c)
{
	size_t	i;
	int		count;
	int		char_count;

	i = 0;
	count = 0;
	char_count = 0;
	while (s[i])
	{
		if (s[i] == c && char_count > 0 && !is_escaped(s, i)
			&& !is_in_double_quote(s, i) && !is_in_quote_simple(s, i))
		{
			count++;
			char_count = 0;
		}
		if (s[i] != c || is_escaped(s, i) || is_in_double_quote(s, i)
			|| is_in_quote_simple(s, i))
			char_count++;
		i++;
	}
	if (char_count > 0)
		return (count + 1);
	return (count);
}

void	init_variables(int *count, int *start, int *num_split, int *i)
{
	*count = 0;
	*start = 0;
	*num_split = 0;
	*i = -1;
}

/* Function to check if the current character meets the condition to split */
int	is_split_condition(char *s, char c, int count, int i)
{
	return ((s[i] == c && count > 0 && !is_escaped(s, i)
			&& !is_in_double_quote(s, i) && !is_in_quote_simple(s, i)) || (s[i
				+ 1] == '\0' && (s[i] != c || (s[i] == c
					&& is_escaped(s, i)))));
}

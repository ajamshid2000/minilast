/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/09 10:19:14 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Helper function to check if a character at index i is escaped*/
int	is_escaped(char *string, size_t i)
{
	int	escape;

	if (string == NULL || i >= ft_strlen(string))
		return (0);
	escape = 0;
	while (i > 0 && string[i - 1] == '\\')
	{
		escape = !escape;
		i--;
	}
	return (escape);
}

/* Helper function to check if a character at index i is inside double quotes */
int	is_in_double_quote(char *string, size_t i)
{
	int		in_double_quote;
	int		in_single_quote;
	size_t	j;

	if (string == NULL || i >= ft_strlen(string))
		return (0);
	in_double_quote = 0;
	in_single_quote = 0;
	j = 0;
	while (j < i)
	{
		if (!is_escaped(string, j))
		{
			if (string[j] == '\"' && !in_single_quote)
				in_double_quote = !in_double_quote;
			else if (string[j] == '\'' && !in_double_quote)
				in_single_quote = !in_single_quote;
		}
		j++;
	}
	return (in_double_quote);
}

/* Helper function to check if a character at index i is inside single quotes */
int	is_in_quote_simple(char *string, size_t i)
{
	int		in_double_quote;
	int		in_single_quote;
	size_t	j;

	if (string == NULL || i >= ft_strlen(string))
		return (0);
	in_double_quote = 0;
	in_single_quote = 0;
	j = 0;
	while (j < i)
	{
		if (!is_escaped(string, j))
		{
			if (string[j] == '\"' && !in_single_quote)
			{
				in_double_quote = !in_double_quote;
			}
			else if (string[j] == '\'' && !in_double_quote)
			{
				in_single_quote = !in_single_quote;
			}
		}
		j++;
	}
	return (in_single_quote);
}

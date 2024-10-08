/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/01 07:17:03 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Utility function to check if a character is a quote*/
int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_escape_char(char c)
{
	return (c == '\\');
}

int	toggle_quote(char c, int *in_single_quotes, int *in_double_quotes)
{
	if (c == '\'' && !*in_double_quotes)
	{
		*in_single_quotes = !*in_single_quotes;
		return (1);
	}
	else if (c == '"' && !*in_single_quotes)
	{
		*in_double_quotes = !*in_double_quotes;
		return (1);
	}
	return (0);
}

int	handle_escape(const char *str, size_t *i, char *new_str, size_t *j)
{
	if (str[*i + 1] == '\'' || str[*i + 1] == '"')
	{
		(*i)++;
		new_str[(*j)++] = str[*i];
		return (1);
	}
	return (0);
}

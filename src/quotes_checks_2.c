/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_checks_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/01 07:12:11 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	init_variable_quotes(size_t *i, size_t *j, int *in_s_q, int *in_d_q)
{
	*i = 0;
	*j = 0;
	*in_s_q = 0;
	*in_d_q = 0;
}

/* Main function to remove quotes that are not escaped or inside other quotes*/
char	*remove_quotes(const char *str)
{
	size_t	i;
	size_t	j;
	char	*new_str;
	int		in_single_quotes;
	int		in_double_quotes;

	init_variable_quotes(&i, &j, &in_single_quotes, &in_double_quotes);
	new_str = (char *)malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (toggle_quote(str[i], &in_single_quotes, &in_double_quotes))
			i++;
		else if (is_escape_char(str[i]) && handle_escape(str, &i, new_str, &j))
			i++;
		else
		{
			new_str[j++] = str[i];
			i++;
		}
	}
	new_str[j] = '\0';
	return (new_str);
}

/* Function to handle quote states (single and double quotes) */
void	handle_quote_state(char ch, int *in_single_quotes,
		int *in_double_quotes)
{
	if (ch == '\'' && !*in_double_quotes)
		*in_single_quotes = !*in_single_quotes;
	else if (ch == '"' && !*in_single_quotes)
		*in_double_quotes = !*in_double_quotes;
}

/* Function to handle escaped characters */
void	process_escaped_character(const char **src, char **dst)
{
	if ((**src == '\\' && (*(*src + 1) == '\\' || *(*src + 1)
				=='\'' || *(*src
					+ 1) == '"' || *(*src + 1) == '$')))
	{
		*(*dst)++ = *++(*src);
	}
	else
	{
		*(*dst)++ = **src;
	}
}

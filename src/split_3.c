/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/12 08:44:47 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Helper Function: Check if Redirection Needs Space*/
int	needs_space_before(const char *input, size_t i)
{
	return (i > 0 && input[i - 1] != ' ' && input[i - 1] != '<' && input[i
			- 1] != '>');
}

int	needs_space_after(const char *input, size_t i)
{
	return (input[i + 1] != ' ' && input[i + 1] != '<' && input[i + 1] != '>');
}

/* Helper Function: Insert Redirection with Spaces */
size_t	insert_redirection_with_spaces(char *new_str, size_t j,
		const char *input, size_t *i)
{
	if (needs_space_before(input, *i))
		new_str[j++] = ' ';
	new_str[j++] = input[*i];
	if ((input[*i] == '<' && input[*i + 1] == '<') || (input[*i] == '>'
			&& input[*i + 1] == '>'))
	{
		new_str[j++] = input[++(*i)];
		if (input[*i + 1] != ' ')
			new_str[j++] = ' ';
	}
	else if (needs_space_after(input, *i))
		new_str[j++] = ' ';
	return (j);
}

/* Helper Function: Reallocate Buffer if Necessary */
char	*reallocate_if_necessary(char *new_str, size_t *new_len, size_t j)
{
	char	*tmp;
	size_t	old_len;

	old_len = *new_len;
	if (j >= *new_len - 4)
	{
		*new_len *= 2;
		tmp = my_realloc(new_str, *new_len + 1, old_len + 1);
		if (!tmp)
		{
			free(new_str);
			return (NULL);
		}
		new_str = tmp;
	}
	return (new_str);
}

/* Helper Function: Copy or Process Character*/
size_t	copy_or_process_char(char *new_str, const char *input, size_t *i,
		size_t j)
{
	if (!is_escaped((char *)input, *i) && !is_in_double_quote((char *)input, *i)
		&& !is_in_quote_simple((char *)input, *i))
	{
		if (input[*i] == '<' || input[*i] == '>')
			j = insert_redirection_with_spaces(new_str, j, input, i);
		else
			new_str[j++] = input[*i];
	}
	else
		new_str[j++] = input[*i];
	return (j);
}

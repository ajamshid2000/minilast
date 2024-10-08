/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/20 11:32:26 by famana           ###   ########.fr       */
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

int	needs_space_before_pipe(const char *input, size_t i)
{
	return (i > 0 && input[i - 1] != ' ');
}

int	needs_space_after_pipe(const char *input, size_t i)
{
	return (input[i + 1] != ' ');
}

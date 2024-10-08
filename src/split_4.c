/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/20 11:30:18 by famana           ###   ########.fr       */
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

size_t	insert_pipe_with_spaces(char *new_str, size_t j, const char *input,
		size_t *i)
{
	if (needs_space_before_pipe(input, *i))
		new_str[j++] = ' ';
	new_str[j++] = input[*i];
	if (needs_space_after_pipe(input, *i))
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
		else if (input[*i] == '|')
			j = insert_pipe_with_spaces(new_str, j, input, i);
		else
			new_str[j++] = input[*i];
	}
	else
		new_str[j++] = input[*i];
	return (j);
}

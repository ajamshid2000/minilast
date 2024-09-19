/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/14 07:26:00 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to reallocate memory when needed */
char	*reallocate_content(char *content, size_t *capacity, size_t new_size)
{
	char	*new_content;

	if (new_size >= *capacity)
	{
		*capacity *= 2;
		new_content = realloc(content, *capacity);
		if (!new_content)
		{
			free(content);
			return (NULL);
		}
		return (new_content);
	}
	return (content);
}

/* Function to append the line to the content */
void	append_line_to_content(char *content, const char *line,
		size_t *content_size)
{
	ft_strcat(content, line);
	*content_size += ft_strlen(line) + 1;
}

/* Function to process a single line and update the content */
int	process_line(char **content, size_t *content_size, size_t *content_capacity,
		const char *line)
{
	size_t	len;

	len = ft_strlen(line);
	*content = reallocate_content(*content, content_capacity, *content_size
			+ len + 2);
	if (!(*content))
	{
		return (0);
	}
	append_line_to_content(*content, line, content_size);
	return (1);
}

int	handle_line_input(char **content, size_t *content_size,
		size_t *content_capacity, const char *stop_word)
{
	char	*line;

	line = read_input_line();
	while (line != NULL)
	{
		if (is_stop_word(line, stop_word))
		{
			free(line);
			break ;
		}
		if (!process_line(content, content_size, content_capacity, line))
		{
			free(line);
			return (0);
		}
		free(line);
		line = read_input_line();
	}
	return (1);
}

char	*handle_heredoc(const char *stop_word)
{
	size_t	content_size;
	size_t	content_capacity;
	char	*content;

	content_size = 0;
	content_capacity = 1024;
	content = allocate_memory(&content_capacity);
	if (!content)
	{
		return (NULL);
	}
	if (!handle_line_input(&content, &content_size, &content_capacity,
			stop_word))
	{
		return (NULL);
	}
	return (content);
}

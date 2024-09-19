/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/14 09:08:58 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to initialize and allocate memory for content */
char	*allocate_memory(size_t *capacity)
{
	char	*content;

	content = malloc(*capacity);
	if (content)
	{
		content[0] = '\0';
	}
	return (content);
}

/* Function to read a line of input from the user */
char	*read_input_line(void)
{
	return (readline("heredoc> "));
}

/* Function to check if the stop word is reached */
int	is_stop_word(const char *line, const char *stop_word)
{
	return (ft_strcmp(line, stop_word) == 0);
}

/* Function to check for null pointers in commands or their components*/
int	is_null_commands(t_commands *commands)
{
	return (commands == NULL || commands->fcommand == NULL);
}

/* Function to add a newline to the end of the heredoc string */
void	add_newline_to_heredoc(t_redirections *redir)
{
	char	*new_here;

	if (redir->here)
	{
		new_here = malloc(ft_strlen(redir->here) + 2);
		if (new_here == NULL)
			return ;
		my_strcpy(new_here, redir->here);
		ft_strcat(new_here, "\n");
		free(redir->here);
		redir->here = new_here;
	}
}

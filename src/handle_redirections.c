/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/27 10:49:24 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_commands	*handle_output_redirection(t_commands *commands,
		char **splited_command, int *i, int id_cmd)
{
	(*i)++;
	return (add_out(commands, id_cmd, splited_command[*i]));
}

t_commands	*handle_append_redirection(t_commands *commands,
		char **splited_command, int *i, int id_cmd)
{
	(*i)++;
	return (add_append(commands, id_cmd, splited_command[*i]));
}

t_commands	*handle_input_redirection(t_commands *commands,
		char **splited_command, int *i, int id_cmd)
{
	(*i)++;
	return (add_in(commands, id_cmd, splited_command[*i]));
}

t_commands	*handle_heredoc_redirection(t_commands *commands,
		char **splited_command, int *i, int id_cmd)
{
	char	*heredoc;

	(*i)++;
	heredoc = handle_heredoc(splited_command[*i]);
	if (heredoc == NULL)
	{
		my_free_cmd(commands);
		printf("Memory allocation for heredoc failed!\n");
		return (NULL);
	}
	commands = add_end_text(commands, id_cmd, heredoc);
	free(heredoc);
	return (commands);
}

t_commands	*handle_redirections(t_commands *commands, char **splited_command,
		int *i, int id_cmd)
{
	if (ft_strcmp(splited_command[*i], ">") == 0)
		return (handle_output_redirection(commands, splited_command, i,
				id_cmd));
	else if (ft_strcmp(splited_command[*i], ">>") == 0)
		return (handle_append_redirection(commands, splited_command, i,
				id_cmd));
	else if (ft_strcmp(splited_command[*i], "<") == 0)
		return (handle_input_redirection(commands, splited_command, i, id_cmd));
	else if (ft_strcmp(splited_command[*i], "<<") == 0)
		return (handle_heredoc_redirection(commands, splited_command, i,
				id_cmd));
	return (commands);
}

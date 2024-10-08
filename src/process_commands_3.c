/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/01 07:16:11 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to handle pipe commands*/
void	process_pipe(int *id_cmd)
{
	handle_pipe_command(id_cmd);
}

/* Function to handle normal commands*/
t_commands	*process_normal(t_commands *commands, int id_cmd, char *command)
{
	commands = handle_normal_command2(commands, id_cmd, command);
	if (commands == NULL)
		return (NULL);
	return (commands);
}

/* Function to process a single command*/
t_commands	*process_single_command(t_commands *commands,
		char **splited_command, int *i, int *id_cmd)
{
	if (is_redirection_operator(splited_command[*i]))
	{
		commands = process_redirection(commands, splited_command, i, *id_cmd);
	}
	else if (is_pipe_operator(splited_command[*i]))
	{
		process_pipe(id_cmd);
	}
	else
	{
		commands = process_normal(commands, *id_cmd, splited_command[*i]);
	}
	return (commands);
}

t_commands	*process_commands(t_commands *commands, char **splited_command)
{
	int	i;
	int	id_cmd;

	i = 0;
	id_cmd = 0;
	while (splited_command[i] != NULL)
	{
		commands = process_single_command(commands, splited_command, &i,
				&id_cmd);
		if (commands == NULL)
			return (NULL);
		i++;
	}
	return (commands);
}

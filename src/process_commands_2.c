/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/01 07:15:47 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	is_redirection_operator(char *cmd)
{
	return (ft_strcmp(cmd, ">") == 0 || ft_strcmp(cmd, ">>") == 0
		|| ft_strcmp(cmd, "<") == 0 || ft_strcmp(cmd, "<<") == 0);
}

int	is_pipe_operator(char *cmd)
{
	return (ft_strcmp(cmd, "|") == 0);
}

t_commands	*handle_redirection(t_commands *commands, char **splited_command,
		int *i, int id_cmd)
{
	commands = process_redirection_commands(commands, splited_command, i,
			id_cmd);
	return (commands);
}

t_commands	*handle_normal_command2(t_commands *commands, int id_cmd, char *cmd)
{
	commands = process_normal_command(commands, id_cmd, cmd);
	return (commands);
}

/* Function to handle redirection commands*/
t_commands	*process_redirection(t_commands *commands, char **splited_command,
		int *i, int id_cmd)
{
	commands = handle_redirection(commands, splited_command, i, id_cmd);
	if (commands == NULL)
		return (NULL);
	return (commands);
}

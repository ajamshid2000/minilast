/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/01 07:16:19 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to append character to result */
void	append_character(const char **src, char **dst)
{
	*(*dst)++ = **src;
}

/* Function to handle pipe commands */
void	handle_pipe_command(int *id_cmd)
{
	(*id_cmd)++;
}

/* Function to handle normal commands */
t_commands	*handle_normal_command(t_commands *commands, int id_cmd,
		char *command)
{
	return (add_cmd_tab(commands, id_cmd, command));
}

/* Handle redirection commands */
t_commands	*process_redirection_commands(t_commands *commands,
		char **splited_command, int *i, int id_cmd)
{
	commands = handle_redirections(commands, splited_command, i, id_cmd);
	if (commands == NULL)
	{
		return (NULL);
	}
	return (commands);
}

/* Handle normal (non-redirection, non-pipe) commands */
t_commands	*process_normal_command(t_commands *commands, int id_cmd,
		char *command)
{
	handle_normal_command(commands, id_cmd, command);
	if (commands == NULL)
	{
		return (NULL);
	}
	return (commands);
}

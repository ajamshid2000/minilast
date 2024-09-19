/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/17 09:32:00 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to ensure the command array has sufficient capacity */
int	ensure_command_capacity(t_commands *commands, int required_capacity)
{
	if (ensure_fcommand_capacity(commands, required_capacity) != 0)
		return (0);
	return (1);
}

/* Function to initialize command if it is NULL */
int	initialize_command_if_needed(t_commands *commands, int id_cmd)
{
	if (commands->fcommand[id_cmd] == NULL)
	{
		commands->fcommand[id_cmd] = initialize_fcommand();
		if (!commands->fcommand[id_cmd])
			return (0);
	}
	return (1);
}

char	*process_command_argument(char *cmd_arg)
{
	char	*cmd_to_add;
	/*
	if (is_quote(cmd_arg[0]) && cmd_arg[ft_strlen(cmd_arg) - 1] == cmd_arg[0])
		cmd_to_add = remove_quotes(cmd_arg);
	else
		cmd_to_add = ft_strdup(cmd_arg);*/
		cmd_to_add=remove_quotes(cmd_arg);
	if (!cmd_to_add)
	{
		printf("Mem allocation failed while processing command argument '%s'.\n",
			cmd_arg);
	}
	return (cmd_to_add);
}

/* Function to add the processed command to the command array */
void	add_processed_command_to_array(t_commands *commands, int id_cmd,
		char *cmd_to_add, char *cmd_arg)
{
	commands->fcommand[id_cmd]->command = add_string_to_array(commands->fcommand[id_cmd]->command,
			cmd_to_add);
	free(cmd_to_add);
	if (!commands->fcommand[id_cmd]->command)
	{
		printf("Failed to add command argument '%s' to fcommand[%d].\n",
			cmd_arg, id_cmd);
	}
}

/* Main function to add a command to the commands table */
void	add_cmd_tab(t_commands *commands, int id_cmd, char *cmd_arg)
{
	char	*cmd_to_add;

	if (!validate_arguments(commands, cmd_arg))
		return ;
	if (!ensure_command_capacity(commands, id_cmd + 1))
		return ;
	if (!initialize_command_if_needed(commands, id_cmd))
		return ;
	cmd_to_add = process_command_argument(cmd_arg);
	if (!cmd_to_add)
		return ;
	add_processed_command_to_array(commands, id_cmd, cmd_to_add, cmd_arg);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/19 16:45:28 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to append character to result */
void	append_character(const char **src, char **dst)
{
	*(*dst)++ = **src;
}

/* Function to handle different types of redirections */
void	handle_redirections(t_commands *commands, char **splited_command,
		int *i, int id_cmd)
{
	char	*heredoc;

	if (ft_strcmp(splited_command[*i], ">") == 0)
	{
		(*i)++;
		add_out(commands, id_cmd, splited_command[*i]);
	}
	else if (ft_strcmp(splited_command[*i], ">>") == 0)
	{
		(*i)++;
		add_append(commands, id_cmd, splited_command[*i]);
	}
	else if (ft_strcmp(splited_command[*i], "<") == 0)
	{
		(*i)++;
		add_in(commands, id_cmd, splited_command[*i]);
	}
	else if (ft_strcmp(splited_command[*i], "<<") == 0 )
	{
		(*i)++;
		heredoc = handle_heredoc(splited_command[*i]);
		add_end_text(commands, id_cmd, heredoc);
		free(heredoc);
		commands->fcommand[id_cmd]->redirections->last_in = 1;
	}
}

/* Function to handle pipe commands */
void	handle_pipe_command(int *id_cmd)
{
	(*id_cmd)++;
}

/* Function to handle normal commands */
void	handle_normal_command(t_commands *commands, int id_cmd, char *command)
{
	add_cmd_tab(commands, id_cmd, command);
}

/* process each command from the input*/
void	process_commands(t_env *env, t_commands *commands,
		char **splited_command, int status)
{
	int	i;
	int	id_cmd;

	i = 0;
	id_cmd = 0;
	while (splited_command[i] != NULL)
	{
		expand_and_replace_variables(env, splited_command, i, status);
		if (ft_strcmp(splited_command[i], ">") == 0
			|| ft_strcmp(splited_command[i], ">>") == 0
			|| ft_strcmp(splited_command[i], "<") == 0
			|| ft_strcmp(splited_command[i], "<<") == 0)
			handle_redirections(commands, splited_command, &i, id_cmd);
		else if (ft_strcmp(splited_command[i], "|") == 0)
			handle_pipe_command(&id_cmd);
		else
			handle_normal_command(commands, id_cmd, splited_command[i]);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_init_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdul-rashed <abdul-rashed@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/18 23:39:12 by abdul-rashe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	count_pipes(char **cmd)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (cmd[i] != NULL)
	{
		if (ft_strcmp(cmd[i], "|") == 0)
			count++;
		i++;
	}
	return (count);
}

/* Function to initialize commands and environment */
void	initialize_commands_and_env(t_commands **commands, t_env **env,
		char **splited_command)
{
	*commands = create_and_init_commands();
	(*commands)->env = *env;
	(*commands)->pipe_count = count_pipes(splited_command);
	(*commands)->fcommand = NULL;
}

/* Function to initialize a newly allocated t_commands structure*/
t_commands	*create_and_init_commands(void)
{
	t_commands	*commands;

	commands = (t_commands *)malloc(sizeof(t_commands));
	if (!commands)
	{
		printf("Memory allocation failed for t_commands.\n");
		return (NULL);
	}
	init_commands(commands);
	return (commands);
}

/* Function to initialize t_commands structure to NULL */
void	init_commands(t_commands *commands)
{
	if (commands == NULL)
		return ;
	commands->status = 0;
	commands->env = NULL;
	commands->fcommand = NULL;
	commands->pipe_count = 0;
}

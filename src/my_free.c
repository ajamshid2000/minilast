/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/08 16:05:39 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	my_free_cmd(t_commands *commands)
{
	int	i;

	i = 0;
	free_redirections(commands);
	while ((commands->fcommand[i]))
	{
		free_table(commands->fcommand[i]->command);
		free(commands->fcommand[i]);
		i++;
	}
	free(commands->fcommand);
	free(commands->child_pid);
	free(commands);
}

void	free_input_split(char *input, char **splited_command)
{
	int	i;

	i = 0;
	while (splited_command[i] != 0)
	{
		free(splited_command[i]);
		i++;
	}
	free(splited_command);
	free(input);
}

void	free_split(char **splited_command)
{
	int	i;

	i = 0;
	while (splited_command[i] != 0)
	{
		free(splited_command[i]);
		i++;
	}
	free(splited_command);
}

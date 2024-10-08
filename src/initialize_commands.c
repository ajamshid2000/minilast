/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/30 09:11:23 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to initialize the fcommand array in commands */
t_commands	*initialize_fcommand_array(t_commands *commands)
{
	if (commands->fcommand == NULL)
	{
		commands->fcommand = (t_fcommand **)malloc(2 * sizeof(t_fcommand *));
		if (commands->fcommand == NULL)
		{
			my_free_cmd(commands);
			printf("Memory allocation for fcommand array failed!\n");
			return (NULL);
		}
		commands->fcommand[0] = NULL;
		commands->fcommand[1] = NULL;
	}
	return (commands);
}

/* Function to initialize a specific fcommand element */
t_commands	*initialize_fcommand_element(t_commands *commands, int id_cmd)
{
	if (commands->fcommand[id_cmd] == NULL)
	{
		commands->fcommand[id_cmd] = (t_fcommand *)malloc(sizeof(t_fcommand));
		if (commands->fcommand[id_cmd] == NULL)
		{
			my_free_cmd(commands);
			printf("Memory allocation for fcommand failed!\n");
			return (NULL);
		}
		commands->fcommand[id_cmd]->error = 0;
		commands->fcommand[id_cmd]->command = NULL;
		commands->fcommand[id_cmd]->redirections = NULL;
	}
	return (commands);
}

/* Function to initialize the redirections structure */
t_commands	*initialize_redirections(t_commands *commands, int id_cmd)
{
	t_redirections	*red;

	if (commands->fcommand[id_cmd]->redirections == NULL)
	{
		red = (t_redirections *)malloc(sizeof(t_redirections));
		commands->fcommand[id_cmd]->redirections = red;
		if (commands->fcommand[id_cmd]->redirections == NULL)
		{
			my_free_cmd(commands);
			printf("Memory allocation for redirections failed!\n");
			return (NULL);
		}
		commands->fcommand[id_cmd]->redirections->out = NULL;
		commands->fcommand[id_cmd]->redirections->append = NULL;
		commands->fcommand[id_cmd]->redirections->in = NULL;
		commands->fcommand[id_cmd]->redirections->here = NULL;
		commands->fcommand[id_cmd]->redirections->last_in = 0;
		commands->fcommand[id_cmd]->redirections->last_out = 0;
	}
	return (commands);
}

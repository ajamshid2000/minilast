/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/19 15:22:57 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to initialize the fcommand array in commands */
void	initialize_fcommand_array(t_commands *commands)
{
	if (commands->fcommand == NULL)
	{
		commands->fcommand = (t_fcommand **)malloc(2 * sizeof(t_fcommand *));
		if (commands->fcommand == NULL)
		{
			printf("Memory allocation for fcommand array failed!\n");
			return ;
		}
		commands->fcommand[0] = NULL;
		commands->fcommand[1] = NULL;
	}
}

/* Function to initialize a specific fcommand element */
void	initialize_fcommand_element(t_commands *commands, int id_cmd)
{
	if (commands->fcommand[id_cmd] == NULL)
	{
		commands->fcommand[id_cmd] = (t_fcommand *)malloc(sizeof(t_fcommand));
		if (commands->fcommand[id_cmd] == NULL)
		{
			printf("Memory allocation for fcommand failed!\n");
			return ;
		}
		commands->fcommand[id_cmd]->error = 0;
		commands->fcommand[id_cmd]->command = NULL;
		commands->fcommand[id_cmd]->redirections = NULL;
	}
}

/* Function to initialize the redirections structure */
void	initialize_redirections(t_commands *commands, int id_cmd)
{
	t_redirections	*red;

	if (commands->fcommand[id_cmd]->redirections == NULL)
	{
		red = (t_redirections *)malloc(sizeof(t_redirections));
		commands->fcommand[id_cmd]->redirections = red;
		if (commands->fcommand[id_cmd]->redirections == NULL)
		{
			printf("Memory allocation for redirections failed!\n");
			return ;
		}
		commands->fcommand[id_cmd]->redirections->out = NULL;
		commands->fcommand[id_cmd]->redirections->append = NULL;
		commands->fcommand[id_cmd]->redirections->in = NULL;
		commands->fcommand[id_cmd]->redirections->here = NULL;
		commands->fcommand[id_cmd]->redirections->last_in = 0;
		commands->fcommand[id_cmd]->redirections->last_out = 0;
	}
}

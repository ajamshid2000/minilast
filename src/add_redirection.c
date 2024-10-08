/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/01 07:13:02 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to add output redirection filename to the redirections structure */
t_commands	*add_output_redirection(t_commands *commands, int id_cmd,
		char *filename)
{
	char	**ntab;
	int		i;

	ntab = add_string_to_table(commands->fcommand[id_cmd]->redirections->out,
			filename);
	if (ntab == NULL)
	{
		my_free_cmd(commands);
		printf("Memory allocation for fcommand array failed!\n");
		return (NULL);
	}
	i = 0;
	while (ntab[i])
		i++;
	commands->fcommand[id_cmd]->redirections->last_out_name = ntab[i - 1];
	commands->fcommand[id_cmd]->redirections->out = ntab;
	return (commands);
}

t_commands	*add_out(t_commands *commands, int id_cmd, char *filename)
{
	commands = initialize_fcommand_array(commands);
	if (commands == NULL)
		return (NULL);
	commands = initialize_fcommand_element(commands, id_cmd);
	if (commands == NULL)
		return (NULL);
	commands = initialize_redirections(commands, id_cmd);
	if (commands == NULL)
		return (NULL);
	if (commands->fcommand[id_cmd]->error == 1)
		return (commands);
	knock_out_char(filename, '"');
	commands = add_output_redirection(commands, id_cmd, filename);
	if (commands == NULL)
	{
		return (NULL);
	}
	if (check_validity_of_outfile(filename, 2))
		commands->fcommand[id_cmd]->error = 1;
	commands->fcommand[id_cmd]->redirections->last_out = 2;
	return (commands);
}

/* Function to add the filename to the append redirection list*/
t_commands	*add_append_redirection(t_commands *commands, int id_cmd,
		char *filename)
{
	char	**ntab;
	int		i;

	ntab = add_string_to_table(commands->fcommand[id_cmd]->redirections->append,
			filename);
	if (ntab == NULL)
	{
		my_free_cmd(commands);
		printf("Memory allocation for fcommand array failed!\n");
		return (NULL);
	}
	i = 0;
	while (ntab[i])
		i++;
	commands->fcommand[id_cmd]->redirections->last_out_name = ntab[i - 1];
	commands->fcommand[id_cmd]->redirections->append = ntab;
	return (commands);
}

t_commands	*add_append(t_commands *commands, int id_cmd, char *filename)
{
	commands = initialize_fcommand_array(commands);
	if (commands == NULL)
		return (NULL);
	commands = initialize_fcommand_element(commands, id_cmd);
	if (commands == NULL)
		return (NULL);
	commands = initialize_redirections(commands, id_cmd);
	if (commands == NULL)
		return (NULL);
	if (commands->fcommand[id_cmd]->error == 1)
		return (commands);
	knock_out_char(filename, '"');
	commands = add_append_redirection(commands, id_cmd, filename);
	if (commands == NULL)
		return (NULL);
	if (check_validity_of_outfile(filename, 1))
		commands->fcommand[id_cmd]->error = 1;
	commands->fcommand[id_cmd]->redirections->last_out = 1;
	return (commands);
}

/* Function to add the filename to the input redirection list */
t_commands	*add_input_redirection(t_commands *commands, int id_cmd,
		char *filename)
{
	char	**ntab;
	int		i;

	ntab = add_string_to_table(commands->fcommand[id_cmd]->redirections->in,
			filename);
	if (ntab == NULL)
	{
		my_free_cmd(commands);
		printf("Memory allocation for fcommand array failed!\n");
		return (NULL);
	}
	i = 0;
	while (ntab[i])
		i++;
	commands->fcommand[id_cmd]->redirections->last_in_name = ntab[i - 1];
	commands->fcommand[id_cmd]->redirections->in = ntab;
	return (commands);
}

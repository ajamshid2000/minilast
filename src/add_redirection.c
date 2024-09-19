/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/19 16:54:10 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	knock_out_char(char *str, char c)
{
	int	i = 0, j;

	i = 0, j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

int	check_validity_of_outfile(char *name, int i)
{
	int	temp;

	if (i == 2)
	{
		temp = open(name, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
		if (temp < 0)
		{
			print_error_write(name);
			return (1);
		}
		close(temp);
	}
	else
	{
		temp = open(name, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
		if (temp < 0)
		{
			print_error_write(name);
			return (1);
		}
		close(temp);
	}
	return (0);
}

/* Function to add output redirection filename to the redirections structure */
void	add_output_redirection(t_commands *commands, int id_cmd, char *filename)
{
	char	**ntab;
	int		i;

	ntab = add_string_to_table(commands->fcommand[id_cmd]->redirections->out,
			filename);
	i = 0;
	while (ntab[i])
		i++;
	commands->fcommand[id_cmd]->redirections->last_out_name = ntab[i - 1];
	commands->fcommand[id_cmd]->redirections->out = ntab;
}

/* Main function decomposed into smaller functions*/
void	add_out(t_commands *commands, int id_cmd, char *filename)
{
	initialize_fcommand_array(commands);
	initialize_fcommand_element(commands, id_cmd);
	initialize_redirections(commands, id_cmd);
	if (commands->fcommand[id_cmd]->error == 1)
		return ;
	knock_out_char(filename, '"');
	add_output_redirection(commands, id_cmd, filename);
	if (check_validity_of_outfile(filename, 2))
		commands->fcommand[id_cmd]->error = 1;
	commands->fcommand[id_cmd]->redirections->last_out = 2;
}

/* Function to add the filename to the append redirection list*/
void	add_append_redirection(t_commands *commands, int id_cmd, char *filename)
{
	char	**ntab;
	int		i;

	ntab = add_string_to_table(commands->fcommand[id_cmd]->redirections->append,
			filename);
	i = 0;
	while (ntab[i])
		i++;
	commands->fcommand[id_cmd]->redirections->last_out_name = ntab[i - 1];
	commands->fcommand[id_cmd]->redirections->append = ntab;
}

/* Main function decomposed into smaller functions */
void	add_append(t_commands *commands, int id_cmd, char *filename)
{
	initialize_fcommand_array(commands);
	initialize_fcommand_element(commands, id_cmd);
	initialize_redirections(commands, id_cmd);
	if (commands->fcommand[id_cmd]->error == 1)
		return ;
	knock_out_char(filename, '"');
	add_append_redirection(commands, id_cmd, filename);
	if (check_validity_of_outfile(filename, 1))
		commands->fcommand[id_cmd]->error = 1;
	commands->fcommand[id_cmd]->redirections->last_out = 1;
}

/* Function to add the filename to the input redirection list */
void	add_input_redirection(t_commands *commands, int id_cmd, char *filename)
{
	char	**ntab;
	int		i;

	ntab = add_string_to_table(commands->fcommand[id_cmd]->redirections->in,
			filename);
	i = 0;
	while (ntab[i])
		i++;
	commands->fcommand[id_cmd]->redirections->last_in_name = ntab[i - 1];
	commands->fcommand[id_cmd]->redirections->in = ntab;
}

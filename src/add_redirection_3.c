/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirection_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/30 09:24:26 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_commands	*add_end_text(t_commands *commands, int id_cmd,
		char *heredoc_content)
{
	if (!validate_inputs(commands, heredoc_content))
		return (commands);
	if (ensure_fcommand_capacity(commands, id_cmd) != 0)
		return (commands);
	if (commands->fcommand[id_cmd] == NULL)
	{
		commands->fcommand[id_cmd] = initialize_fcommand();
		if (!commands->fcommand[id_cmd])
		{
			my_free_cmd(commands);
			printf("Memory allocation for fcommand array failed!\n");
			return (NULL);
		}
		if (commands->fcommand[id_cmd]->error == 1)
			return (commands);
	}
	handle_heredoc_content(commands, id_cmd, heredoc_content);
	commands->fcommand[id_cmd]->redirections->last_in = 1;
	return (commands);
}

/* Function to handle here-document content addition */
void	handle_heredoc_content(t_commands *commands, int id_cmd,
		char *heredoc_content)
{
	if (!ensure_redirections_initialized(commands, id_cmd))
	{
		return ;
	}
	allocate_or_append_heredoc_content
		(&commands->fcommand[id_cmd]->redirections->here,
		heredoc_content);
}

void	knock_out_char(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirection_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/19 16:54:55 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"


int	check_validity_of_infile(char *name)
{
	int	temp;

	temp = open(name, O_RDONLY);
	if (temp == -1)
	{
		print_error_read(name);
		return (1);
	}
	close(temp);
	return (0);
}

/* Main function decomposed into smaller functions */
void	add_in(t_commands *commands, int id_cmd, char *filename)
{
	// printf("%s", filename);
	initialize_fcommand_array(commands);
	initialize_fcommand_element(commands, id_cmd);
	initialize_redirections(commands, id_cmd);
	if (commands->fcommand[id_cmd]->error == 1)
		return ;
	knock_out_char(filename, '"');
	add_input_redirection(commands, id_cmd, filename);
	if (check_validity_of_infile(filename))
		commands->fcommand[id_cmd]->error = 1;
	commands->fcommand[id_cmd]->redirections->last_in = 2;
}

/* Function to check the validity of input arguments */
int	validate_inputs(t_commands *commands, char *heredoc_content)
{
	if (!commands || !heredoc_content)
	{
		printf("Invalid arguments provided to add_end_text.\n");
		return (0);
	}
	return (1);
}

/* Function to ensure the redirections structure is initialized **/
int	ensure_redirections_initialized(t_commands *commands, int id_cmd)
{
	t_redirections	*red;

	if (commands->fcommand[id_cmd]->redirections == NULL)
	{
		red = malloc(sizeof(t_redirections));
		commands->fcommand[id_cmd]->redirections = red;
		if (!commands->fcommand[id_cmd]->redirections)
		{
			printf("Memory allocation for redirections failed.\n");
			return (0);
		}
		commands->fcommand[id_cmd]->redirections->out = NULL;
		commands->fcommand[id_cmd]->redirections->append = NULL;
		commands->fcommand[id_cmd]->redirections->in = NULL;
		commands->fcommand[id_cmd]->redirections->here = NULL;
	}
	return (1);
}

/* Function to allocate or append here-document content */
void	allocate_or_append_heredoc_content(char **here_field,
		char *heredoc_content)
{
	size_t	existing_length;
	size_t	new_length;
	char	*new_here;

	if (*here_field == NULL)
	{
		*here_field = ft_strdup(heredoc_content);
	}
	else
	{
		existing_length = ft_strlen(*here_field);
		new_length = existing_length + ft_strlen(heredoc_content) + 2;
		new_here = (char *)my_realloc(*here_field, new_length, existing_length
				+ 1);
		if (new_here == NULL)
		{
			printf("Memory reallocation for here-document content failed.\n");
			return ;
		}
		ft_strcat(new_here, "\n");
		ft_strcat(new_here, heredoc_content);
		*here_field = new_here;
	}
}

/* Function to handle here-document content addition */
void	handle_heredoc_content(t_commands *commands, int id_cmd,
		char *heredoc_content)
{
	if (!ensure_redirections_initialized(commands, id_cmd))
	{
		return ;
	}
	allocate_or_append_heredoc_content(&commands->fcommand[id_cmd]->redirections->here,
		heredoc_content);
}

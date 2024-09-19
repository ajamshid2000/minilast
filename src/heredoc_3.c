/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/14 09:09:13 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to apply changes related to redirections for a single command */
void	apply_redirection_changes(t_fcommand *cmd)
{
	if (cmd == NULL || cmd->redirections == NULL)
		return ;
	add_newline_to_heredoc(cmd->redirections);
}

/* Function to traverse through each command in the commands structure */
void	traverse_commands(t_commands *commands)
{
	int	i;

	i = 0;
	while (commands->fcommand[i])
	{
		apply_redirection_changes(commands->fcommand[i]);
		i++;
	}
}

/* Main function to add a newline at the end of each heredoc string */
void	add_line_heredoc(t_commands *commands)
{
	if (is_null_commands(commands))
		return ;
	traverse_commands(commands);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_here_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:15:49 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/01 07:17:09 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	redirect_in(t_commands *commands, int i, int in_fd)
{
	int	open_fd;

	if (commands->fcommand[i]->redirections->last_in == 1)
	{
		ft_putstr_fd(commands->fcommand[i]->redirections->here,
			commands->pipe_fd[i][1]);
		dup2(in_fd, 0);
		if (in_fd)
			close(in_fd);
	}
	else
	{
		open_fd = open(commands->fcommand[i]->redirections->last_in_name,
				O_RDONLY);
		dup2(open_fd, 0);
		close(open_fd);
		if (in_fd)
			close(in_fd);
	}
}

void	redirect_out(t_commands *commands, int i, int out_fd)
{
	int	open_fd;

	open_fd = -1;
	if (commands->fcommand[i]->redirections->last_out == 1)
	{
		open_fd = open(commands->fcommand[i]->redirections->last_out_name,
				O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
	}
	else if (commands->fcommand[i]->redirections->last_out == 2)
	{
		open_fd = open(commands->fcommand[i]->redirections->last_out_name,
				O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	}
	dup2(open_fd, 1);
	close(open_fd);
	if (out_fd != 1)
		close(out_fd);
}

void	redirect_commands(t_commands *commands, int i, int in_fd, int out_fd)
{
	if (commands->fcommand[i]->redirections
		&& commands->fcommand[i]->redirections->last_in != 0)
		redirect_in(commands, i, in_fd);
	else
	{
		if (in_fd)
			dup2(in_fd, 0);
		if (in_fd)
			close(in_fd);
	}
	if (commands->fcommand[i]->redirections
		&& commands->fcommand[i]->redirections->last_out != 0)
		redirect_out(commands, i, out_fd);
	else
	{
		if (out_fd != 1)
			dup2(out_fd, 1);
		if (out_fd != 1)
			close(out_fd);
	}
}

int	set_fd(t_fcommand *command, int write_end)
{
	int	i;
	int	temp;

	i = 0;
	while (command->redirections && command->redirections->in
		&& command->redirections->in[i])
	{
		temp = open(command->redirections->in[i], O_RDONLY);
		if (temp == -1)
		{
			print_error_read(command->redirections->in[i]);
			return (1);
		}
		close(temp);
		i++;
	}
	(void)write_end;
	return (0);
}

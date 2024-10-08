/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:58:30 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/30 13:28:02 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	execute_cur_command(t_commands *commands, int **pipe_fd, int j, int i)
{
	t_fcommand	*command;

	(void)j;
	command = commands->fcommand[i];
	if (i == commands->pipe_count && !(command->redirections
			&& ((command->redirections->out && command->redirections->out[0])
				|| (command->redirections->append
					&& command->redirections->append[0]))))
	{
		if ((!is_builtin(commands->fcommand[i]->command)
				&& commands->pipe_count == i))
		{
			execute_builtin(commands->env, commands, i, 1);
			commands->j--;
		}
		else
		{
			if (!commands->fcommand[i]->redirections && i == 0)
				execute_command(commands, i, 0, 1);
			else
				execute_command(commands, i, pipe_fd[i][0], 1);
		}
	}
	else
		execute_command(commands, i, pipe_fd[i][0], pipe_fd[i + 1][1]);
}

int	execute_and_redirect(t_commands *commands, int **pipe_fd, int i)
{
	t_fcommand	*command;
	int			set_fd_return_value;

	set_fd_return_value = commands->fcommand[i]->error;
	(void)command;
	commands->status = set_fd_return_value;
	if (set_fd_return_value == 1)
	{
		close(pipe_fd[i][1]);
		return (-1);
	}
	else
	{
		execute_cur_command(commands, pipe_fd, set_fd_return_value, i);
		close(pipe_fd[i][1]);
	}
	return (0);
}

int	close_pipes_and_wait(t_commands *commands, int i)
{
	close(commands->pipe_fd[i][1]);
	close(commands->pipe_fd[i][0]);
	i = 0;
	while (i <= commands->j)
	{
		if (!commands->status)
		{
			wait(&commands->status);
			commands->status = WEXITSTATUS(commands->status);
		}
		else
			wait(0);
		i++;
	}
	free_pipe(commands);
	return (0);
}

int	execute_pipe(t_commands *commands)
{
	int	i;

	commands->j = commands->pipe_count;
	commands->pipe_fd = (int **)malloc(sizeof(int *) * (commands->pipe_count
				+ 2));
	i = 0;
	while (i <= commands->pipe_count + 1)
	{
		commands->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		pipe(commands->pipe_fd[i]);
		i++;
	}
	i = 0;
	while (i <= commands->pipe_count)
	{
		if (execute_and_redirect(commands, commands->pipe_fd, i) == -1)
			commands->j--;
		if (i >= 0)
			close(commands->pipe_fd[i][0]);
		i++;
	}
	close_pipes_and_wait(commands, i);
	return (0);
}

int	execute_pipes(t_commands *commands)
{
	int	i;

	i = -1;
	while (commands->fcommand[++i])
	{
		if (is_builtin(commands->fcommand[i]->command)
			&& !ft_strchr(commands->fcommand[i]->command[0], '/'))
			commands->fcommand[i]->command[0] = find_path(commands->env,
					commands->fcommand[i]->command);
	}
	execute_pipe(commands);
	if (commands->fcommand[i - 1]->command && commands->fcommand[i
			- 1]->command[0]
		&& !ft_strcmp(commands->fcommand[i - 1]->command[0],
			"exit"))
	{
		return (exit_minishell(commands, i));
	}
	return (0);
}

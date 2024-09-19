/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:34:29 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/19 19:33:07 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	is_builtin(char **command)
{
	if (!ft_strcmp(command[0], "echo") || !ft_strcmp(command[0], "env")
		|| !ft_strcmp(command[0], "exit") || !ft_strcmp(command[0], "unset")
		|| !ft_strcmp(command[0], "export") || !ft_strcmp(command[0], "cd")
		|| !ft_strcmp(command[0], "pwd"))
		return (0);
	return (1);
}

int	cd_pwd(t_env *env, t_commands *commands, int i, int out_fd)
{
	char	buffer[512];

	ft_bzero(buffer, sizeof(buffer));
	if (!ft_strcmp(commands->fcommand[i]->command[0], "pwd"))
	{
		// if (commands->fcommand[i]->command[1])
		// {
		// 	ft_putstr_fd("minishell: pwd : too many arguments\n", 2);
		// 	commands->status = 1;
		// 	return (1);
		// }
		getcwd(buffer, sizeof(buffer));
		if (buffer[0])
			print_pwd(buffer, out_fd, commands);
		commands->status = 0;
	}
	if (!ft_strcmp(commands->fcommand[i]->command[0], "cd"))
	{
		if (cd(env, commands->fcommand[i]->command, out_fd, commands))
			return (1);
	}
	return (0);
}

int	execute_builtin(t_env *env, t_commands *commands, int i, int out_fd)
{
	if (!ft_strcmp(commands->fcommand[i]->command[0], "echo"))
	{
		echo(&commands->fcommand[i]->command[1], out_fd, commands);
		commands->status = 0;
	}
	if (!ft_strcmp(commands->fcommand[i]->command[0], "env"))
	{
		if (commands->fcommand[i]->command[1])
		{
			ft_putstr_fd("minishell: env: too many arguments\n", 2);
			commands->status = 1;
			return (1);
		}
		print_env(env, out_fd);
		commands->status = 0;
	}
	if (!ft_strcmp(commands->fcommand[i]->command[0], "unset"))
		env_remove(env, &commands->fcommand[i]->command[1], commands);
	if (!ft_strcmp(commands->fcommand[i]->command[0], "export"))
		export_multiple(env, commands, i, out_fd);
	if (cd_pwd(env, commands, i, out_fd))
		return (1);
	return (0);
}

char	**child_proccess(t_commands *commands, int i, int in_fd, int out_fd)
{
	extern char	**environ;
	int			open_fd;

	environ = create_env_array(commands->env);
	// ------------------------------------------
	if (commands->fcommand[i]->redirections
		&& commands->fcommand[i]->redirections->last_in != 0)
	{
		if (commands->fcommand[i]->redirections->last_in == 1)
		{
			ft_putstr_fd(commands->fcommand[i]->redirections->here, in_fd);
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
	else
	{
		if (in_fd)
			dup2(in_fd, 0);
		if (in_fd)
			close(in_fd);
	}
	if (commands->fcommand[i]->redirections
		&& commands->fcommand[i]->redirections->last_out != 0)
	{
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
	else
	{
		if (out_fd != 1)
			dup2(out_fd, 1);
		if (out_fd != 1)
			close(out_fd);
	}
	if (commands->fcommand[i + 1] && (!is_builtin(commands->fcommand[i
				+ 1]->command) && commands->pipe_count == i + 1))
	{
		close(commands->pipe_fd[i + 1][0]);
	}
	// (void)out_fd;
	//---------------------------------------------
	// if (out_fd != 1)
	// 	dup2(out_fd, 1);
	// if (out_fd != 1)
	// 	close(out_fd);
	if (!is_builtin(commands->fcommand[i]->command))
	{
		if (execute_builtin(commands->env, commands, i, 1))
			if (!free_all(commands, environ))
				exit(1);
		exit(0);
	}
	else if (ft_strchr(commands->fcommand[i]->command[0], '/'))
		execve(commands->fcommand[i]->command[0],
			commands->fcommand[i]->command, environ);
	return ((char **)environ);
}

void	execute_command(t_commands *commands, int i, int in_fd, int out_fd)
{
	pid_t	pid;
	char	**environ;
	int		j;

	// printf("%i\n", commands->fcommand[i]->redirections->last_out);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		exit(0);
	}
	else if (pid == 0)
	{
		environ = child_proccess(commands, i, in_fd, out_fd);
		j = print_error_execve(commands->fcommand[i]->command[0]);
		free_all(commands, environ);
		exit(j);
	}
}

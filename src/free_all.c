/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:23:29 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/06 11:58:56 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	free_table(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	return (0);
}

int	free_env_stack(t_env *env)
{
	t_env	*temp;
	int		i;

	while (env->next->next)
	{
		temp = env->next;
		i = 0;
		while (env->env[i])
			free(env->env[i++]);
		free(env->env);
		free(env);
		env = temp;
	}
	i = 0;
	while (env->env[i])
		free(env->env[i++]);
	free(env->env);
	free(env->next);
	free(env);
	return (0);
}

int	free_pipe(t_commands *commands)
{
	int	i;

	i = 0;
	while (i <= commands->pipe_count)
	{
		free(commands->pipe_fd[i]);
		i++;
	}
	free(commands->pipe_fd[i]);
	free(commands->pipe_fd);
	return (0);
}

int	free_redirections(t_commands *commands)
{
	int	i;

	i = 0;
	while (commands->fcommand && commands->fcommand[i])
	{
		if (commands->fcommand[i]->redirections)
		{
			free_table(commands->fcommand[i]->redirections->in);
			free_table(commands->fcommand[i]->redirections->out);
			free_table(commands->fcommand[i]->redirections->append);
			if (commands->fcommand[i]->redirections->here)
				free(commands->fcommand[i]->redirections->here);
		}
		if (commands->fcommand[i]->redirections)
			free(commands->fcommand[i]->redirections);
		i++;
	}
	return (0);
}

int	free_all(t_commands *commands, char **environ)
{
	int	i;

	if (environ)
		free_table(environ);
	if (commands)
	{
		free_env_stack(commands->env);
		free_pipe(commands);
		i = 0;
		free_redirections(commands);
		while ((commands->fcommand[i]))
		{
			free_table(commands->fcommand[i]->command);
			free(commands->fcommand[i]);
			i++;
		}
		free(commands->fcommand);
		free(commands);
	}
	rl_clear_history();
	return (0);
}

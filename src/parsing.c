/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/01 13:45:05 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to allocate and initialize the result buffer */
char	*allocate_result_buffer(const char *str)
{
	size_t	initial_size;
	char	*result;

	if (str == NULL)
		initial_size = 1;
	else
		initial_size = ft_strlen(str) + 1;
	result = ft_calloc(initial_size, sizeof(char));
	if (!result)
	{
		perror("calloc");
		exit(EXIT_FAILURE);
	}
	return (result);
}

void	my_free_all_exit(t_env *env, char **splited_command)
{
	free_env_stack(env);
	rl_clear_history();
	free_split(splited_command);
	exit(2);
}

int	do_the_magic(char *input, t_env *env, int *status, char **splited_command)
{
	t_commands	*commands;
	int			exit_flag;

	commands = initialize_commands_and_env(&commands, &env, splited_command);
	if (commands == NULL)
		my_free_all_exit(env, splited_command);
	commands = process_commands(commands, splited_command);
	if (commands == NULL)
		my_free_all_exit(env, splited_command);
	free_input_split(input, splited_command);
	g_ctrl_c_status = 1;
	exit_flag = execute_pipes(commands);
	*status = commands->status;
	my_free_cmd(commands);
	return (exit_flag);
}

int	free_input_and_set_status(char *input, int *status, int i)
{
	if (i == 0)
	{
		free(input);
		*status = 0;
		return (0);
	}
	if (i == 1)
	{
		free(input);
		*status = 2;
		return (1);
	}
	return (0);
}

int	eval2(char *input, t_env *env, int *status)
{
	char	*spaced;
	char	**splited_command;
	int		check;
	char	*cmd;

	cmd = expand_and_replace_variables_string(env, input, *status);
	if (cmd == NULL)
		return (free_input_and_set_status(input, status, 1));
	input = cmd;
	if (is_only_space(input) == 1)
		return (free_input_and_set_status(input, status, 0));
	check = rec_check(input, 0);
	if (check != -1)
		return (if_check_is_1(input, check, status));
	if (!allocate_and_check_memory(input, &spaced, &splited_command))
		return (free_input_and_set_status(input, status, 1));
	if (!check_redirections_and_pipes(splited_command, spaced))
	{
		free_input_split(input, splited_command);
		free(spaced);
		*status = 2;
		return (0);
	}
	free(spaced);
	return (do_the_magic(input, env, status, splited_command));
}

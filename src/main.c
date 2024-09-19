/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdul-rashed <abdul-rashed@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 07:27:49 by famana            #+#    #+#             */
/*   Updated: 2024/09/16 00:15:17 by abdul-rashe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to process the input and handle history*/
int	process_input(char *input, t_env *env, int *status)
{
	int	exit_flag;

	exit_flag = 0;
	if (*input)
	{
		add_history(input);
		exit_flag = eval2(input, env, status);
	}
	return (exit_flag);
}

int	main(void)
{
	char	*input;
	int		exit_flag;
	t_env	*env;
	int		status;

	status = 0;
	env = create_env_stack();
	exit_flag = 0;
	setup_signal_handlers();
	while (1)
	{
		g_ctrl_c_status = 0;
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		exit_flag = process_input(input, env, &status);
		if (exit_flag == 1)
			break ;
	}
	free_env_stack(env);
	rl_clear_history();
	return (status);
}

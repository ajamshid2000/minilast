/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/01 07:14:12 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*expand_and_replace_variables_string(t_env *env,
		char *command, int status)
{
	char		*temp;

	temp = command;
	command = expand_variables2(env, temp, status);
	if (command)
		free(temp);
	else
	{
		free(temp);
		return (NULL);
	}
	return (command);
}

/* Function to initialize the expansion state */
t_expand_state	initialize_expand_state(const char *str)
{
	t_expand_state	state;

	state.src = str;
	state.dst = allocate_result_buffer(str);
	state.in_single_quotes = 0;
	state.in_double_quotes = 0;
	state.initial_size = ft_strlen(str) + 1;
	return (state);
}

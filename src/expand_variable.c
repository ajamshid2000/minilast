/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/17 09:38:00 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to expand variables using the initialized state structure */
char	*expand_variables2(t_env *env, const char *str, int status)
{
	t_expand_state			state;
	char					*result;
	t_expansion_context		ctx;

	state = initialize_expand_state(str);
	result = state.dst;
	ctx = initialize_expansion_context
		(&state.src, &state.dst, result, &state.initial_size);
	while (*state.src)
	{
		handle_quote_state(*state.src, &state.in_single_quotes,
			&state.in_double_quotes);
		if (*state.src == '\\' && !state.in_single_quotes)
			process_escaped_character(&state.src, &state.dst);
		else if (*state.src == '$' && !state.in_single_quotes && *(state.src+1) != '\0' && *(state.src+1) != ' ' && *(state.src+1) != '"')
			ctx.result = process_variable_expansion(env, &ctx, status);
		else
			append_character(&state.src, &state.dst);
		state.src++;
	}
	*state.dst = '\0';
	return (ctx.result);
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

/* Function to handle the processing of each character */
void	process_character(t_env *env, t_expand_state *state,
	char **result, int status)
{
	t_expansion_context	ctx;

	ctx = initialize_expansion_context(&state->src,
			&state->dst,*result, &state->initial_size);
	handle_quote_state(*state->src, &state->in_single_quotes,
		&state->in_double_quotes);
	if (*state->src == '\\' && !state->in_single_quotes)
		process_escaped_character(&state->src, &state->dst);
	else if (*state->src == '$' && !state->in_single_quotes)
		ctx.result = process_variable_expansion(env, &ctx, status);
	else
		append_character(&state->src, &state->dst);
	*result = ctx.result;
}

/* Helper function to find value of environment variable */
char	*find_value_of_env(t_env *env, char *name)
{
	t_env	*temp;

	temp = locate_env(env, name);
	if (temp && temp->env && temp->env[1])
		return (temp->env[1]);
	else
		return (NULL);
}

/* Function to expand and replace variables in a command */
void	expand_and_replace_variables(t_env *env, char **splited_command, int i,
		int status)
{
	char	*temp;

	temp = splited_command[i];
	splited_command[i] = expand_variables2(env, temp, status);
	free(temp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/01 13:38:21 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	should_process_escape(t_expand_state state)
{
	return (*state.src == '\\' && !state.in_single_quotes);
}

int	should_expand_variable(t_expand_state state)
{
	return (*state.src == '$' && !state.in_single_quotes && *(state.src
			+ 1) != '\0' && *(state.src + 1) != ' ' && *(state.src + 1) != '"');
}

void	handle_variable_expansion(t_env *env, t_expand_state *state,
		t_expansion_context *ctx, int status)
{
	ctx->result = process_variable_expansion(env, ctx, status);
	if (*(state->src) != '\0' && *(state->src + 1) != '"')
	{
		append_character_without_space(&state->src, &state->dst);
	}
}

void	expand_string(t_env *env, t_expand_state *state,
		t_expansion_context *ctx, int status)
{
	while (state->src && *state->src)
	{
		handle_quote_state(*state->src, &state->in_single_quotes,
			&state->in_double_quotes);
		if (should_process_escape(*state))
		{
			process_escaped_character(&state->src, &state->dst);
		}
		else if (should_expand_variable(*state))
		{
			handle_variable_expansion(env, state, ctx, status);
		}
		else
		{
			append_character(&state->src, &state->dst);
		}
		if (*state->src != '\0')
		{
			state->src++;
		}
	}
	if (state->dst)
	{
		*state->dst = '\0';
	}
}

char	*expand_variables2(t_env *env, const char *str, int status)
{
	t_expand_state		state;
	t_expansion_context	ctx;
	char				*result;

	state = initialize_expand_state(str);
	if (!state.dst)
	{
		return (NULL);
	}
	result = state.dst;
	ctx = initialize_expansion_context(&state.src, &state.dst, result,
			&state.initial_size);
	expand_string(env, &state, &ctx, status);
	return (ctx.result);
}

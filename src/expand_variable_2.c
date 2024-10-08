/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/01 07:13:59 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to extract variable name from the source string */
const char	*extract_variable_name(const char **src, size_t *var_len)
{
	const char	*var_start;

	if (**src == '$')
	{
		(*src)++;
		if (**src == '?')
		{
			*var_len = 1;
			(*src)++;
			return ("?");
		}
		var_start = *src;
		*var_len = 0;
		while (**src && (isalnum((unsigned char)**src) || **src == '_'))
		{
			(*src)++;
			(*var_len)++;
		}
		return (var_start);
	}
	return (NULL);
}

/* Function to allocate and initialize variable name */
char	*allocate_and_initialize_var_name(const char *var_start, size_t var_len)
{
	char	*var_name;

	var_name = ft_calloc(var_len + 1, sizeof(char));
	if (!var_name)
	{
		return (NULL);
	}
	ft_strncpy(var_name, var_start, var_len);
	return (var_name);
}

char	*process_variable_expansion(t_env *env, t_expansion_context *ctx,
		int status)
{
	size_t		var_len;
	char		*var_name;
	char		*var_value;
	const char	*var_start = extract_variable_name(ctx->src, &var_len);
	int			should_free_var_value;

	should_free_var_value = 0;
	var_name = allocate_and_initialize_var_name(var_start, var_len);
	if (var_name == NULL)
		return (NULL);
	if (var_name[0] == '?')
	{
		var_value = ft_itoa(status);
		should_free_var_value = 1;
	}
	else
		var_value = find_value_of_env(env, var_name);
	free(var_name);
	if (var_value == NULL)
		return (ctx->result);
	ctx->result = expand_variable_and_adjust_result(var_value, ctx->dst,
			ctx->result, ctx->initial_size);
	if (should_free_var_value)
		free(var_value);
	return (ctx->result);
}

/* Function to initialize the expansion context structure */
t_expansion_context	initialize_expansion_context(const char **src, char **dst,
		char *result, size_t *initial_size)
{
	t_expansion_context	ctx;

	ctx.src = src;
	ctx.dst = dst;
	ctx.result = result;
	ctx.initial_size = initial_size;
	return (ctx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/11 11:30:40 by famana           ###   ########.fr       */
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
char	*allocate_and_initialize_var_name(const char *var_start, size_t var_len,
		char *result)
{
	char	*var_name;

	var_name = malloc(var_len + 1);
	if (!var_name)
	{
		perror("malloc");
		free(result);
		exit(EXIT_FAILURE);
	}
	ft_strncpy(var_name, var_start, var_len);
	var_name[var_len] = '\0';
	return (var_name);
}

/* Function to expand the variable and adjust the result buffer */
char	*expand_variable_and_adjust_result(char *var_value, char **dst,
		char *result, size_t *initial_size)
{
	size_t	current_length;
	size_t	needed_size;
	size_t	old_size;

	needed_size = ft_strlen(result) + ft_strlen(var_value) + 1;
	if (needed_size > *initial_size)
	{
		current_length = *dst - result;
		old_size = *initial_size;
		result = my_realloc(result, needed_size, old_size);
		if (!result)
		{
			perror("realloc");
			exit(EXIT_FAILURE);
		}
		*dst = result + current_length;
		*initial_size = needed_size;
	}
	my_strcpy(*dst, var_value);
	*dst += ft_strlen(var_value);
	return (result);
}

/* Function to handle variable expansion */
char	*process_variable_expansion(t_env *env,
	t_expansion_context *ctx, int status)
{
	size_t		var_len;
	char		*var_name;
	char		*var_value;
	const char	*var_start = extract_variable_name(ctx->src, &var_len);

	var_name = allocate_and_initialize_var_name(
			var_start, var_len, ctx->result);
	if (var_name[0] == '?')
		var_value = ft_itoa(status);
	else
	{
		var_value = find_value_of_env(env, var_name);
		free(var_name);
	}
	if (var_value)
		ctx->result = expand_variable_and_adjust_result
			(var_value, ctx->dst, ctx->result, ctx->initial_size);
	(*ctx->src)--;
	return (ctx->result);
}

/* Function to initialize the expansion context structure */
t_expansion_context	initialize_expansion_context(const char **src,
	char **dst, char *result, size_t *initial_size)
{
	t_expansion_context	ctx;

	ctx.src = src;
	ctx.dst = dst;
	ctx.result = result;
	ctx.initial_size = initial_size;
	return (ctx);
}

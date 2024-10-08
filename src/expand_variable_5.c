/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/03 08:59:43 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*allocate_initial_result(char *var_value, char **dst, char *result,
		size_t *initial_size)
{
	size_t	needed_size;

	needed_size = ft_strlen(var_value) + 1;
	result = ft_calloc(needed_size, sizeof(char));
	if (!result)
		return (NULL);
	*dst = result;
	*initial_size = needed_size;
	return (result);
}

int	should_reallocate_result(size_t needed_size, size_t initial_size)
{
	return (needed_size > initial_size);
}

char	*reallocate_result(char *result, char **dst, size_t needed_size,
		size_t *initial_size)
{
	size_t	current_length;
	size_t	old_size;

	current_length = *dst - result;
	old_size = *initial_size;
	result = my_realloc(result, needed_size, old_size);
	if (!result)
		return (NULL);
	*dst = result + current_length;
	*initial_size = needed_size;
	return (result);
}

char	*copy_variable_value(char *dst, char *var_value)
{
	my_strcpy(dst, var_value);
	dst += ft_strlen(var_value);
	return (dst);
}

char	*expand_variable_and_adjust_result(char *var_value, char **dst,
		char *result, size_t *initial_size)
{
	size_t	needed_size;

	if (result != NULL)
	{
		needed_size = ft_strlen(result) + ft_strlen(var_value)
			+ *initial_size + 2;
	}
	else
		result = allocate_initial_result(var_value, dst, result, initial_size);
	if (!result || var_value == NULL)
		return (result);
	if (should_reallocate_result(needed_size, *initial_size))
		result = reallocate_result(result, dst, needed_size, initial_size);
	if (!result)
		return (NULL);
	*dst = copy_variable_value(*dst, var_value);
	return (result);
}

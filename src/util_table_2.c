/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_table_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/11 08:03:10 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	**ft_realloc_table(char **table, int new_count, int old_count)
{
	char	**new_table;
	int		i;

	new_table = (char **)malloc((new_count + 1) * sizeof(char *));
	if (new_table == NULL)
		return (NULL);
	i = 0;
	while (i < old_count && i < new_count)
	{
		new_table[i] = table[i];
		i++;
	}
	free(table);
	return (new_table);
}

/* Helper function to add a string to a NULL-terminated array of strings */
/*
char	**add_string_to_array(char **array, char *new_string)
{
	size_t	count;
	char	**new_array;

	if (!new_string)
	{
		printf("Invalid string provided: NULL string cannot be added.\n");
		return (array);
	}
	count = 0;
	while (array && array[count])
		count++;
	new_array = realloc(array, sizeof(char *) * (count + 2));
	if (!new_array)
	{
		printf("Memory allocation failed while adding string to array.\n");
		return (array);
	}
	new_array[count] = ft_strdup(new_string);
	if (!new_array[count])
	{
		printf("Memory allocation failed while duplicating string.\n");
		new_array[count] = NULL;
		return (new_array);
	}
	new_array[count + 1] = NULL;
	return (new_array);
}
*/

/* Function to calculate the size of a NULL-terminated array of strings */
size_t	get_array_size(char **array)
{
	size_t	count;

	count = 0;
	while (array && array[count])
		count++;
	return (count);
}

/* Function to duplicate a string with error handling */
char	*duplicate_string(char *source)
{
	char	*duplicated;

	if (!source)
	{
		printf("Invalid string provided: NULL string cannot be duplicated.\n");
		return (NULL);
	}
	duplicated = ft_strdup(source);
	if (!duplicated)
	{
		printf("Memory allocation failed while duplicating string.\n");
		return (NULL);
	}
	return (duplicated);
}

/* Function to reallocate memory for a string array with an extra slot */
char	**reallocate_string_array(char **array, size_t new_size)
{
	size_t	old_size;
	char	**new_array;

	old_size = get_array_size(array) + 1;
	new_array = my_realloc(array, sizeof(char *) * new_size, sizeof(char *)
			* old_size);
	if (!new_array)
	{
		printf("Memory allocation failed while reallocating string array.\n");
		return (array);
	}
	return (new_array);
}

/* Main function to add a string to a NULL-terminated array of strings */
char	**add_string_to_array(char **array, char *new_string)
{
	size_t	count;
	char	**new_array;

	if (!new_string)
	{
		printf("Invalid string provided: NULL string cannot be added.\n");
		return (array);
	}
	count = get_array_size(array);
	new_array = reallocate_string_array(array, count + 2);
	if (!new_array)
		return (array);
	new_array[count] = duplicate_string(new_string);
	if (!new_array[count])
	{
		new_array[count] = NULL;
		return (new_array);
	}
	new_array[count + 1] = NULL;
	return (new_array);
}

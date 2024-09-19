/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/18 14:23:30 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to allocate memory for a new table with the initial string**/
char	**allocate_initial_table(char *new_string)
{
	char	**table;

	table = (char **)malloc(2 * sizeof(char *));
	if (table == NULL)
	{
		printf("Memory allocation failed!\n");
		return (NULL);
	}
	table[0] = clone_string(new_string);
	if (table[0] == NULL)
	{
		free(table);
		return (NULL);
	}
	table[1] = NULL;
	return (table);
}

/* Function to count the number of strings in the table */
int	count_strings_in_table(char **table)
{
	int	count;

	count = 0;
	while (table && table[count] != NULL)
	{
		count++;
	}
	return (count);
}

/* Function to reallocate memory for the table */
char	**reallocate_table(char **table, int count)
{
	char	**new_table;

	new_table = ft_realloc_table(table, count + 2, count);
	if (new_table == NULL)
	{
		printf("Memory reallocation failed!\n");
		return (NULL);
	}
	return (new_table);
}

/*Function to add a new string to the table */
int	add_string_to_table_helper(char **table, char *new_string, int count)
{
	table[count] = clone_string(new_string);
	if (table[count] == NULL)
	{
		printf("String cloning failed!\n");
		return (0);
	}
	table[count + 1] = NULL;
	return (1);
}

char	**add_string_to_table(char **table, char *new_string)
{
	int		count;
	char	**new_table;

	if (table == NULL)
	{
		return (allocate_initial_table(new_string));
	}
	count = count_strings_in_table(table);
	new_table = reallocate_table(table, count);
	if (new_table == NULL)
	{
		return (NULL);
	}
	if (!add_string_to_table_helper(new_table, new_string, count))
	{
		free(new_table);
		return (NULL);
	}
	return (new_table);
}

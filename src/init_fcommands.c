/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fcommands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/01 07:15:07 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to calculate the current size of the fcommand array */
int	calculate_current_size(t_commands *commands)
{
	int	current_size;

	current_size = 0;
	while (commands->fcommand[current_size])
	{
		current_size++;
	}
	return (current_size);
}

/* Function to initialize the new slots to NULL */
void	initialize_new_slots(t_fcommand **fcommand, int start_index,
		int end_index)
{
	while (start_index <= end_index)
	{
		fcommand[start_index] = NULL;
		start_index++;
	}
}

/* Function to reallocate memory for the fcommand array */
t_fcommand	**reallocate_fcommand_array(t_fcommand **fcommand,
		int required_size, int current_size)
{
	size_t		old_size;
	size_t		new_size;
	t_fcommand	**new_fcommand;

	old_size = sizeof(t_fcommand *) * (current_size + 1);
	new_size = sizeof(t_fcommand *) * (required_size + 2);
	new_fcommand = my_realloc(fcommand, new_size, old_size);
	if (!new_fcommand)
	{
		printf("Memory reallocation failed for fcommand array.\n");
		return (NULL);
	}
	initialize_new_slots(new_fcommand, current_size, required_size);
	return (new_fcommand);
}

int	ensure_fcommand_capacity(t_commands *commands, int required_size)
{
	t_fcommand	**new_fcommand;
	int			current_size;

	if (allocate_fcommand_array_if_null(commands, required_size) == 0)
	{
		return (0);
	}
	current_size = calculate_current_size(commands);
	if (current_size >= required_size)
	{
		return (0);
	}
	new_fcommand = reallocate_fcommand_array(commands->fcommand, required_size,
			current_size);
	if (!new_fcommand)
	{
		return (-1);
	}
	commands->fcommand = new_fcommand;
	return (0);
}

t_fcommand	*initialize_fcommand(void)
{
	t_fcommand	*new_command;

	new_command = malloc(sizeof(t_fcommand));
	if (!new_command)
	{
		printf("Memory allocation failed for new fcommand.\n");
		return (NULL);
	}
	new_command->error = 0;
	new_command->command = malloc(sizeof(char *));
	new_command->command[0] = NULL;
	new_command->redirections = NULL;
	return (new_command);
}

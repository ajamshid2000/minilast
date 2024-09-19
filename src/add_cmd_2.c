/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/12 06:54:19 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to check for valid arguments */
int	validate_arguments(t_commands *commands, char *cmd_arg)
{
	if (!commands || !cmd_arg)
	{
		printf("Invalid arguments provided to add_cmd_tab.\n");
		return (0);
	}
	return (1);
}

/* Function to allocate the fcommand array if it is NULL */
int	allocate_fcommand_array_if_null(t_commands *commands, int required_size)
{
	if (commands->fcommand == NULL)
	{
		commands->fcommand = ft_calloc(required_size + 2, sizeof(t_fcommand *));
		if (!commands->fcommand)
		{
			printf("Memory allocation failed for fcommand array.\n");
			return (-1);
		}
		return (0);
	}
	return (1);
}

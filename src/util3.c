/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/14 08:24:27 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to process a single redirection */
int	process_redirection(char **args_with_redirect, int *index)
{
	int	redirection_type;

	redirection_type = check_redirection(args_with_redirect[*index]);
	if (redirection_type >= 0)
	{
		if (validate_redirection(args_with_redirect, index) < 0)
		{
			return (-1);
		}
		(*index)++;
	}
	(*index)++;
	return (0);
}

/* Function to check initial redirection validity */
int	check_redirection_validity(char **args_with_redirect, int *index)
{
	if (args_with_redirect[*index + 1] == NULL)
	{
		printf("Error: Missing filename after redirection '%s'\n",
			args_with_redirect[*index]);
		return (-1);
	}
	if (check_redirection(args_with_redirect[*index + 1]) >= 0)
	{
		printf("Error: Another redirection '%s' follows '%s'\n",
			args_with_redirect[*index + 1], args_with_redirect[*index]);
		return (-1);
	}
	return (0);
}

/* Function to validate redirection type */
int	validate_redirection_type(char **args_with_redirect, int *index)
{
	int	redirection_type;

	redirection_type = check_redirection(args_with_redirect[*index]);
	if (redirection_type == 1)
	{
		if (!file_exists(args_with_redirect[*index + 1]))
		{
			printf("Error: File '%s' does not exist for input redirection\n",
				args_with_redirect[*index + 1]);
			return (-1);
		}
	}
	else if (redirection_type == 0 || redirection_type == 2)
	{
		if (!is_valid_filename(args_with_redirect[*index + 1]))
		{
			printf("Error: Invalid filename '%s' for output redirection\n",
				args_with_redirect[*index + 1]);
			return (-1);
		}
	}
	return (0);
}

/* Main function to validate the redirection logic*/
int	validate_redirection(char **args_with_redirect, int *index)
{
	if (check_redirection_validity(args_with_redirect, index) != 0)
	{
		return (-1);
	}
	if (validate_redirection_type(args_with_redirect, index) != 0)
	{
		return (-1);
	}
	return (0);
}

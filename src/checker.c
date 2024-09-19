/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/17 09:52:51 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	pipe_checker(char **cmd)
{
	int	i;
	int	cmp;

	i = 0;
	if (cmd == NULL)
		return (0);
	while (cmd[i] != NULL)
	{
		cmp = ft_strcmp(cmd[i], "|");
		if (cmp == 0 && cmd[i + 1] != NULL && ft_strcmp(cmd[i + 1], "|") == 0)
		{
			return (-1);
		}
		i++;
	}
	return (0);
}

/* Function to handle memory allocation and checking */
int	allocate_and_check_memory(char *input, char **spaced,
		char ***splited_command)
{
	*spaced = realloc_with_spaces(input);
	if (*spaced == 0)
		return (0);
	*splited_command = custom_ft_split(*spaced, ' ');
	if (*splited_command == 0)
	{
		free(*spaced);
		return (0);
	}
	return (1);
}

/* Function to check for redirection and pipes */
/*int	check_redirections_and_pipes(char **splited_command, char *spaced)
{
	if (redirection_checker(splited_command) != 0
		|| pipe_checker(splited_command) != 0)
	{
		free(spaced);
		free(splited_command);
		return (0);
	}
	return (1);
}*/
int	check_redirections_and_pipes(char **splited_command, char *spaced)
{
	(void)spaced;
	if (pipe_checker(splited_command) != 0)
	{
		ft_putstr_fd("parse error near `|'", 2);
		return (0);
	}
	return (1);
}

int	redirection_checker(char **args_with_redirect)
{
	int	index;

	index = 0;
	while (args_with_redirect[index] != NULL)
	{
		if (process_redirection(args_with_redirect, &index) < 0)
		{
			return (-1);
		}
	}
	return (0);
}

/* The provided check_redirection function */
int	check_redirection(char *s)
{
	if (s == NULL || s[0] == 0)
		return (-1);
	if (s[0] == '<' && s[1] == '<')
		return (3);
	if (s[0] == '<')
		return (1);
	if (s[0] == '>' && s[1] == '>')
		return (2);
	if (s[0] == '>')
		return (0);
	return (-1);
}

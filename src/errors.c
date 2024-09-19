/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdul-rashed <abdul-rashed@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:08:54 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/19 00:01:12 by abdul-rashe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	print_second_error(char *name)
{
	if (!access(name, F_OK) && access(name, X_OK) != 0 && ft_strchr(name, '/') != 0)
	{
		ft_putendl_fd("Permission denied", 2);
		return (126);
	}
	if (ft_strchr(name, '/') == 0)
	{
		ft_putendl_fd("command not found", 2);
		return (127);
	}
	if (access(name, F_OK) != 0)
	{
		ft_putendl_fd("No such file or directory", 2);
		return (127);
	}
	return (0);
}

int	print_error_execve(char *name)
{
	int	i;
	DIR	*folder;

	folder = opendir(name);
	ft_putstr_fd("minishell: ", 2);
	i = print_second_error(name);
	if (!i && folder != 0)
	{
		ft_putendl_fd("Is a directory", 2);
		return (126);
	}
	if (!i)
	{
		perror("execve");
		return (1);
	}
	return (i);
}

void	print_error_read(char *name)
{
	DIR	*folder;
	int	fd;

	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	if (access(name, R_OK) == -1)
	{
		perror(": ");
		return ;
	}
	fd = open(name, O_RDONLY);
	folder = opendir(name);
	if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", 2);
	if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", 2);
	if (folder)
		closedir(folder);
	if (fd != -1)
		close(fd);
}

void	print_error_write(char *name)
{
	DIR	*folder;
	int	fd;

	ft_putstr_fd("minishell: ", 2);
	// ft_putstr_fd(name, 2);
	if (access(name, R_OK) == -1)
	{
		perror("");
		return ;
	}
	fd = open(name, O_WRONLY);
	folder = opendir(name);
	if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", 2);
	if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", 2);
	if (folder)
		closedir(folder);
	if (fd != -1)
		close(fd);
}

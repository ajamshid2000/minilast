/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:31:15 by ajamshid          #+#    #+#             */
/*   Updated: 2024/08/20 19:15:35 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*path_creator(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	free(tmp);
	return (path);
}

char	*check_dir(char *bin, char *command)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	item = readdir(folder);
	while (item)
	{
		if (ft_strcmp(item->d_name, command) == 0)
		{
			path = path_creator(bin, item->d_name);
			break ;
		}
		item = readdir(folder);
		if (!item)
			break ;
	}
	closedir(folder);
	return (path);
}

char	*check_all_dirs(t_env *temp, char **args)
{
	char	**bin;
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	bin = ft_split(temp->env[1], ':');
	while (bin[i])
	{
		path = check_dir(bin[i], args[0]);
		if (path)
			break ;
		i++;
	}
	free_table(bin);
	if (path)
		return (path);
	else
		return (NULL);
}

char	*find_path(t_env *env, char **args)
{
	char	*path;
	t_env	*temp;

	path = NULL;
	temp = NULL;
	if (args[0][0] == '/')
	{
		return (args[0]);
	}
	temp = locate_env(env, "PATH");
	if (temp)
	{
		path = check_all_dirs(temp, args);
	}
	if (path)
	{
		free(args[0]);
		return (path);
	}
	else
		return (args[0]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdul-rashed <abdul-rashed@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:18:05 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/20 00:00:19 by abdul-rashe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	sort_export(int i, int j, int n, char **str)
{
	char	*temp;

	while (i < n)
	{
		j = i + 1;
		while (j < n)
		{
			if (ft_strcmp(str[i], str[j]) > 0)
			{
				temp = ft_strdup(str[i]);
				free(str[i]);
				str[i] = ft_strdup(str[j]);
				free(str[j]);
				str[j] = ft_strdup(temp);
				free(temp);
			}
			j++;
		}
		i++;
	}
}

int	print_export(char **str, int out_fd)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (str[n])
		n++;
	sort_export(0, 0, n, str);
	i = 0;
	while (i < n)
	{
		(void)out_fd;
		i++;
	}
	free_table(str);
	return (0);
}

int	create_array2(t_env *temp, char **enva, int i)
{
	char	*temps;

	if (temp->env[0])
	{
		if (temp->env[0][0] == '_' && !temp->env[0][1])
			return (1);
		temps = ft_strjoin(temp->env[0], "=");
		if (temp->env[1])
			enva[i] = ft_strjoin(temps, temp->env[1]);
		else
			enva[i] = ft_strjoin(temps, "''");
		free(temps);
		return (0);
	}
	return (1);
}

char	**create_export_array(t_env *env)
{
	int		i;
	char	**enva;
	t_env	*temp;

	temp = env;
	i = 0;
	while (temp && temp->next)
	{
		temp = temp->next;
		i++;
	}
	enva = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	temp = env;
	while (temp->next)
	{
		if (!create_array2(temp, enva, i))
			i++;
		temp = temp->next;
	}
	enva[i] = NULL;
	return (enva);
}

int	export_one(t_env *env, char *name, char *value, int out_fd)
{
	t_env	*temp;
	char	**str;

	if (check_name(name) == 1)
		return (1);
	if (name && name[0])
	{
		temp = locate_env(env, name);
		if (temp)
		{
			if (value)
			{
				free(temp->env[1]);
				temp->env[1] = ft_strdup(value);
			}
		}
		else
			env_add_last(env, name, value);
		return (0);
	}
	temp = env;
	str = create_export_array(temp);
	print_export(str, out_fd);
	return (0);
}

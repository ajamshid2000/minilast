/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_and_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdul-rashed <abdul-rashed@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:10:29 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/19 21:37:53 by abdul-rashe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	export_multiple(t_env *env, t_commands *commands, int i, int out_fd)
{
	int		j;
	char	**name_value;

	j = 1;
	while (commands->fcommand[i]->command[j])
	{
		name_value = ft_split_one(commands->fcommand[i]->command[j], '=');
		commands->status = export_one(env, name_value[0], name_value[1],
				out_fd);
		j++;
	}
	if (!commands->fcommand[i]->command[1])
		commands->status = export_one(env, NULL, NULL, out_fd);
	return (0);
}

int	print_env(t_env *env, int out_fd)
{
	t_env	*temp;
	char	*temp1;

	temp = env;
	while (temp->next)
	{
		if (temp->env[0] && temp->env[1])
		{
			temp1 = ft_strjoin(temp->env[0], "=");
			temp1 = ft_strjoin_free(temp1, temp->env[1]);
			ft_putstr_fd(temp1, out_fd);
			ft_putstr_fd("\n", out_fd);
			free(temp1);
		}
		temp = temp->next;
	}
	return (0);
}

char	*find_value_of_env2(t_env *env, char *name)
{
	t_env	*temp;
	char	*str;

	temp = NULL;
	temp = locate_env(env, name);
	if (temp)
	{
		str = temp->env[1];
		return (str);
	}
	else
		return (NULL);
}

int	check_name(char *name)
{
	if (!name || !name[0] || ft_strchr(name, '-') || ft_isdigit(name[0]))
	{
		ft_putstr_fd("minishell:", 2);
		ft_putendl_fd(" not a valid identifier", 2);
		return (1);
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:13:59 by ajamshid          #+#    #+#             */
/*   Updated: 2024/08/27 15:14:00 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

//changes
t_env	*locate_env(t_env *env, char *keyword)
{
	t_env	*temp;

	temp = env;
	while (temp->next)
	{
		if (!ft_strncmp(temp->env[0], keyword, ft_strlen(keyword)))
			if (temp->env[0][ft_strlen(keyword)] == '\0')
				return ((temp));
		temp = temp->next;
	}
	return (0);
}
/*parsing different
t_env *locate_env(t_env *env, char *keyword) {
    t_env   *temp;

    temp = env;
    while (temp) {
        if (!ft_strncmp(temp->env[0], keyword, ft_strlen(keyword))) {
            if (temp->env[0][ft_strlen(keyword)] == '\0') {
                return temp;
            }
        }
        temp = temp->next;
    }
    return NULL;
}*/

int	env_add_last(t_env *env, char *name, char *value)
{
	t_env	*temp;
	t_env	*new;
	int		i;

	new = (t_env *)malloc(sizeof(t_env));
	new->env = (char **)malloc(3 * sizeof(char *));
	temp = env;
	i = 0;
	while (temp->next->next->next)
	{
		temp = temp->next;
	}
	new->env[i++] = ft_strdup(name);
	if (value)
		new->env[i++] = ft_strdup(value);
	new->env[i++] = NULL;
	new->next = temp->next;
	temp->next = new;
	return (0);
}

int	remove_if_found(t_env *temp1, char **name, int i)
{
	t_env	*temp2;

	temp2 = NULL;
	if (!ft_strncmp(temp1->next->env[0], name[i], ft_strlen(name[i]))
		&& temp1->next->env[0][ft_strlen(name[i])] == '\0')
	{
		temp2 = temp1->next;
		free_table(temp2->env);
		temp1->next = temp2->next;
		free(temp2);
		return (0);
	}
	return (1);
}

int	env_remove(t_env *env, char **name, t_commands *commands)
{
	t_env	*temp1;
	int		i;

	i = 0;
	temp1 = env;
	while (name[i])
	{
		while (temp1->next->next)
		{
			if (!remove_if_found(temp1, name, i))
				break ;
			temp1 = temp1->next;
		}
		i++;
	}
	commands->status = 0;
	return (0);
}

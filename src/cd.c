/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:24:04 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/08 16:45:48 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	print_pwd(char *pwd, int out_fd, t_commands *commands)
{
	char	*temp;

	temp = ft_strjoin(pwd, "\n");
	ft_putstr_fd(temp, out_fd);
	free(temp);
	commands->status = 0;
}

void	go_to_oldpwd(char *oldpwd, t_env *env, int out_fd)
{
	char	*buffer_two;
	char	*root;
	char	*user;
	char	*oldpwd_copy;

	oldpwd_copy = ft_strdup(oldpwd);
	user = find_value_of_env2(env, "USER");
	root = ft_strjoin("/home/", user);
	buffer_two = getcwd(NULL, 131072);
	export_one(env, "OLDPWD", buffer_two, out_fd);
	free(buffer_two);
	chdir(oldpwd_copy);
	buffer_two = getcwd(NULL, 131072);
	export_one(env, "PWD", buffer_two, out_fd);
	free(buffer_two);
	if (!ft_strncmp(root, oldpwd_copy, ft_strlen(root)))
		printf("~%s\n", oldpwd_copy + ft_strlen(root));
	free(root);
}

void	go_to_pwd(char *buffer, t_env *env, int out_fd)
{
	char	*buffer_two;

	export_one(env, "OLDPWD", buffer, out_fd);
	buffer_two = getcwd(NULL, 131072);
	export_one(env, "PWD", buffer_two, out_fd);
	free(buffer_two);
}

char	*set_dir(t_env *env, char **command, t_commands *commands)
{
	t_env	*home;
	char	*dir;

	if (command && command[0] && !command[1])
	{
		home = locate_env(env, "HOME");
		dir = home->env[1];
		return (dir);
	}
	else if (command && command[0] && command[1])
		dir = command[1];
	if (command && command[0] && command[1] && command[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		commands->status = 1;
		return (NULL);
	}
	return (dir);
}

int	cd(t_env *env, char **command, int out_fd, t_commands *commands)
{
	char	*oldpwd;
	char	*buffer;
	char	*dir;

	if (find_value_of_env2(env, "OLDPWD"))
		oldpwd = find_value_of_env2(env, "OLDPWD");
	dir = set_dir(env, command, commands);
	if (!dir)
		return (1);
	buffer = getcwd(NULL, 131072);
	if (command[1] && !ft_strcmp(command[1], "-"))
		go_to_oldpwd(oldpwd, env, out_fd);
	else if (!chdir(dir))
		go_to_pwd(buffer, env, out_fd);
	else
	{
		free(buffer);
		perror("minishell: cd");
		commands->status = 1;
		return (1);
	}
	free(buffer);
	commands->status = 0;
	return (0);
}

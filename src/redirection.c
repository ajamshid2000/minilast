/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdul-rashed <abdul-rashed@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:51:13 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/20 00:08:00 by abdul-rashe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	append(t_fcommand *command, char *str)
{
	int	i;
	int	temp;

	i = 0;
	(void)str;
	while (command->redirections && command->redirections->append
		&& command->redirections->append[i]
		&& command->redirections->append[i][0])
	{
		temp = open(command->redirections->append[i],
				O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
		if (temp < 0)
		{
			print_error_write(command->redirections->append[i]);
			return (1);
		}
		close(temp);
		i++;
	}
	return (0);
}

int	out_and_append(t_fcommand *command, int read_end, int write_end)
{
	int		i;
	int		temp;
	char	*str;

	i = 0;
	str = NULL;
	(void)read_end;
	(void)write_end;
	while (command->redirections && command->redirections->out
		&& command->redirections->out[i])
	{
		temp = open(command->redirections->out[i], O_CREAT | O_RDWR | O_TRUNC,
				S_IRUSR | S_IWUSR);
		if (temp < 0)
		{
			print_error_write(command->redirections->out[i]);
			return (1);
		}
		close(temp);
		i++;
	}
	if (append(command, str) == 1)
		return (1);
	return (0);
}

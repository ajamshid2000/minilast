/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_here_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdul-rashed <abdul-rashed@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:15:49 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/18 22:38:44 by abdul-rashe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	write_from_in(int temp, int write_end)
{
	int		j;
	char	buffer[512];

	j = 1;
	ft_bzero(buffer, 512);
	while (j > 0)
	{
		j = read(temp, buffer, sizeof(buffer));
		if (j == -1)
		{
			perror("minishell: read");
			return (-1);
		}
		if (j == 0)
			break ;
		write(write_end, buffer, j);
	}
	return (0);
}

int	set_fd(t_fcommand *command, int write_end)
{
	int	i;
	int	temp;

	i = 0;
	while (command->redirections && command->redirections->in
		&& command->redirections->in[i])
	{
		temp = open(command->redirections->in[i], O_RDONLY);
		if (temp == -1)
		{
			print_error_read(command->redirections->in[i]);
			return (1);
		}
		// if (write_from_in(temp, write_end) == -1)
		// 	return (1);
		close(temp);
		i++;
	}
	(void)write_end;
	// if (command->redirections && command->redirections->here
	// 	&& command->redirections->here[0])
	// 	ft_putstr_fd(command->redirections->here, write_end);
	return (0);
}

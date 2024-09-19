/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:51:13 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/19 19:26:49 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	check_pipe_contents(int read_end)
{
	int	bytes_available;

	bytes_available = 0;
	if (ioctl(read_end, FIONREAD, &bytes_available) == -1)
	{
		perror("minishell: ioctl");
		return (0);
	}
	return (bytes_available);
}

char	*read_and_write(int read_end)
{
	long unsigned int	j;
	char				buffer[512];
	char				*str;
	int					bytes_available;

	bytes_available = check_pipe_contents(read_end);
	j = sizeof(buffer) - 1;
	str = NULL;
	// str = (char *)malloc(sizeof(char) * 512);
	// ft_bzero(str, 512);
	while (j)
	{
		printf("it is reading");
		bytes_available = check_pipe_contents(read_end);
		if (bytes_available > 0)
			j = read(read_end, buffer, sizeof(buffer) - 1);
		else
			break ;
		buffer[j] = '\0';
		// str = ft_strjoin_free(str, buffer);
		// if (j < sizeof(buffer) - 1)
		// 	break ;
	}
	return (str);
}

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
		// ft_putstr_fd(str, temp);
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
	// str = read_and_write(read_end);
	str = NULL;
	(void)read_end;
	(void)write_end;
	while (command->redirections && command->redirections->out
		&& command->redirections->out[i])
	{
		// printf("%s\n", command->redirections->out[i]);
		temp = open(command->redirections->out[i], O_CREAT | O_RDWR | O_TRUNC,
				S_IRUSR | S_IWUSR);
		if (temp < 0)
		{
			// printf("here\n");
			print_error_write(command->redirections->out[i]);
			// printf("here\n");
			return (1);
		}
		// ft_putstr_fd(str, temp);
		close(temp);
		i++;
	}
	if (append(command, str) == 1)
		return (1);
	// if (write_end != 1)
	// 	ft_putstr_fd(str, write_end);
	// free(str);
	return (0);
}

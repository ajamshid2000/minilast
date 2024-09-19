/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:42:10 by famana            #+#    #+#             */
/*   Updated: 2023/11/23 07:48:32 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s == 0)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

/*
int	main(void) {
	char *message = "Hello, World!";
	char *message2 = "Hello Hello, World2!";
	int file_descriptor = 1;

	ft_putendl_fd(message, file_descriptor);
	ft_putendl_fd(message2, file_descriptor);
	return (0);
}*/
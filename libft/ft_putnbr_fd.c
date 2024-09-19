/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:42:34 by famana            #+#    #+#             */
/*   Updated: 2023/11/15 10:22:05 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	handle_special_case(int fd)
{
	write(fd, "-2147483648", 11);
}

static void	write_num(int n, int fd)
{
	char	c;

	if (n < 0)
	{
		write(fd, "-", 1);
		write_num(-n, fd);
		return ;
	}
	if (n <= 9)
	{
		c = (char)(n + '0');
		write(fd, &c, 1);
	}
	else
	{
		write_num(n / 10, fd);
		c = (char)(n % 10 + '0');
		write(fd, &c, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		(handle_special_case(fd));
		return ;
	}
	write_num(n, fd);
}

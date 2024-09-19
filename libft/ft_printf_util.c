/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:55:19 by famana            #+#    #+#             */
/*   Updated: 2023/12/19 10:40:53 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_write_string(va_list args)
{
	char	*s;

	s = (char *)va_arg(args, int *);
	if (s == NULL)
		s = "(null)";
	ft_putstr_fd(s, 1);
	return (ft_strlen(s));
}

int	ft_write_percent(void)
{
	write(1, "%", 1);
	return (1);
}

void	ft_write_num(unsigned int n, int fd)
{
	char	c;

	if (n <= 9)
	{
		c = (char)(n + '0');
		write(fd, &c, 1);
	}
	else
	{
		ft_write_num(n / 10, fd);
		c = (char)(n % 10 + '0');
		write(fd, &c, 1);
	}
}

int	ft_rec_hex(unsigned long x)
{
	const char	*hex_chars = "0123456789abcdef";
	int			r;

	if (x == 0)
		return (0);
	r = ft_rec_hex(x / 16);
	write(1, &hex_chars[x % 16], 1);
	return (r + 1);
}

int	ft_write_to_hex(va_list args)
{
	uintptr_t	num;
	void		*p;

	p = (void *)va_arg(args, void *);
	num = (uintptr_t)p;
	if (p == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	return (2 + ft_rec_hex(num));
}

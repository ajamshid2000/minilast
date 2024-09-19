/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:01:52 by famana            #+#    #+#             */
/*   Updated: 2023/12/19 10:40:33 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_write_int(va_list args)
{
	int	j;
	int	sign;
	int	d;

	d = (int)va_arg(args, int);
	sign = 0;
	ft_putnbr_fd(d, 1);
	j = 0;
	if (d == 0)
		return (1);
	if (d < 0)
	{
		d = -d;
		sign = 1;
	}
	while (d != 0)
	{
		d = d / 10;
		j++;
	}
	return (j + sign);
}

int	ft_write_unsigned_int(va_list args)
{
	int				count;
	unsigned int	temp;
	unsigned int	ui;

	ui = (unsigned int)va_arg(args, unsigned int);
	count = 0;
	temp = ui;
	if (ui == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	while (temp != 0)
	{
		temp /= 10;
		count++;
	}
	ft_write_num(ui, 1);
	return (count);
}

int	ft_rec_hex_upper(unsigned long x)
{
	const char	*hex_chars = "0123456789ABCDEF";
	int			r;

	if (x == 0)
		return (0);
	r = ft_rec_hex_upper(x / 16);
	write(1, &hex_chars[x % 16], 1);
	return (r + 1);
}

int	ft_write_lower_hex(va_list args)
{
	unsigned int	x;

	x = (unsigned int)va_arg(args, unsigned int);
	if (x == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	return (ft_rec_hex((unsigned long)x));
}

int	ft_write_upper_hex(va_list args)
{
	unsigned int	upx;

	upx = (unsigned int)va_arg(args, unsigned int);
	if (upx == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	return (ft_rec_hex_upper((unsigned long)upx));
}

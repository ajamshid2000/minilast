/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:07:27 by famana            #+#    #+#             */
/*   Updated: 2023/11/23 07:54:37 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_int_min(const char *nptr)
{
	int	i;

	if (nptr == 0)
		return (0);
	i = 0;
	while (nptr[i])
	{
		if (nptr[i] != "-2147483648"[i])
			return (0);
		i++;
	}
	if ((nptr[i] <= '0' && nptr[i] >= '9') && i == 11)
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\r'
		|| nptr[i] == '\n' || nptr[i] == '\v' || nptr[i] == '\f')
		i++;
	if (is_int_min(nptr + i) == 1)
		return (-2147483648);
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		sign = (nptr[i] == '+') * 2 - 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - 48;
		i++;
	}
	return (sign * result);
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main(void) {
	const char *str = "+\t\v\f\r\n \f1234";
	int number;

	number = atoi(str);

	printf("The integer value is: %d\n", number);

	return (0);
}*/

/*char	n[40] = "+\t\v\f\r\n \f1234";

			int		i1 = atoi(n);
			int		i2 = ft_atoi(n);*/

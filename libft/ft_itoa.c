/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 06:55:29 by famana            #+#    #+#             */
/*   Updated: 2023/11/14 08:59:29 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nb_char(int n)
{
	if (n == -2147483648)
	{
		return (11);
	}
	if (n < 0)
		return (ft_nb_char(-n) + 1);
	if (n < 10)
		return (1);
	return (1 + ft_nb_char(n / 10));
}

static char	*handle_special_case(void)
{
	char	*result;
	int		i;

	result = malloc(12 * sizeof(char));
	if (result == 0)
		return (0);
	i = 0;
	while (i < 12)
	{
		result[i] = "-2147483648"[i];
		i++;
	}
	return (result);
}

static char	*allocate_and_fill(int n, int nb_char)
{
	char	*result;
	int		nb;
	int		i;

	i = 0;
	nb = n;
	result = malloc((nb_char + 1) * sizeof(char));
	if (result == 0)
		return (0);
	result[nb_char] = '\0';
	if (n < 0)
	{
		nb = -n;
	}
	while (i < nb_char)
	{
		result[nb_char - i - 1] = nb % 10 + '0';
		nb = nb / 10;
		i++;
	}
	if (n < 0)
	{
		result[0] = '-';
	}
	return (result);
}

char	*ft_itoa(int n)
{
	int	nb_char;

	nb_char = ft_nb_char(n);
	if (n == -2147483648)
	{
		return (handle_special_case());
	}
	return (allocate_and_fill(n, nb_char));
}
/*
#include <stdio.h>

int	main(void)
{
	// printf("%d\n",ft_nb_char(-75));
	printf("%s", ft_itoa(0));
	// printf("%c%c",ft_itoa(75)[0],ft_itoa(75)[1]);
}
*/
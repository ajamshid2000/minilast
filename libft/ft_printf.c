/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:58:35 by famana            #+#    #+#             */
/*   Updated: 2023/12/19 12:31:07 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_write_char(va_list args)
{
	char	c;

	c = (char)va_arg(args, int);
	write(1, &c, 1);
	return (1);
}

int	ft_handle_format(const char *f, int *i, va_list args)
{
	(*i)++;
	if (f[*i] == 'c')
		return (ft_write_char(args));
	if (f[*i] == 's')
		return (ft_write_string(args));
	if (f[*i] == 'p')
		return (ft_write_to_hex(args));
	if (f[*i] == 'd' || f[*i] == 'i')
		return (ft_write_int(args));
	if (f[*i] == 'u')
		return (ft_write_unsigned_int(args));
	if (f[*i] == 'x')
		return (ft_write_lower_hex(args));
	if (f[*i] == 'X')
		return (ft_write_upper_hex(args));
	if (f[*i] == '%')
		return (ft_write_percent());
	(*i)--;
	return (ft_write_percent());
}

int	ft_printf(const char *f, ...)
{
	int		nb_char;
	int		i;
	va_list	args;

	va_start(args, f);
	nb_char = 0;
	i = 0;
	if (f == 0)
		return (-1);
	while (f[i])
	{
		if (f[i] != '%')
		{
			write(1, &f[i], 1);
			nb_char++;
		}
		else
			nb_char = nb_char + ft_handle_format(f, &i, args);
		i++;
	}
	va_end(args);
	return (nb_char);
}
/*
#include <stdio.h>

int	main(void)
{
	char *str = "world";
	int num = 42;
	unsigned int unum = 420;
	char ch = 'A';

	// Test 1: String
	printf("Standard printf: Hello, %s!\n", str);
	ft_printf("Custom ft_printf: Hello, %s!\n", str);

	// Test 2: Integer
	printf("Standard printf: Number: %d\n", num);
	ft_printf("Custom ft_printf: Number: %d\n", num);

	// Test 3: Unsigned Integer
	printf("Standard printf: Unsigned Number: %u\n", unum);
	ft_printf("Custom ft_printf: Unsigned Number: %u\n", unum);
	// Test 3: Unsigned Integer
	printf("Standard printf: Unsigned Number: %u\n", -1);
	ft_printf("Custom ft_printf: Unsigned Number: %u\n", -1);

	// Test 4: Character
	printf("Standard printf: Character: %c\n", ch);
	ft_printf("Custom ft_printf: Character: %c\n", ch);

	// Test 5: p
	printf("Standard printf: Character: %p\n", (void *)0);
	ft_printf("Custom ft_printf: Character: %p\n", (void *)0);
	// Add more tests as needed for different format specifiers and edge cases
	printf(NULL, (void *)0);
	printf("\nreturn value=%d\n",printf(NULL, (void *)0));
	ft_printf(NULL, (void *)0);
	ft_printf("\nreturn value=%d\n",printf(NULL, (void *)0));
	// test 7:no arg
	printf("Standard printf: Character: %c ...\n");
	ft_printf("Custom ft_printf: Character: %c ...\n");
	printf("\nStandard printf: Character: %", "acv");

	ft_printf("\nCustom ft_printf: Character: %", "acv");
	
	printf("null", (char)0);
	ft_printf("null", (char)0);

	printf("Standard printf: %2 %* %^ %~ \n",1,1,1,1);
	printf("return value=%d\n",printf("Standard printf: %2 %* %^ %~ \n",1,1,1,1));
	ft_printf("Custom printf: %2 %* %^ %~ \n",1,1,1,1);
	printf("return value=%d\n",ft_printf("Custom printf: %2 %* %^ %~ \n",1,1,1,1));
	return (0);
}*/
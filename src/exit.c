/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdul-rashed <abdul-rashed@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:02:24 by abdul-rashe       #+#    #+#             */
/*   Updated: 2024/09/16 00:02:27 by abdul-rashe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_isnumeric(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (i == 0)
		{
			while (str[i++] == ' ')
				if (str[i] == '+' || str[i] == '-')
					i++;
			j = i;
		}
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	if (j == 0 || str[j - 1] == '+' || str[j - 1] == ' ')
		if (ft_strcmp(&str[j], "9223372036854775807") > 0)
			return (1);
	if (str[j - 1] == '-')
		if (ft_strcmp(&str[j], "9223372036854775808") > 0)
			return (1);
	return (0);
}

long long int	ft_atoi_long(char *nptr)
{
	int				i;
	long long int	result;
	int				sign;

	result = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign = -1;
	if (i != 0 && nptr[i - 1] == '-')
		if (ft_strcmp(&nptr[i], "9223372036854775808") == 0)
			return (LLONG_MIN);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - 48;
		i++;
	}
	return (sign * result);
}

int	exit_minishell(t_commands *commands, int i)
{
	if (commands->fcommand[i - 1]->command[1])
	{
		if (commands->fcommand[i - 1]->command[2]
			&& !ft_isnumeric(commands->fcommand[i - 1]->command[1]))
		{
			write(2, "exit\nminishell: Exit: too many arguments\n", 41);
			commands->status = 1;
			return (0);
		}
		else if (ft_isnumeric(commands->fcommand[i - 1]->command[1]))
		{
			write(2, "exit\nminishell: Exit: a numeric argument is required\n",
				53);
			commands->status = 2;
			if (commands->fcommand[i - 1]->command[2])
				return (1);
			return (0);
		}
		commands->status = (ft_atoi_long(commands->fcommand[i - 1]->command[1])
				% 256);
		return (1);
	}
	commands->status = 0;
	return (1);
}

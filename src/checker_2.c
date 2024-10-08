/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/01 07:13:15 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#define TRUE 1
#define FALSE 0

/* Check if the character is a space or other whitespace */
int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
	{
		return (1);
	}
	return (0);
}

int	is_only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (ft_is_space(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	skip_spaces(char *str, int *i)
{
	if (str == NULL || i == NULL)
		return ;
	while (str[*i] == ' ')
		(*i)++;
}

/*return the indice of the error*/
int	check_str(char *s)
{
	int	j;

	j = 0;
	while (s[j] != 0 && !(s[j] == '|' && is_quote_escaped(s, j) == 0))
	{
		if (s[j] != ' ')
		{
			return (-1);
		}
		j++;
	}
	if (s[j] == 0)
		return (0);
	return (-2);
}

int	check_error2(char *s, int start)
{
	int	i;
	int	j;
	int	red;

	i = start;
	while (s[i] != 0 && !(s[i] == '|' && is_quote_escaped(s, i) == 0))
	{
		red = check_redirection_2(s, i);
		if (red != -1)
		{
			if (red == 3 || red == 2)
				i++;
			i++;
			skip_spaces(s, &i);
			if (s[i] == 0 || (s[i] == '|' && is_quote_escaped(s, i) == 0)
				|| check_redirection_2(s, i) != -1)
				return (i);
		}
		i++;
	}
	j = check_str(s);
	if (j != -2)
		return (j);
	return (i);
}

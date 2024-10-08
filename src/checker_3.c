/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/20 12:41:16 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	rec_check(char *s, int start)
{
	int			i;
	const int	len = ft_strlen(s);
	int			c;

	i = start;
	if (s == 0 || s[start] == 0 || start >= len)
		return (-1);
	c = check_error2(s, i);
	if (c != -1)
		return (c);
	while (s[i] != 0 && !(s[i] == '|' && is_quote_escaped(s, i) == 0))
		i++;
	if (s[i] == 0)
		return (-1);
	start = i + 1;
	return (rec_check(s, start));
}

int	if_check_is_1(char *input, int check, int *status)
{
	ft_putstr_fd(" syntax error near unexpected token `", 2);
	if (input[check] == 0)
	{
		ft_putstr_fd("newline", 2);
	}
	else
	{
		ft_putchar_fd(input[check], 2);
		if (input[check] == input[check + 1])
			ft_putchar_fd(input[check], 2);
	}
	ft_putstr_fd("'\n", 2);
	free(input);
	*status = 2;
	return (0);
}

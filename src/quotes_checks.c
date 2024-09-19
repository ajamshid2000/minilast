/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/17 09:22:26 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Utility function to check if a character is a quote*/
int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

/* Function to remove quotes from the beginning and end of a string*/
/*char	*remove_quotes(const char *str)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	if (len < 2)
		return (ft_strdup(str));
	if (is_quote(str[0]) && str[0] == str[len - 1])
	{
		new_str = (char *)malloc(len - 1);
		if (!new_str)
			return (NULL);
		ft_strncpy(new_str, str + 1, len - 2);
		new_str[len - 2] = '\0';
		return (new_str);
	}
	return (ft_strdup(str));
}*/

/* Function to remove quotes that are not escaped or inside other quotes */
char *remove_quotes(const char *str)
{
    size_t i = 0, j = 0;
    size_t len = ft_strlen(str);
    char *new_str = (char *)malloc(len + 1); // Allocate memory for the new string
    int in_single_quotes = 0; // Flag to check if inside single quotes
    int in_double_quotes = 0; // Flag to check if inside double quotes

    if (!new_str)
        return (NULL);

    while (str[i])
    {
        if (str[i] == '\'' && !in_double_quotes && (i == 0 || str[i - 1] != '\\'))
        {
            // Toggle single quote flag if not inside double quotes and not escaped
            in_single_quotes = !in_single_quotes;
        }
        else if (str[i] == '"' && !in_single_quotes && (i == 0 || str[i - 1] != '\\'))
        {
            // Toggle double quote flag if not inside single quotes and not escaped
            in_double_quotes = !in_double_quotes;
        }
        else if (str[i] == '\\' && (str[i + 1] == '\'' || str[i + 1] == '"'))
        {
            // Skip the escape character and copy the next character
            i++;
            new_str[j++] = str[i];
        }
        else
        {
            // Copy the character if it is not a removable quote
            new_str[j++] = str[i];
        }
        i++;
    }
    new_str[j] = '\0'; // Null-terminate the new string
    return new_str;
}

/* Function to handle quote states (single and double quotes) */
void	handle_quote_state(char ch, int *in_single_quotes,
		int *in_double_quotes)
{
	if (ch == '\'' && !*in_double_quotes)
		*in_single_quotes = !*in_single_quotes;
	else if (ch == '"' && !*in_single_quotes)
		*in_double_quotes = !*in_double_quotes;
}

/* Function to handle escaped characters */
void	process_escaped_character(const char **src, char **dst)
{
	if ((**src == '\\' && (*(*src + 1) == '\\' || *(*src
					+ 1) == '\'' || *(*src
					+ 1) == '"' || *(*src + 1) == '$')))
	{
		*(*dst)++ = *++(*src);
	}
	else
	{
		*(*dst)++ = **src;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/14 08:24:10 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	find_unescaped_unquoted_index(const char *string, const char *substring)
{
	size_t	len_string;
	size_t	len_substring;
	size_t	i;

	len_string = ft_strlen(string);
	len_substring = ft_strlen(substring);
	if (len_substring == 0 || len_string < len_substring)
		return (-1);
	i = 0;
	while (i <= len_string - len_substring)
	{
		if (!is_escaped((char *)string, i)
			&& !is_in_double_quote((char *)string, i)
			&& !is_in_quote_simple((char *)string, i))
		{
			if (ft_strncmp(&string[i], substring, len_substring) == 0)
				return (i);
		}
		i++;
	}
	return (-1);
}

/* Function to validate filenames */
int	is_valid_filename(char *filename)
{
	char	*invalid_chars;
	int		i;

	if (filename == NULL || filename[0] == '\0')
		return (0);
	invalid_chars = "<>:\"/\\|?*";
	i = 0;
	while (filename[i] != '\0')
	{
		if (ft_strchr(invalid_chars, filename[i]) != NULL)
			return (0);
		i++;
	}
	return (1);
}

/* Function to check if a file exists using open */
int	file_exists(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		return (0);
	}
	close(fd);
	return (1);
}

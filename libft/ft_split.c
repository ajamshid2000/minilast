/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 07:04:06 by famana            #+#    #+#             */
/*   Updated: 2023/11/23 07:53:57 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_all_from(char **result, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(result[j]);
		j++;
	}
	free(result);
}

static int	ft_count_split(char const *s, char c)
{
	int	i;
	int	count;
	int	char_count;

	i = 0;
	count = 0;
	char_count = 0;
	while (s[i])
	{
		if (s[i] == c && char_count > 0)
		{
			count++;
			char_count = 0;
		}
		if (s[i] != c)
		{
			char_count++;
		}
		i++;
	}
	if (char_count > 0)
		return (count + 1);
	return (count);
}

static void	init_variables(int *count, int *start, int *num_split, int *i)
{
	*count = 0;
	*start = 0;
	*num_split = 0;
	*i = -1;
}

static void	fill_result(char const *s, char c, char **result)
{
	int	i;
	int	count;
	int	start;
	int	num_split;

	init_variables(&count, &start, &num_split, &i);
	while (s[++i])
	{
		if (count == 0)
			start = i;
		if ((s[i] == c && count > 0) || (s[i + 1] == '\0' && s[i] != c))
		{
			result[num_split] = ft_substr(s, start, count + ((s[i + 1] == '\0')
						&& s[i] != c));
			if (result[num_split] == 0)
			{
				free_all_from(result, num_split);
				return ;
			}
			count = 0;
			num_split++;
		}
		else if (s[i] != c)
			count++;
	}
}

char	**ft_split(char const *s, char c)
{
	int		num_split;
	char	**result;

	if (s == 0)
		return (0);
	num_split = ft_count_split(s, c);
	result = malloc((num_split + 1) * sizeof(char *));
	if (result == 0)
		return (0);
	fill_result(s, c, result);
	result[num_split] = 0;
	return (result);
}
/*
// Function to free the memory allocated for the result array
void	free_result(char **result)
{
	char	**ptr;

	ptr = result;
	while (*ptr != NULL)
	{
		free(*ptr);
		ptr++;
	}
	free(result);
}

#include <stdio.h>

int	main(void)
{
	const char	*test_string = "Hello,World,Split,Me";
	char		delimiter;
	char		**result;
	char		**ptr;

	delimiter = ',';
	result = ft_split(test_string, delimiter);
	if (result == NULL)
	{
		printf( "Error: Memory allocation failed.\n");
		return (1);
	}
	printf("Resulting substrings: ");
	ptr = result;
	while (*ptr != NULL)
	{
		printf("%s", *ptr);
		ptr++;
		printf("\n");
	}
	printf("\n");
	free_result(result);
	return (0);
}
*/
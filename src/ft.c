/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:13:44 by ajamshid          #+#    #+#             */
/*   Updated: 2024/08/19 15:34:48 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	int		len;
	char	*newstr;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	newstr = malloc(len);
	if (!newstr)
		return (NULL);
	i = -1;
	while (s1 && s1[++i])
		newstr[i] = s1[i];
	j = 0;
	while (s2 && s2[j])
	{
		newstr[i + j] = s2[j];
		j++;
	}
	if (s1)
		free((void *)s1);
	newstr[i + j] = '\0';
	return (newstr);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int	splitit_one(char const *s, int length, int i, char **splitted)
{
	if (i == 1)
		splitted[i] = ft_strdup(s);
	else
		splitted[i] = ft_substr(s, 0, length);
	if (!splitted[i])
	{
		while (i > 0)
		{
			i--;
			free(splitted[i]);
		}
		free(splitted);
		return (0);
	}
	i++;
	return (i);
}

static int	word_length(char const *s, char c)
{
	int	length;

	if (!ft_strchr(s, c))
		length = ft_strlen(s);
	else
		length = ft_strchr(s, c) - s;
	return (length);
}

char	**ft_split_one(char const *s, char c)
{
	char	**splitted;
	int		length;
	int		i;

	i = 0;
	splitted = (char **)malloc((3) * sizeof(char *));
	if (!s || !splitted)
		return (0);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			length = word_length(s, c);
			i = splitit_one(s, length, i, splitted);
			if (i == 0)
				return (NULL);
			s += length;
		}
		if (i == 2)
			break ;
	}
	splitted[i] = NULL;
	return (splitted);
}

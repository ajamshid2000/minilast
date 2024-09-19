/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:38:47 by famana            #+#    #+#             */
/*   Updated: 2023/12/15 06:53:57 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strncat(char *dest, const char *src, size_t dest_len, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}

ssize_t	ft_find_eol(char *buffer, size_t buffer_size)
{
	size_t	i;

	i = 0;
	while (i < buffer_size)
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_realloc(char *buffer, size_t new_buffer_size,
		size_t old_buffer_size)
{
	char	*new_buffer;
	size_t	i;

	if (new_buffer_size == old_buffer_size)
		return (buffer);
	if (buffer == 0)
	{
		buffer = (char *)malloc((new_buffer_size + 1) * sizeof(char));
		return (buffer);
	}
	new_buffer = (char *)malloc((new_buffer_size + 1) * sizeof(char));
	if (new_buffer == 0)
	{
		free(buffer);
		return (0);
	}
	i = 0;
	while (i < old_buffer_size)
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	free(buffer);
	return (new_buffer);
}
/*return -1 if fail to read the file*/
/*return 0 if EOF found*/

int	ft_fill_buffer(char *buffer, int fd)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		return (-1);
	}
	if (bytes_read == 0)
		return (0);
	buffer[BUFFER_SIZE] = 0;
	return (bytes_read);
}

void	ft_remove_first_n_elements(char *arr, size_t n, ssize_t size)
{
	size_t	i;

	if (n >= (size_t)size)
		return ;
	i = n;
	while (i < (size_t)size)
	{
		arr[i - n] = arr[i];
		i++;
	}
	arr[i - n] = 0;
}

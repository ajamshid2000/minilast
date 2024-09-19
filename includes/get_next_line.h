/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:38:31 by famana            #+#    #+#             */
/*   Updated: 2023/12/15 06:55:00 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define EXTRA_BUFFER_SIZE 1024

typedef struct s_gnl_data
{
	char			*line;
	size_t			line_size;
	int				fd;
}					t_gnl_data;

typedef struct s_extra_buffer
{
	char			*buffer;
	size_t			size;
	size_t			max_size;
}					t_extra_buffer;

typedef struct s_handle_leftovers_data
{
	char			*buffer;
	ssize_t			*buffer_size;
	t_gnl_data		*data;
	t_extra_buffer	*extra;
}					t_handle_leftovers_data;

char				*get_next_line(int fd);
ssize_t				ft_find_eol(char *buffer, size_t buffer_size);
char				*ft_realloc(char *buffer, size_t new_buffer_size,
						size_t old_buffer_size);
int					ft_fill_buffer(char *buffer, int fd);
void				ft_remove_first_n_elements(char *arr, size_t n,
						ssize_t size);
char				*ft_strncat(char *dest, const char *src, size_t dest_len,
						size_t n);

#endif
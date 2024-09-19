/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:39:22 by famana            #+#    #+#             */
/*   Updated: 2023/12/15 06:53:15 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	handle_leftovers_part2(const t_handle_leftovers_data *h,
		ssize_t pos, ssize_t read_or_pos1)
{
	if (pos >= 0)
	{
		h->data->line = ft_realloc(h->data->line, h->data->line_size
				+ h->extra->size + read_or_pos1, h->data->line_size);
		if (h->data->line == 0)
			return (-1);
		ft_strncat(h->data->line, h->extra->buffer, h->data->line_size,
			h->extra->size);
		h->data->line_size = h->data->line_size + h->extra->size;
		ft_strncat(h->data->line, h->buffer, h->data->line_size, read_or_pos1);
		h->data->line_size = h->data->line_size + read_or_pos1;
		ft_remove_first_n_elements(h->buffer, read_or_pos1, *h->buffer_size);
		*h->buffer_size = *h->buffer_size - (read_or_pos1);
		return (1);
	}
	else
	{
		ft_strncat(h->extra->buffer, h->buffer, h->extra->size, read_or_pos1);
		h->extra->size = h->extra->size + read_or_pos1;
		*h->buffer_size = 0;
	}
	return (0);
}

/*overusage of pos for return values*/
static int	handle_leftovers_part1(const t_handle_leftovers_data *h,
		ssize_t pos, ssize_t read_or_pos1)
{
	if (*h->buffer_size != 0)
	{
		if (h->extra->max_size < h->extra->size + read_or_pos1)
		{
			h->data->line = ft_realloc(h->data->line, h->data->line_size
					+ h->extra->size + read_or_pos1 * (pos > 0),
					h->data->line_size);
			if (h->data->line == 0)
				return (-1);
			ft_strncat(h->data->line, h->extra->buffer, h->data->line_size,
				h->extra->size);
			h->data->line_size = h->data->line_size + h->extra->size;
			h->extra->size = 0;
		}
		pos = handle_leftovers_part2(h, pos, read_or_pos1);
		if (pos != 0)
			return (pos);
	}
	return (0);
}

/*overusage of pos for return values*/
static int	handle_leftovers(char *buffer, ssize_t *buffer_size,
		t_gnl_data *data, t_extra_buffer *extra)
{
	ssize_t							read_or_pos1;
	ssize_t							pos;
	const t_handle_leftovers_data	h = {buffer, buffer_size, data, extra};
	const ssize_t					temp = *buffer_size;

	pos = ft_find_eol(buffer, *buffer_size);
	read_or_pos1 = pos + 1;
	if (pos < 0)
		read_or_pos1 = *buffer_size;
	pos = handle_leftovers_part1(&h, pos, read_or_pos1);
	if (pos != 0)
		return (pos);
	if (temp == 0)
	{
		if (extra->size != 0)
		{
			data->line = ft_realloc(data->line, data->line_size + extra->size,
					data->line_size);
			if (data->line == 0)
				return (-1);
			ft_strncat(data->line, extra->buffer, data->line_size, extra->size);
			extra->size = 0;
		}
	}
	return (0);
}

static char	*process_read(t_gnl_data *data, char *buffer, ssize_t *buffer_size,
		t_extra_buffer *extra)
{
	ssize_t	nb_char_read;
	int		cpt;

	if (BUFFER_SIZE <= 0)
		return (0);
	while (1)
	{
		cpt = handle_leftovers(buffer, buffer_size, data, extra);
		if (cpt == -1)
			return (0);
		if (cpt == 1)
			return (data->line);
		nb_char_read = ft_fill_buffer(buffer, data->fd);
		if (nb_char_read == -1)
		{
			free(data->line);
			return (NULL);
		}
		if (nb_char_read == 0 && extra->size == 0)
			return (data->line);
		*buffer_size = nb_char_read;
	}
	return (data->line);
}

char	*get_next_line(int fd)
{
	t_gnl_data		data;
	static ssize_t	buffer_size = 0;
	static char		buffer[BUFFER_SIZE + 1];
	t_extra_buffer	extra;
	char			*result;

	data.fd = fd;
	data.line = 0;
	data.line_size = 0;
	extra.max_size = EXTRA_BUFFER_SIZE;
	if (BUFFER_SIZE > EXTRA_BUFFER_SIZE)
	{
		extra.buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		extra.max_size = BUFFER_SIZE;
	}
	else
		extra.buffer = malloc((EXTRA_BUFFER_SIZE + 1) * sizeof(char));
	extra.size = 0;
	if (extra.buffer == 0)
		return (0);
	result = process_read(&data, buffer, &buffer_size, &extra);
	free(extra.buffer);
	return (result);
}

/*
int	main(void)
{
	int		fd;
	char	*s;

	// test_ft_get_line();
	// test_ft_find_eol();
	// test_ft_realloc();
	// test_ft_fill_buffer();
	// Test 1: Regular file with complete lines
	printf("Test 1: Regular file with complete lines\n");
	fd = open("testfiles/regular_file.txt", O_RDONLY);
	s = get_next_line(fd);
	while (s)
	{
		printf("getline=\n%s", s);
		free(s);
		s = get_next_line(fd);
	}
	free(s);
	/// printf("%s\n\n",get_next_line(fd));
	close(fd);
	// Expected: Regular lines each ending with '\n'
	// Test 2: File with long lines (longer than BUFFER_SIZE)
	printf("\nTest 2: File with long lines\n");
	fd = open("testfiles/long_lines.txt", O_RDONLY);
	s = get_next_line(fd);
	while (s)
	{
		printf("getline=\n%s", s);
		free(s);
		s = get_next_line(fd);
	}
	free(s);
	close(fd);
	// Expected: Lines longer than BUFFER_SIZE are handled correctly
	// Test 3: File that ends without a newline
	printf("\nTest 3: File ending without newline\n");
	fd = open("testfiles/no_newline_end.txt", O_RDONLY);
	s = get_next_line(fd);
	while (s)
	{
		printf("getline=\n%s", s);
		free(s);
		s = get_next_line(fd);
	}
	free(s);
	close(fd);
	// Expected: Last line read correctly without trailing '\n'
	// Test 4: Empty file
	printf("\nTest 4: Empty file\n");
	fd = open("testfiles/empty.txt", O_RDONLY);
	s = get_next_line(fd);
	while (s)
	{
		printf("getline=\n%s", s);
		s = get_next_line(fd);
	}
	close(fd);
	// Expected: No output, function should return NULL immediately
	// Test 5: File with a single newline
	printf("\nTest 5: File with single newline\n");
	fd = open("testfiles/single_newline.txt", O_RDONLY);
	s = get_next_line(fd);
	while (s)
	{
		printf("getline=\n%s", s);
		free(s);
		s = get_next_line(fd);
	}
	free(s);
	close(fd);
	// Expected: A single empty line (just a '\n')
	printf("\nTest 6: File with '\\0' character\n");
	fd = open("binary.bin", O_RDONLY);
	s = get_next_line(fd);
	while (s)
	{
		printf("getline=\n%s", s);
		free(s);
		s = get_next_line(fd);
	}
	free(s);
	close(fd);
	return (0);
}
*/

/*
#include <stdio.h>

int	main(void) {
	FILE *file = fopen("binary.bin", "w"); // Open in text mode
	if (file == NULL) {
		perror("Unable to open the file");
		return (1);
	}

	// Write some text
	fprintf(file, "Hello, World!");

	// Write a null character
	fputc('\0', file);

	// Write more text
	fprintf(file, "More text here");

	fclose(file);
	return (0);
}
*/
/*
#include <errno.h>

void	print_hex(const char *buffer, ssize_t len) {
	for (ssize_t i = 0; i < len; ++i) {
		printf("%02x ", (unsigned char)buffer[i]);
	}
	printf("\n");
}

void	test_read(const char *filename) {
	int fd = open(filename, O_RDONLY);
	if (fd == -1) {
		perror("Error opening file");
		return ;
	}

	char buffer[100];
	ssize_t bytes_read = read(fd, buffer, sizeof(buffer));

	if (bytes_read == -1) {
		perror("Error reading file");
	} else {
		printf("Read %zd bytes from %s: ", bytes_read, filename);
		print_hex(buffer, bytes_read);
	}

	close(fd);
}

int	main(void) {
	printf("Testing read on a text file:\n");
	test_read("testfile.txt");

	printf("\nTesting read on a binary file:\n");
	test_read("binary.bin");

	return (0);
}
*/
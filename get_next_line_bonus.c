/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:07:32 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/05/05 22:07:32 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	free_buf(char **buf)
{
	free(*buf);
	*buf = NULL;
}

// get_next_line: read a line from a file descriptor
// If fd is invalid or BUFFER_SIZE is invalid, return NULL.
// If buf is not initialized, initialize it with buf_init.
// Allocate a line buffer and initialize it with '\0'.
// Read until a newline character is found or EOF is reached with gnl_read.
// return: a line read from the file descriptor
char	*get_next_line(int fd)
{
	static char	*buf[OPEN_MAX + 1] = {};
	char		*line;
	int			line_size;
	int			flag;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || buf_init(buf + fd) < 0)
		return (NULL);
	line_size = BUFFER_SIZE + 1;
	line = (char *)malloc(line_size * sizeof(char));
	if (!line)
		return (free_buf(buf + fd), NULL);
	gnl_bzero(line, line_size);
	flag = gnl_read(fd, &line, &line_size, buf[fd]);
	if (flag == -1 || flag == 0)
	{
		free_buf(buf + fd);
		if (flag == -1 || line[0] == '\0')
			return (free(line), NULL);
	}
	line = gnl_realloc(line, 0, line_size);
	if (line == NULL)
		free_buf(buf + fd);
	return (line);
}

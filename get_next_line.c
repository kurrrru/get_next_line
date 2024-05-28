/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 20:02:39 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/05/28 13:37:29 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// get_next_line: read a line from a file descriptor
// If fd is invalid or BUFFER_SIZE is invalid, return NULL.
// If buf is not initialized, initialize it with buf_init.
// Allocate a line buffer and initialize it with '\0'.
// Read until a newline character is found or EOF is reached with gnl_read.
// return: a line read from the file descriptor
char	*get_next_line(int fd)
{
	static char	*buf = NULL;
	char		*line;
	int			line_size;
	int			flag;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || buf_init(&buf) == -1)
		return (NULL);
	line_size = BUFFER_SIZE + 1;
	line = (char *)malloc(line_size * sizeof(char));
	if (!line)
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	gnl_bzero(line, line_size);
	flag = gnl_read(fd, &line, &line_size, buf);
	if (flag == -1 || flag == 0)
	{
		free(buf);
		buf = NULL;
		if (flag == -1 || line[0] == '\0')
			return (free(line), NULL);
	}
	return (line);
}

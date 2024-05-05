/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 20:02:39 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/05/05 22:02:54 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>	

char	*get_next_line(int fd)
{
	static char	*buf = NULL;
	char		*line;
	int			line_size;
	int			flag;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (buf_init(&buf) == -1)
		return (NULL);
	line_size = BUFFER_SIZE + 1;
	line = (char *)malloc(line_size * sizeof(char));
	if (line == NULL)
		return (NULL);
	gnl_bzero(line, line_size);
	flag = gnl_read(fd, &line, &line_size, buf);
	if (flag == -1 || flag == 0)
	{
		free(buf);
		buf = NULL;
		if (flag == -1)
			return (free(line), NULL);
	}
	return (line);
}

// int main()
// {
// 	char *filename = "test.txt";
// 	char	*line;
// 	int fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("open");
// 		return 1;
// 	}
// 	while (*(line = get_next_line(fd)) && *line)
// 	{
// 		printf("result: %s\n", line);
// 		free(line);
// 	}
// 	free(line);
// 	if (close(fd) == -1)
// 	{
// 		perror("close");
// 		return 1;
// 	}
// 	// do the same thing with test2.txt
// 	filename = "test2.txt";
// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("open");
// 		return 1;
// 	}
// 	line = get_next_line(0);
// 	while (line && *line)
// 	{
// 		printf("result: %s\n", line);
// 		free(line);
// 		line = get_next_line(0);
// 	}
// 	free(line);
// 	if (close(fd) == -1)
// 	{
// 		perror("close");
// 		return 1;
// 	}
// 	return 0;
// }

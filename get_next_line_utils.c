/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 20:02:34 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/05/05 20:44:39 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

// gnl_realloc: Reallocate memory with size.
// If the reallocation fails, free the original pointer and return NULL.
// If the reallocation succeeds, copy the original data to the new pointer.
// Return: the new pointer.
void	*gnl_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	size_t	i;

	new_ptr = malloc(size);
	if (new_ptr == NULL)
		return (free(ptr), NULL);
	i = 0;
	while (((char *)ptr)[i])
	{
		((char *)new_ptr)[i] = ((char *)ptr)[i];
		i++;
	}
	((char *)new_ptr)[i] = '\0';
	free(ptr);
	return (new_ptr);
}

// gnl_strncat: Concatenate src to dst with a limit of BUFFER_SIZE characters.
// Encountering '\n' in src stops concatenation. ('\n' is copied.)
// If the size of dst is not enough, it is reallocated.
// Return: the number of characters concatenated.
int	gnl_strncat(char **dst, char *src, int *line_size)
{
	int	i;
	int	j;

	i = gnl_strlen(*dst);
	j = 0;
	while (src[j] && (j == 0 || src[j - 1] != '\n'))
	{
		if (i + j + 1 >= *line_size)
		{
			*dst = gnl_realloc(*dst, *line_size * 2);
			if (*dst == NULL)
				return (-1);
			*line_size *= 2;
		}
		(*dst)[i + j] = src[j];
		j++;
	}
	(*dst)[i + j] = '\0';
	return (j);
}

void	gnl_bzero(char *buf, size_t size)
{
	while (size--)
		buf[size] = '\0';
}

// gnl_read: Read from fd to buf and concatenate buf to line.
// If the size of line is not enough, it is reallocated in gnl_strncat.
// Return: whether the reading is successful. (1: success, -1: error)
int	gnl_read(int fd, char **line, int *line_size, char *buf)
{
	int			read_size;
	int			cat_size;
	int			i;

	if (line[0])
		cat_size = gnl_strncat(line, buf, line_size);
	if (cat_size == gnl_strlen(buf))
	{
		while (1)
		{
			read_size = read(fd, buf, BUFFER_SIZE);
			if (read_size == -1 || read_size == 0)
				return (read_size);
			buf[read_size] = '\0';
			cat_size = gnl_strncat(line, buf, line_size);
			if (cat_size == -1 || cat_size == 0)
				return (cat_size);
			if (buf[cat_size - 1] == '\n')
				break ;
		}
	}
	i = -1;
	while (++i <= BUFFER_SIZE - cat_size)
		buf[i] = buf[cat_size + i];
	return (1);
}

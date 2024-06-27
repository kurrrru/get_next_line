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

static int	bst_add(t_nodes **t, unsigned int fd)
{
	if (!t)
		return (-1);
	if (!(*t))
	{
		*t = (t_nodes *)malloc(sizeof(t_nodes));
		if (!(*t))
			return (-1);
		(*t)->fd = fd;
		(*t)->buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!((*t)->buf))
			return (free(*t), gnl_bzero((void *)t, sizeof(*t)), -1);
		gnl_bzero((*t)->buf, BUFFER_SIZE + 1);
		(*t)->ch[0] = NULL;
		(*t)->ch[1] = NULL;
		return (1);
	}
	if (fd == (*t)->fd)
		return (1);
	return (bst_add(&((*t)->ch[fd > (*t)->fd]), fd));
}

static t_nodes	*bst_find(t_nodes *t, unsigned int fd)
{
	if (!t)
		return (NULL);
	if (fd == t->fd)
		return (t);
	return (bst_find(t->ch[fd > t->fd], fd));
}

static void	bst_del(t_nodes *t, unsigned int fd)
{
	t_nodes			*c;
	t_nodes			*p;
	unsigned int	new_c_fd;

	if (!t)
		return ;
	c = t->ch[fd > t->fd];
	if (!c)
		return ;
	if (c->fd != fd)
		return (bst_del(c, fd));
	if (!c->ch[0] || !c->ch[1])
	{
		t->ch[fd > t->fd] = c->ch[!(c->ch[0])];
		return (free(c->buf), free(c), gnl_bzero((void *)&c, sizeof(c)));
	}
	p = c;
	while (p->ch[p == c]->ch[0])
		p = p->ch[p == c];
	free(c->buf);
	c->buf = p->ch[p == c]->buf;
	new_c_fd = p->ch[p == c]->fd;
	bst_del(p, new_c_fd);
	c->fd = new_c_fd;
}

// get_next_line: read a line from a file descriptor
// If fd is invalid or BUFFER_SIZE is invalid, return NULL.
// If buf is not initialized, initialize it with buf_init.
// Allocate a line buffer and initialize it with '\0'.
// Read until a newline character is found or EOF is reached with gnl_read.
// return: a line read from the file descriptor
char	*get_next_line(int fd)
{
	static t_nodes	root = {0x80000000, NULL, {NULL, NULL}};
	t_nodes			*buf;
	char			*line;
	int				line_size;
	int				flag;

	buf = &root;
	if (fd < 0 || BUFFER_SIZE <= 0 || bst_add(&buf, fd) < 0)
		return (NULL);
	line_size = BUFFER_SIZE + 1;
	line = (char *)malloc(line_size * sizeof(char));
	if (!line)
		return (bst_del(buf, fd), NULL);
	gnl_bzero(line, line_size);
	flag = gnl_read(fd, &line, &line_size, bst_find(buf, fd)->buf);
	if (flag == -1 || flag == 0)
	{
		bst_del(buf, fd);
		if (flag == -1 || line[0] == '\0')
			return (free(line), NULL);
	}
	line = gnl_realloc(line, 0, line_size);
	if (line == NULL)
		return (bst_del(buf, fd), NULL);
	return (line);
}

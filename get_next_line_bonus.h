/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:07:37 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/05/05 22:07:37 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

typedef struct s_node
{
	unsigned int	fd;
	char			*buf;
	struct s_node	*ch[2];
}	t_nodes;

// # define DEBUG

char	*get_next_line(int fd);
void	*gnl_realloc(void *ptr, size_t new_size, size_t old_size);
int		gnl_strncat(char **dst, const char *src, int *line_size, int *cat_size);
int		gnl_read(int fd, char **line, int *line_size, char *buf);
void	gnl_bzero(void *buf, size_t size);

#endif

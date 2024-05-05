/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 20:02:43 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/05/05 20:26:16 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

// # define DEBUG

char	*get_next_line(int fd);
void	*gnl_realloc(void *ptr, size_t size);
int		gnl_strncat(char **dst, char *src, int *line_size);
int		gnl_read(int fd, char **line, int *line_size, char *buf);
void	gnl_bzero(char *buf, size_t size);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirabet <mmirabet@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 10:52:49 by mmirabet          #+#    #+#             */
/*   Updated: 2020/02/13 12:19:41 by mmirabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int		get_next_line(int fd, char **line);
char	*gnl_get_line(char **lines);
int		gnl_alocbuf(char **buf);
void	gnl_desaloc_lines_buf(char *lines[], char **buf);
int		get_next_line(int fd, char **line);
int		gnl_chk_newl(char *lines);
int		gnl_acc_buf_lines(char **lines, char *buf);
char	*gnl_strdup(const char *s1);
size_t	gnl_strlen(const char *s);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
char	*gnl_strjoin(char **s1, char const *s2);
#endif

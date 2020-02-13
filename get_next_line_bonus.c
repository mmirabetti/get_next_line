/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirabet <mmirabet@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 10:52:57 by mmirabet          #+#    #+#             */
/*   Updated: 2020/02/13 13:18:20 by mmirabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		gnl_alocbuf(char **buf)
{
	if (!(*buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (0);
	return (1);
}

void	gnl_desaloc_lines_buf(char **lines, char **buf)
{
	size_t	i;

	if (*buf)
		free(*buf);
	*buf = NULL;
	i = 0;
	while (i < OPEN_MAX)
	{
		if (lines[i])
		{
			free(lines[i]);
			lines[i] = NULL;
		}
		i++;
	}
}

int		gnl_chk_newl(char *lines)
{
	size_t	i;

	i = 0;
	if (lines)
		while (lines[i])
		{
			if (lines[i] == '\n')
				return (1);
			i++;
		}
	return (0);
}

char	*gnl_get_line(char **lines)
{
	size_t	len;
	char	*aux;
	char	*aux_lines;

	if (!*lines || !gnl_strlen(*lines))
		return (NULL);
	len = 0;
	while ((*lines)[len] && (*lines)[len] != '\n')
		len++;
	aux = gnl_substr(*lines, 0, len);
	len = (*lines)[len] == '\n' ? len + 1 : len;
	aux_lines = gnl_substr(*lines, len, (gnl_strlen(*lines) - len));
	free(*lines);
	*lines = aux_lines;
	return (aux);
}

int		get_next_line(int fd, char **line)
{
	static char	*lines[OPEN_MAX];
	ssize_t		ret;
	char		*buf;

	if (BUFFER_SIZE < 1 || fd < 0 || !line || !gnl_alocbuf(&buf))
		return (-1);
	ret = -1;
	while (!gnl_chk_newl(lines[fd]) && ret)
	{
		if ((ret = read(fd, buf, BUFFER_SIZE)) == -1)
		{
			gnl_desaloc_lines_buf(&(*lines), &buf);
			return (-1);
		}
		else if (ret > 0)
		{
			buf[ret] = '\0';
			gnl_acc_buf_lines(&lines[fd], buf);
		}
	}
	free(buf);
	if (!(*line = gnl_get_line(&lines[fd])))
		*line = gnl_strdup("");
	if (ret == 0)
		return (0);
	return (1);
}

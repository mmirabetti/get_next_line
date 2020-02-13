/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirabet <mmirabet@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 10:52:57 by mmirabet          #+#    #+#             */
/*   Updated: 2020/02/13 10:23:01 by mmirabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

	if (!*lines)
		return (gnl_strdup(""));
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
	buf[BUFFER_SIZE] = '\0';
	ret = -1;
	while (!gnl_chk_newl(lines[fd]) && ret)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
		{
			gnl_desaloc_lines_buf(&(*lines), &buf);
			return (-1);
		}
		else if (ret > 0)
			gnl_acc_buf_lines(&lines[fd], buf);
	}
	*line = gnl_get_line(&lines[fd]);
	return (0);
}

int		main(void)
{
	int		ret;
	int		fd;
	char	*line;

	fd = open("42", O_RDONLY);
	if (fd == -1)
	{
		gnl_putstr_fd("open() error", STDOUT_FILENO);
		return (1);
	}
	ret = get_next_line(fd, &line);
	gnl_putendl_fd(line, STDOUT_FILENO);
	if (close(fd) == -1)
	{
		gnl_putstr_fd("close() error", STDOUT_FILENO);
		return (1);
	}
	return (0);
}

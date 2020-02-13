/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirabet <mmirabet@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 10:53:04 by mmirabet          #+#    #+#             */
/*   Updated: 2020/02/13 13:18:27 by mmirabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;
	size_t	length;

	if (!s)
		return (NULL);
	length = gnl_strlen(s);
	if (start >= length)
		return (gnl_strdup(""));
	if (!(substr = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*gnl_strdup(const char *s1)
{
	char	*dup;
	size_t	i;

	if (s1)
		i = gnl_strlen(s1);
	else
		i = 0;
	if (!(dup = (char *)malloc((i + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*gnl_strjoin(char **s1, char const *s2)
{
	char	*joined;
	size_t	total_len;
	size_t	i;

	if (!*s1)
		*s1 = gnl_strdup("");
	if (!s2)
		s2 = gnl_strdup("");
	total_len = gnl_strlen(*s1) + gnl_strlen(s2);
	if (!(joined = (char *)malloc(sizeof(char) * (total_len + 1))))
		return (NULL);
	i = 0;
	while ((*s1)[i])
	{
		*joined++ = (*s1)[i];
		i++;
	}
	while (*s2)
		*joined++ = *s2++;
	*joined = '\0';
	return (joined - total_len);
}

int		gnl_acc_buf_lines(char **lines, char *buf)
{
	char	*aux;

	if (!buf)
		return (0);
	if (!(aux = gnl_strjoin(lines, buf)))
		return (0);
	if (*lines)
		free(*lines);
	if (!(*lines = gnl_strdup(aux)))
		return (0);
	free(aux);
	return (1);
}

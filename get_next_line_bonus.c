/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:26:07 by ibouram           #+#    #+#             */
/*   Updated: 2024/02/09 18:43:10 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(int fd, char *rest)
{
	ssize_t	i;
	char	*buffer;

	buffer = (char *)malloc((size_t)(BUFFER_SIZE + 1));
	if (!buffer)
		return (free(rest), rest = NULL, NULL);
	i = 1;
	while (!(ft_strchr(rest, '\n')) && i != 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[i] = '\0';
		rest = ft_strjoin(rest, buffer);
		if (!rest)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (rest);
}

char	*ft_getline(char *rest)
{
	char	*line;
	size_t	len;

	len = 0;
	line = NULL;
	while (rest[len] != '\n' && rest[len] != '\0')
		len++;
	if (rest[len] == '\n')
		len++;
	if (len == 0 && rest[len] == '\0')
		return (NULL);
	line = (char *)malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strncpy(rest, line, len);
	return (line);
}

char	*ft_newline(char *rest)
{
	char	*new;
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	while (rest[j] != '\n' && rest[j] != '\0')
		j++;
	if (!rest[j])
	{
		free(rest);
		return (NULL);
	}
	new = (char *)malloc(ft_strlen(rest) - j + 1);
	if (!new)
		return (free(rest), rest = NULL, NULL);
	while (rest[j++])
		new[i++] = rest[j];
	new[i] = '\0';
	free(rest);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*rest[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (fd >= 0 && fd < OPEN_MAX)
		{
			if (rest[fd])
				(free(rest[fd]), rest[fd] = NULL);
		}
		return (NULL);
	}
	rest[fd] = ft_read(fd, rest[fd]);
	if (!rest[fd])
		return (NULL);
	line = ft_getline(rest[fd]);
	if (!line)
	{
		if (rest[fd])
			(free(rest[fd]), rest[fd] = NULL);
		return (NULL);
	}
	rest[fd] = ft_newline(rest[fd]);
	return (line);
}

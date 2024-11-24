/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 23:22:22 by mohben-t          #+#    #+#             */
/*   Updated: 2024/11/24 23:04:09 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*fill_line_buffer(int fd, char *left_c, char *buffer)
{
	ssize_t	b_read;
	char	*tmp;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
		{
			free(left_c);
			return (NULL);
		}
		else if (b_read == 0)
			break ;
		buffer[b_read] = '\0';
		if (!left_c)
			left_c = ft_strdup("");
		tmp = left_c;
		left_c = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (left_c);
}

static char	*extract_line(char *line_buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!line_buffer || !*line_buffer)
		return (NULL);
	while (line_buffer[i] && line_buffer[i] != '\n')
		i++;
	line = ft_substr(line_buffer, 0, i + 1);
	return (line);
}

static char	*set_remainder(char *line_buffer)
{
	size_t	i;
	char	*remainder;

	i = 0;
	if (!line_buffer)
		return (NULL);
	while (line_buffer[i] && line_buffer[i] != '\n')
		i++;
	if (!line_buffer[i])
	{
		free(line_buffer);
		return (NULL);
	}
	remainder = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i - 1);
	free(line_buffer);
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*left_c[OPEN_MAX];
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX || BUFFER_SIZE > 2147483647)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE * sizeof(char)) + 1);
	if (!buffer)
		return (NULL);
	left_c[fd] = fill_line_buffer(fd, left_c[fd], buffer);
	free(buffer);
	if (!left_c[fd])
		return (NULL);
	line = extract_line(left_c[fd]);
	left_c[fd] = set_remainder(left_c[fd]);
	return (line);
}

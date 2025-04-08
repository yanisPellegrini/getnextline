/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypellegr <ypellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:15:06 by ypellegr          #+#    #+#             */
/*   Updated: 2025/04/08 15:13:55 by ypellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	static char *buffer[1024];
	char *line;
	int bytes_read;
	int i;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	while (ft_strchr_index(buffer[fd], '\n') == -1)
	{
		line = malloc(BUFFER_SIZE + 1);
		if (!line)
			return (NULL);
		bytes_read = read(fd, line, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(line);
			return (NULL);
		}
		line[bytes_read] = '\0';
		buffer[fd] = ft_strjoin(buffer[fd], line);
		free(line);
		if (!buffer[fd])
			return (NULL);
	}
}
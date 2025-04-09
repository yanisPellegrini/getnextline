/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypellegr <ypellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:15:06 by ypellegr          #+#    #+#             */
/*   Updated: 2025/04/09 12:39:53 by ypellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int read_line(int fd, char **buffer)
{
	int bytes_read;
	int read_size;

	read_size = BUFFER_SIZE;
	if (BUFFER_SIZE >= 4096)
		read_size = 4096;
	*buffer = malloc(read_size + 1);
	if (!*buffer)
		return (-1);
	bytes_read = read(fd, *buffer, read_size);
	if (bytes_read < 0)
	{
		free(*buffer);
		return (-1);
	}
	(*buffer)[bytes_read] = '\0';
	return (bytes_read);
}

char *extract_line(char **buffer)
{
	char *line;
	char *new_buffer;
	int i;

	i = ft_strchr_index(*buffer, '\n');
	if (i == -1)
		return (NULL);
	line = ft_substr(*buffer, 0, i + 1);
	if (!line)
		return (NULL);
	new_buffer = ft_substr(*buffer, i + 1, ft_strlen(*buffer) - i - 1);
	free(*buffer);
	*buffer = new_buffer;
	if (!*buffer)
		return (NULL);
	
	return (line);
}

char *get_next_line(int fd)
{
    static char *buffer;
    char temp[BUFFER_SIZE + 1];
    char *line;
    char *new_buffer;
    int bytes_read;

    if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
        return (NULL);
    if (!buffer)
        buffer = ft_strdup("");
    while (ft_strchr_index(buffer, '\n') == -1)
    {
        bytes_read = read(fd, temp, BUFFER_SIZE);
        if (bytes_read <= 0)
        {
            if (bytes_read == 0 && *buffer != '\0')
            {
                line = ft_strdup(buffer);
                free(buffer);
                buffer = NULL;
                return (line);
            }
            free(buffer);
            buffer = NULL;
            return (NULL);
        }
        temp[bytes_read] = '\0';
        new_buffer = ft_strjoin(buffer, temp);
        if (!new_buffer)
        {
            free(buffer);
            return (NULL);
        }
        free(buffer);
        buffer = new_buffer;
    }
    line = extract_line(&buffer);
    return (line);
}

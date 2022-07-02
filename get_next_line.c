/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcaetano <wcaetano@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 23:13:02 by wcaetano          #+#    #+#             */
/*   Updated: 2022/06/22 10:58:13 by wcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int				i;
	char			*line_buffer;
	static t_buffer	buffer;

	line_buffer = NULL;
	if (!buffer.last_read)
		load_buffer(&buffer, read(fd, buffer.buffer, BUFFER_SIZE));
	while (buffer.last_read > 0)
	{
		if (buffer.start != buffer.end)
		{
			i = find(&buffer, '\n');
			line_buffer = get_line(line_buffer, &buffer, i);
			if (!line_buffer)
				return (NULL);
			buffer.start += i;
			if (line_buffer[ft_strlen(line_buffer) - 1] == '\n')
				return (line_buffer);
		}
		else
			load_buffer(&buffer, read(fd, buffer.buffer, BUFFER_SIZE));
	}
	return (line_buffer);
}

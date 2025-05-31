/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nix <nix@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:24:20 by nix               #+#    #+#             */
/*   Updated: 2025/05/18 17:59:58 by nix              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_buffer_until_newline(int fd, char *buffer)
{
	char	*buf;
	char	*tmp;
	ssize_t	bytes_read;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (ft_strchr(buffer, '\n') == NULL)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buf), free(buffer), NULL);
		if (bytes_read == 0)
			break ;
		buf[bytes_read] = '\0';
		if (!buffer)
			buffer = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(buffer, buf);
			(free(buffer), buffer = tmp);
		}
	}
	return (free(buf), buffer);
}

char	*get_next_line(int fd)
{
	char		*tmp;
	char		*line;
	char		*newline;
	static char	*buffers[FD_MAX];
	size_t		line_len;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_MAX)
		return (NULL);
	buffers[fd] = fill_buffer_until_newline(fd, buffers[fd]);
	if (!buffers[fd] || ft_strlen_mod(buffers[fd]) == 0)
		return (free(buffers[fd]), buffers[fd] = NULL, NULL);
	newline = ft_strchr(buffers[fd], '\n');
	if (newline)
	{
		line_len = newline - buffers[fd] + 1;
		line = ft_substr(buffers[fd], 0, line_len);
		tmp = ft_strdup(buffers[fd] + line_len);
		(free(buffers[fd]), buffers[fd] = tmp);
	}
	else
	{
		line = ft_strdup(buffers[fd]);
		(free(buffers[fd]), buffers[fd] = NULL);
	}
	return (line);
}

// int main(void)
// {
// 	int fd1 = open("test", O_RDONLY);
// 	int fd2 = open("test2", O_RDONLY);
// 	char *line;

// 	//Read lines alternately from fd1 and fd2
// 	while (1)
// 	{
// 		line = get_next_line(fd1);
// 		if (line)
// 		{
// 			printf("FD1: %s", line);
// 			free(line);
// 		}
// 		line = get_next_line(fd2);
// 		if (line) {
// 			printf("FD2: %s", line);
// 			free(line);
// 		}
// 		if (!line) // Break when both fds reach EOF
// 			break;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	return (0);
//  }
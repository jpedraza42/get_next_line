/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedraza < jpedraza@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:19:16 by jpedraza          #+#    #+#             */
/*   Updated: 2026/06/01 14:25:05 by jpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*store[1024];
	char		*line;
	char		*tmp;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	store[fd] = ft_read_and_store(fd, store[fd]);
	if (!store[fd])
		return (NULL);
	tmp = store[fd];
	line = ft_extract_line(store[fd]);
	if (!line)
	{
		store[fd] = NULL;
		return (free(tmp), NULL);
	}
	store[fd] = ft_extract_rest(store[fd]);
	free(tmp);
	return (line);
}

char	*ft_read_and_store(int fd, char *s1)
{
	char	*buffer;
	int		bytes;
	char	*tmp;

	bytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (ft_str_end_line(s1) < 0 && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (free(buffer), free(s1), NULL);
		buffer[bytes] = '\0';
		if (bytes > 0)
		{
			tmp = s1;
			s1 = ft_strjoin(s1, buffer);
			free(tmp);
			if (!s1)
				return (free(buffer), NULL);
		}
	}
	free(buffer);
	return (s1);
}
/*
int	main(void)
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*line;

	fd1 = open("texto1.txt", O_RDONLY);
	fd2 = open("texto2.txt", O_RDONLY);
	fd3 = open("texto3.txt", O_RDONLY);
	line = get_next_line(fd1);
	printf("fd1: %s", line);
	free(line);
	line = get_next_line(fd2);
	printf("fd2: %s", line);
	free(line);
	line = get_next_line(fd3);
	printf("fd3: %s", line);
	free(line);
	line = get_next_line(fd1);
	printf("fd1: %s", line);
	free(line);
	line = get_next_line(fd2);
	printf("fd2: %s", line);
	free(line);
	line = get_next_line(fd3);
	printf("fd3: %s", line);
	free(line);
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
	*/
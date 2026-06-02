/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedraza < jpedraza@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:19:16 by jpedraza          #+#    #+#             */
/*   Updated: 2026/06/01 13:10:27 by jpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*store;
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	store = ft_read_and_store(fd, store);
	if (!store)
		return (NULL);
	tmp = store;
	line = ft_extract_line(store);
	if (!line)
	{
		store = NULL;
		return (free(tmp), NULL);
	}
	store = ft_extract_rest(store);
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
	int		fd;
	char	*line;

	fd = open("texto1.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
	*/
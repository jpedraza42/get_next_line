/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedraza < jpedraza@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 11:03:07 by jpedraza          #+#    #+#             */
/*   Updated: 2026/06/01 12:21:51 by jpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_str_end_line(const char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*storage;
	int		ct;
	int		ct2;

	if (!s2)
		return (NULL);
	if (!s1)
		s1 = "";
	storage = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!storage)
		return (NULL);
	ct = 0;
	while (s1[ct])
	{
		storage[ct] = s1[ct];
		ct++;
	}
	ct2 = 0;
	while (s2[ct2])
		storage[ct++] = s2[ct2++];
	storage[ct] = '\0';
	return (storage);
}

char	*ft_extract_line(char *s1)
{
	char	*new_line;
	int		i;
	int		ct;

	if (!s1 || s1[0] == '\0')
		return (NULL);
	i = ft_str_end_line(s1);
	if (i < 0)
		i = ft_strlen(s1) - 1;
	new_line = malloc(sizeof(char) * (i + 2));
	if (!new_line)
		return (NULL);
	ct = 0;
	while (ct <= i)
	{
		new_line[ct] = s1[ct];
		ct++;
	}
	new_line[ct] = '\0';
	return (new_line);
}

char	*ft_extract_rest(char *s1)
{
	int		end;
	int		st;
	char	*store;

	end = ft_str_end_line(s1);
	if (end < 0)
		return (NULL);
	if (s1[end + 1] == '\0')
		return (NULL);
	store = malloc(sizeof(char) * (ft_strlen(s1) - end));
	if (!store)
		return (NULL);
	st = 0;
	while (s1[st + end + 1])
	{
		store[st] = s1[st + end + 1];
		st++;
	}
	store[st] = '\0';
	return (store);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedraza < jpedraza@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 10:26:00 by jpedraza          #+#    #+#             */
/*   Updated: 2026/06/01 13:03:32 by jpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

char	*get_next_line(int fd);
int		ft_strlen(const char *s);
int		ft_str_end_line(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_extract_line(char *s1);
char	*ft_extract_rest(char *s1);
char	*ft_read_and_store(int fd, char *s1);

#endif
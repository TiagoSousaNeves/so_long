/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:55:24 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 02:38:37 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_get_next_line(int fd);
static int	ft_find_next_line(char *buf);
static void	ft_start_read(char **the_line, int fd);
static void	ft_continue_read(char **the_line, int fd);
static char	*ft_update_next_line(char *the_line, char *n);

char	*ft_get_next_line(int fd)
{
	char		*n;
	char		*the_line;
	static char	*nxt_line;

	n = NULL;
	the_line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (nxt_line)
	{
		the_line = ft_strdup(nxt_line);
		free(nxt_line);
	}
	if (nxt_line == NULL)
		ft_start_read(&the_line, fd);
	if (the_line == NULL)
		return (NULL);
	if (!ft_find_next_line(the_line))
		ft_continue_read(&the_line, fd);
	n = ft_strchr(the_line, '\n');
	nxt_line = ft_update_next_line(the_line, n);
	if (nxt_line == NULL && the_line[0] == '\0')
		return (NULL);
	return (the_line);
}

static char	*ft_update_next_line(char *the_line, char *n)
{
	char	*nxt_line;

	if (n && *(n + 1))
	{
		nxt_line = ft_strdup(n + 1);
		*(n + 1) = '\0';
	}
	else
	{
		nxt_line = NULL;
		if (the_line[0] == '\0')
		{
			free(the_line);
			return (NULL);
		}
	}
	return (nxt_line);
}

static void	ft_start_read(char **the_line, int fd)
{
	int		size_read;
	char	*buf;

	size_read = 0;
	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return ;
	size_read = read(fd, buf, BUFFER_SIZE);
	if (size_read <= 0)
	{
		free(buf);
		return ;
	}
	buf[size_read] = '\0';
	*the_line = ft_strdup(buf);
	if (*the_line == NULL)
		return ;
	free(buf);
	return ;
}

static void	ft_continue_read(char **the_line, int fd)
{
	int		size_read;
	char	*temp;
	char	*buf;

	while (!ft_find_next_line(*the_line))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		size_read = read(fd, buf, BUFFER_SIZE);
		if (size_read <= 0)
		{
			free(buf);
			return ;
		}
		buf[size_read] = '\0';
		temp = ft_strdup(*the_line);
		free(*the_line);
		*the_line = ft_strjoin(temp, buf);
		free(temp);
		free(buf);
	}
	return ;
}

static int	ft_find_next_line(char *buf)
{
	unsigned int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

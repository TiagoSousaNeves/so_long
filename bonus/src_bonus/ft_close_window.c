/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_window.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 02:53:23 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 04:55:16 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int		ft_close_window(t_game *game);
int		ft_update(t_game *game);
int		ft_count_file_lines(int fd);
int		ft_find_code(char c);
char	*ft_strrchr(const char *str, int c);

int	ft_close_window(t_game *game)
{
	ft_handle_error("Closing game!\n", game, 0);
	exit(0);
}

int	ft_update(t_game *game)
{
	ft_put_bh_images(game);
	ft_put_exit_images(game);
	ft_put_astro_anime(game);
	if (game->bool_start)
		ft_put_start(game);
	return (0);
}

int	ft_find_code(char c)
{
	int		i;
	char	*str;

	i = 0;
	str = "012TP";
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			ptr = (char *)&str[i];
		i++;
	}
	if ((unsigned char)c == '\0')
		ptr = (char *)&str[i];
	return (ptr);
}

int	ft_count_file_lines(int fd)
{
	int		line_count;
	char	*line;

	line_count = 0;
	line = ft_get_next_line(fd);
	while (line)
	{
		line_count++;
		free(line);
		line = ft_get_next_line(fd);
	}
	lseek(fd, 0, SEEK_SET);
	return (line_count);
}

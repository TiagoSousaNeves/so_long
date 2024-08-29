/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 03:03:14 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/12 16:05:28 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void		ft_handle_map(char *str, t_game *game);
static int	ft_define_height(int fd);
static int	ft_define_width(int fd);
static char	**ft_read_map(int fd, int height, t_game *game);
static void	ft_check_map_shape(t_game *game);

void	ft_handle_map(char *str, t_game *game)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nUnable to open file %s\n", str);
		ft_handle_error("", game, 1);
	}
	game->map.height = ft_define_height(fd);
	game->map.width = ft_define_width(fd);
	game->map.map = ft_read_map(fd, game->map.height, game);
	ft_check_map_shape(game);
	ft_check_map(game);
	ft_check_map_errors(game);
	ft_check_map_playability(game);
	ft_get_player_position(game);
	close(fd);
}

static int	ft_define_height(int fd)
{
	int		height;
	char	*line;

	height = 0;
	lseek(fd, 0, SEEK_SET);
	line = ft_get_next_line(fd);
	while (line)
	{
		free(line);
		line = ft_get_next_line(fd);
		height++;
	}
	lseek(fd, 0, SEEK_SET);
	return (height);
}

static int	ft_define_width(int fd)
{
	char	*line;
	int		width;

	width = 0;
	lseek(fd, 0, SEEK_SET);
	line = ft_get_next_line(fd);
	if (line)
	{
		while (line[width] != '\n' && line[width] != '\0')
			width++;
		free(line);
	}
	lseek(fd, 0, SEEK_SET);
	return (width);
}

static char	**ft_read_map(int fd, int height, t_game *game)
{
	char	**map;
	int		i;

	i = 0;
	map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map)
	{
		close(fd);
		ft_handle_error("Error\nMemory allocation failed\n", game, 1);
	}
	while (i < height)
	{
		map[i] = ft_get_next_line(fd);
		if (!map[i])
		{
			close(fd);
			ft_handle_error("Error\nReading line\n", game, 1);
		}
		i++;
	}
	map[height] = NULL;
	return (map);
}

static void	ft_check_map_shape(t_game *game)
{
	int	i;
	int	j;
	int	line_len;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (game->map.map[i][j] && game->map.map[i][j] != '\n')
			j++;
		line_len = j;
		if (line_len != game->map.width)
		{
			ft_handle_error("Error\nThe shape of the map must be a rectangle"
				" or a square!\n", game, 1);
		}
		i++;
	}
}

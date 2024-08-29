/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:04:53 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 05:30:49 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
		exit(1);
	}
	game->map.height = ft_define_height(fd);
	game->map.width = ft_define_width(fd);
	game->map.map = ft_read_map(fd, game->map.height, game);
	ft_check_map_shape(game);
	ft_check_map(game);
	ft_check_map_errors(game);
	ft_check_map_playability(game);
	ft_count_walls(game);
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
		height++;
		line = ft_get_next_line(fd);
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
	if (width < 6)
		ft_printf("For the optimal gaming experience, it is recommended to "
			"play a map with a minimum of 6 columns!\n");
	return (width);
}

static char	**ft_read_map(int fd, int height, t_game *game)
{
	char	**map;
	int		i;

	i = -1;
	map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map)
	{
		close(fd);
		ft_handle_error("Error\nMemory allocation failed\n", game, 1);
	}
	lseek(fd, 0, SEEK_SET);
	while (++i < height)
	{
		map[i] = ft_get_next_line(fd);
		if (!map[i])
		{
			ft_printf("Erro\nReading line %d\n", i);
			close(fd);
			ft_handle_error("", game, 1);
		}
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
			ft_handle_error("The shape of the map must be a rectangle "
				"or a square!\n", game, 1);
		}
		i++;
	}
}

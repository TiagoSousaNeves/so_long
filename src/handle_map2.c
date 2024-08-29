/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 03:27:34 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 06:18:50 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void		ft_check_map_playability(t_game *game);
static char	**ft_copy_map(t_game *game, int i, int j);
static void	ft_check_ducks_gathering(char **map, t_game *game, int ducks,
				char c);
static int	ft_flood_fill_ducks(char **map, int i, int j, char c);
static int	ft_flood_fill_exit(char **map, int i, int j, int c);

void	ft_check_map_playability(t_game *game)
{
	char	**map_temp;
	int		i;
	int		j;

	i = -1;
	j = -1;
	ft_get_player_position(game);
	map_temp = ft_copy_map(game, i, j);
	ft_check_ducks_gathering(map_temp, game, game->map.collectible,
		'F');
	while (++i < game->map.height)
		free(map_temp[i]);
	free(map_temp);
}

static char	**ft_copy_map(t_game *game, int i, int j)
{
	char	**map_temp;

	map_temp = malloc(sizeof(char *) * (game->map.height + 1));
	if (map_temp == NULL)
		return (NULL);
	while (++i < game->map.height)
	{
		map_temp[i] = malloc(game->map.width + 1);
		if (map_temp[i] == NULL)
		{
			while (--i >= 0)
				free(map_temp[i]);
			free(map_temp);
			return (NULL);
		}
		j = -1;
		while (++j < game->map.width)
			map_temp[i][j] = game->map.map[i][j];
		map_temp[i][game->map.width] = '\0';
	}
	map_temp[game->map.height] = NULL;
	return (map_temp);
}

void	ft_check_ducks_gathering(char **map, t_game *game, int ducks,
				char c)
{
	int	i;

	i = -1;
	if (ducks != ft_flood_fill_ducks(map, game->player.y, game->player.x, c))
	{
		while (++i < game->map.height)
			free(map[i]);
		free(map);
		ft_handle_error("Error\nVerifying the map, you must be able to gather "
			"all the rubber ducks!\n", game, 1);
	}
	if (!(ft_flood_fill_exit(map, game->player.y, game->player.x, 'f')))
	{
		while (++i < game->map.height)
			free(map[i]);
		free(map);
		ft_handle_error("Error\nverifying the map, you must be able to reach"
			" the exit!\n", game, 1);
	}
}

int	ft_flood_fill_exit(char **map, int i, int j, int c)
{
	int	exit;

	exit = 0;
	if (map[i][j] == '1' || map[i][j] == c || map[i][j] == '2')
		return (exit);
	if (map[i][j] == 'E')
	{
		exit++;
		return (exit);
	}
	map[i][j] = c;
	exit += ft_flood_fill_exit(map, i + 1, j, c);
	exit += ft_flood_fill_exit(map, i - 1, j, c);
	exit += ft_flood_fill_exit(map, i, j + 1, c);
	exit += ft_flood_fill_exit(map, i, j - 1, c);
	return (exit);
}

int	ft_flood_fill_ducks(char **map, int i, int j, char c)
{
	int	ducks;

	ducks = 0;
	if (map[i][j] == '1' || map[i][j] == c || map[i][j] == 'E' ||
		map[i][j] == '2')
		return (ducks);
	if (map[i][j] != '1')
	{
		if (map[i][j] == 'C')
			ducks++;
		map[i][j] = c;
	}
	ducks += ft_flood_fill_ducks(map, i + 1, j, c);
	ducks += ft_flood_fill_ducks(map, i - 1, j, c);
	ducks += ft_flood_fill_ducks(map, i, j + 1, c);
	ducks += ft_flood_fill_ducks(map, i, j - 1, c);
	return (ducks);
}

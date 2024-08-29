/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 03:13:51 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/08 18:52:55 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void		ft_check_map(t_game *game);
static void	ft_update_map_counters(t_game *game, char map_char, int i, int j);
void		ft_check_map_errors(t_game *game);
void		ft_destroy_map(t_game *game);
void		ft_get_player_position(t_game *game);

void	ft_check_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = -1;
		while (++j < game->map.width)
		{
			ft_update_map_counters(game, game->map.map[i][j], i, j);
		}
		i++;
	}
}

static void	ft_update_map_counters(t_game *game, char map_char, int i, int j)
{
	if (map_char == 'E')
		game->map.exit++;
	if (map_char == 'C')
		game->map.collectible++;
	if (map_char == 'P')
		game->map.player++;
	if (game->map.map[i][j] != '1' && game->map.map[i][j] != 'P' &&
		game->map.map[i][j] != '0' && game->map.map[i][j] != 'E' &&
		game->map.map[i][j] != 'C')
	{
		ft_handle_error("Error\nMap not valid! The map must only contain wall "
			"(1), floor (0), player (P), collectables (C) and exit (E)\n",
			game, 1);
		exit(1);
	}
	if ((i == 0 || j == 0 || i == game->map.height - 1
			|| j == game->map.width - 1) && game->map.map[i][j] != '1')
	{
		ft_handle_error("Error\nMap not valid! The map must be surrounded by "
			"walls (1)\n", game, 1);
		exit(1);
	}
}

void	ft_check_map_errors(t_game *game)
{
	if (game->map.exit != 1)
	{
		ft_handle_error("Error\nThe map must contain a valid exit, just one "
			"(E)!\n", game, 1);
	}
	if (game->map.collectible < 1)
	{
		ft_handle_error("Error\nThe map must contain at least one collectible "
			"item (C)!\n", game, 1);
	}
	if (game->map.player != 1)
	{
		ft_handle_error("Error\nThe map must contain a player, just one (P)!"
			"\n", game, 1);
	}
}

void	ft_destroy_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.map)
	{
		while (i < game->map.height)
		{
			free(game->map.map[i]);
			i++;
		}
		free(game->map.map);
		game->map.map = NULL;
	}
}

void	ft_get_player_position(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.map[i][j] == 'P')
			{
				game->player.x = j;
				game->player.y = i;
			}
			j++;
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_mapfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:12:48 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 07:59:42 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ft_check_mapfile(char *str);
void		ft_check_map(t_game *game);
static void	ft_update_map_counters(t_game *game, char map_char);
void		ft_check_map_errors(t_game *game);
void		ft_count_walls(t_game *game);

void	ft_check_mapfile(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if ((str[i - 1] != 'r' || str[i - 2] != 'e' || str[i - 3] != 'b'
			|| str[i - 4] != '.') || i < 6)
	{
		ft_printf("Error\nOpening map file! The file map must be a valid "
			"'.ber' file");
		exit(1);
	}
}

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
			ft_update_map_counters(game, game->map.map[i][j]);
			if ((i == 0 || j == 0 || i == game->map.height - 1
					|| j == game->map.width - 1)
				&& (game->map.map[i][j] != '1' && game->map.map[i][j] != '2'))
			{
				ft_handle_error("Error\nInvalid map! The map must be "
					"surrounded by walls (1)\n", game, 1);
			}
		}
		i++;
	}
}

static void	ft_update_map_counters(t_game *game, char map_char)
{
	if (map_char == 'E')
		game->map.exit++;
	if (map_char == 'C')
		game->map.collectible++;
	if (map_char == 'P')
		game->map.player++;
	if (map_char == 'B')
		game->map.bh++;
}

void	ft_check_map_errors(t_game *game)
{
	if (game->map.exit != 1)
	{
		ft_handle_error("Error\nInvalid map! The map must contain a valid "
			"exit, just one (E)!\n", game, 1);
	}
	if (game->map.collectible < 1)
	{
		ft_handle_error("Error\nInvalid map! The map must contain at least "
			"one collectible item (C)!\n", game, 1);
	}
	if (game->map.player != 1)
	{
		ft_handle_error("Error\nInvalid map! The map must contain a player,"
			" just one (P)!\n", game, 1);
	}
	if (game->map.bh != 1)
	{
		ft_handle_error("Error\nInvalid map! The map must contain 1 black "
			"hole (B)\n", game, 1);
	}
}

void	ft_count_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.map[i][j] == '1')
				game->wall.count_a++;
			if (game->map.map[i][j] == '2')
				game->wall.count_b++;
			j++;
		}
		i++;
	}
}

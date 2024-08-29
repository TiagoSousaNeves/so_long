/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_ducks_gathering.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 01:14:28 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 04:39:34 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ft_check_ducks_gathering(char **map, t_game *game, int ducks,
				char c);
static int	ft_flood_fill_exit(char **map, int i, int j, int c);
static int	ft_flood_fill_ducks(char **map, int i, int j, char c);

void	ft_check_ducks_gathering(char **map, t_game *game, int ducks, char c)
{
	if (ducks != ft_flood_fill_ducks(map, game->player.y, game->player.x, c))
	{
		ft_printf("Error\nVerifying the map, you must be able to gather all "
			"the rubber ducks!\n");
		ft_destroy_map(game);
		exit(1);
	}
	if (!(ft_flood_fill_exit(map, game->player.y, game->player.x, 'f')))
	{
		ft_printf("Error\nVerifying the map, you must be able to reach the"
			"exit!\n");
		ft_destroy_map(game);
		exit(1);
	}
}

static int	ft_flood_fill_exit(char **map, int i, int j, int c)
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

static int	ft_flood_fill_ducks(char **map, int i, int j, char c)
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

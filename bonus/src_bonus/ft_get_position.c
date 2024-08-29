/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 01:02:42 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 05:22:47 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ft_get_position(t_game *game, char c);
static void	ft_get_position_player(t_game *game, int i, int j);
static void	ft_get_position_bh(t_game *game, int i, int j);
static void	ft_get_position_exit(t_game *game, int i, int j);

void	ft_get_position(t_game *game, char c)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.map[i][j] == c)
			{
				if (c == 'P')
					ft_get_position_player(game, i, j);
				else if (c == 'B')
					ft_get_position_bh(game, i, j);
				else if (c == 'E')
					ft_get_position_exit(game, i, j);
			}
			j++;
		}
		i++;
	}
}

static void	ft_get_position_player(t_game *game, int i, int j)
{
	game->player.x = j;
	game->player.y = i;
	if (game->player.x == -1 || game->player.y == -1)
	{
		ft_handle_error("Error\nPlayer position not found in the map\n",
			game, 1);
	}
}

static void	ft_get_position_bh(t_game *game, int i, int j)
{
	game->bh.x = j;
	game->bh.y = i;
	if (game->bh.x == -1 || game->bh.y == -1)
	{
		ft_handle_error("Error\nBH position not found in the map\n",
			game, 1);
	}
}

static void	ft_get_position_exit(t_game *game, int i, int j)
{
	game->exit.x = j;
	game->exit.y = i;
	if (game->exit.x == -1 || game->exit.y == -1)
	{
		ft_handle_error("Error\nExit position not found in the map\n",
			game, 1);
	}
}

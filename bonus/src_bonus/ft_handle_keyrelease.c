/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_keyrelease.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 04:24:36 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 07:21:08 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int		ft_handle_keyrelease(int keycode, t_game *game);
void	ft_undress_astronaut(t_game *game);
void	ft_handle_agu(t_game *game, int new_x, int new_y);
void	ft_del_prev_msg(t_game *game, int start, int end);

void	ft_undress_astronaut(t_game *game)
{
	ft_del_prev_msg(game, (game->map.height * IP + 40),
		(game->map.height * IP + 60));
	mlx_string_put(game->mlx_c, game->mlx_w, 0, (game->map.height * IP + 56),
		CORAL,
		"AGU suit undressed! Does the black hole live? Be careful!");
	game->player.agu = 0;
	game->player.stop = 0;
	game->agu.y = game->player.y;
	game->agu.x = game->player.x;
	ft_undress_astro(game);
	mlx_do_sync(game->mlx_c);
	game->map.map[game->player.y][game->player.x] = 'A';
	mlx_put_image_to_window(game->mlx_c, game->mlx_w,
		game->player.player_img[0], game->player.x * IP,
		game->player.y * IP);
	if (game->map.map[game->player.y][game->player.x] ==
		game->map.map[game->bh.y][game->bh.x] && !game->bh.stop)
	{
		ft_swallow_player(game);
	}
}

int	ft_handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == 100 || keycode == 65363 || keycode == 97
		|| keycode == 65361 || keycode == 119 || keycode == 65362
		|| keycode == 115 || keycode == 65364)
	{
		if (!game->player.agu)
		{
			mlx_put_image_to_window(game->mlx_c, game->mlx_w,
				game->player.player_img[0], game->player.x * IP,
				game->player.y * IP);
		}
		else
		{
			mlx_put_image_to_window(game->mlx_c, game->mlx_w,
				game->player.astronaut[0], game->player.x * IP,
				game->player.y * IP);
		}
	}
	return (0);
}

void	ft_handle_agu(t_game *game, int new_x, int new_y)
{
	if (game->map.map[new_y][new_x] == 'T')
	{
		if (game->agu.agu == 0)
			game->map.map[game->bh.y][game->bh.x] = game->bh.c;
		game->bh.spin = 4;
		game->agu.agu = 0;
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->wall.floor_wall_img[game->bh.code],
			game->bh.x * IP, game->bh.y * IP);
		game->bh.x = new_x;
		game->bh.y = new_y;
		game->bh.c = game->map.map[new_y][new_x];
		game->map.map[new_y][new_x] = 'B';
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->bh.spin_agu[5], game->bh.x * IP, game->bh.y * IP);
	}
}

void	ft_del_prev_msg(t_game *game, int start, int end)
{
	int		i;
	int		j;

	i = start;
	while (i < end)
	{
		j = 0;
		while (j < game->map.width * IP)
		{
			mlx_pixel_put(game->mlx_c, game->mlx_w, j, i, BLACK);
			j++;
		}
		i++;
	}
}

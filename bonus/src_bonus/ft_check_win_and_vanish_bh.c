/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 01:42:39 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/04 22:26:01 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ft_update_bh_on_floor(t_game *game, int new_x, int new_y);
void		ft_check_win_and_vanish_bh(t_game *game, int new_x, int new_y);
static void	ft_handle_bh_position_to_vanish(t_game *game, int new_x, int new_y);
void		ft_handle_swallow_duck(t_game *game, int new_x, int new_y);
void		ft_handle_swallow_player(t_game *game, int new_x, int new_y);

void	ft_update_bh_on_floor(t_game *game, int new_x, int new_y)
{
	char	*msg;

	msg = ft_print_bh_move(game, new_x, new_y);
	ft_del_prev_msg(game, (game->map.height * IP + 20),
		(game->map.height * IP + 40));
	mlx_string_put(game->mlx_c, game->mlx_w, 0,
		(game->map.height * IP + 36), BLUE, msg);
	free(msg);
	if (game->map.map[new_y][new_x] == '0')
	{
		game->bh.spin = 0;
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->wall.floor_wall_img[game->bh.code],
			game->bh.x * IP, game->bh.y * IP);
		game->map.map[game->bh.y][game->bh.x] = game->bh.c;
		game->bh.x = new_x;
		game->bh.y = new_y;
		game->bh.c = game->map.map[new_y][new_x];
		game->map.map[new_y][new_x] = 'B';
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->bh.bh_img[1], (new_x * IP), (new_y * IP));
	}
}

void	ft_check_win_and_vanish_bh(t_game *game, int new_x, int new_y)
{
	mlx_put_image_to_window(game->mlx_c, game->mlx_w,
		game->exit.opened[0], (game->exit.x * IP), (game->exit.y * IP));
	mlx_do_sync(game->mlx_c);
	game->bh.stop = 1;
	game->player.stop = 0;
	game->map.map[game->bh.y][game->bh.x] = game->bh.c;
	ft_handle_bh_position_to_vanish(game, new_x, new_y);
	ft_vanish_bh(game);
	if (game->player.agu)
	{
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->player.astro_anime[1], game->player.x * IP,
			game->player.y * IP);
	}
	mlx_do_sync(game->mlx_c);
	mlx_put_image_to_window(game->mlx_c, game->mlx_w,
		game->wall.floor_wall_img[0], game->bh.x * IP, game->bh.y * IP);
	mlx_do_sync(game->mlx_c);
}

static void	ft_handle_bh_position_to_vanish(t_game *game, int new_x, int new_y)
{
	if (game->map.map[new_y][new_x] == '0')
	{
		if (game->bh.code == 4)
		{
			mlx_put_image_to_window(game->mlx_c, game->mlx_w,
				game->player.astro_anime[game->bh.code],
				game->bh.x * IP, game->bh.y * IP);
		}
		else
		{
			mlx_put_image_to_window(game->mlx_c, game->mlx_w,
				game->wall.floor_wall_img[game->bh.code],
				game->bh.x * IP, game->bh.y * IP);
		}
		mlx_do_sync(game->mlx_c);
		game->bh.x = new_x;
		game->bh.y = new_y;
	}
}

void	ft_handle_swallow_duck(t_game *game, int new_x, int new_y)
{
	if (game->map.map[new_y][new_x] == 'C')
	{
		ft_del_prev_msg(game, (game->map.height * IP + 40),
			(game->map.height * IP + 60));
		mlx_string_put(game->mlx_c, game->mlx_w, 0,
			(game->map.height * IP + 56), RED,
			"The black hole swallowed a duck!");
		ft_swallow_duck(game, new_x, new_y, game->bh.code);
		usleep(100000);
		mlx_do_sync(game->mlx_c);
	}
}

void	ft_handle_swallow_player(t_game *game, int new_x, int new_y)
{
	if (game->map.map[new_y][new_x] == 'P' ||
		(new_x == game->player.x && new_y == game->player.y))
	{
		if (!game->player.stop)
		{
			ft_swallow_player(game);
			usleep(100000);
			mlx_do_sync(game->mlx_c);
		}
		if (game->player.stop)
		{
			game->bh.spin = 3;
			mlx_put_image_to_window(game->mlx_c, game->mlx_w,
				game->wall.floor_wall_img[game->bh.code],
				game->bh.x * IP, game->bh.y * IP);
			game->map.map[game->bh.y][game->bh.x] = game->bh.c;
			game->bh.x = new_x;
			game->bh.y = new_y;
			game->bh.c = game->map.map[new_y][new_x];
			mlx_put_image_to_window(game->mlx_c, game->mlx_w,
				game->player.astronaut[0], game->bh.x * IP, game->bh.y * IP);
		}
	}
}

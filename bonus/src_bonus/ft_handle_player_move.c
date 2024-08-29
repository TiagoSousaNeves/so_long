/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_player_move.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 07:53:34 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 07:18:21 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ft_handle_player_move(t_game *game, int new_x, int new_y);
static void	ft_update_map_on_move(t_game *game, int new_x, int new_y);
static void	ft_update_player_image(t_game *game, int new_x, int new_y);
void		ft_handle_astro_transf(t_game *game, int new_x, int new_y);
void		ft_handle_exit(t_game *game);

void	ft_handle_player_move(t_game *game, int new_x, int new_y)
{
	char	*msg;

	ft_update_map_on_move(game, new_x, new_y);
	msg = ft_print_player_move(game, new_x, new_y);
	ft_del_prev_msg(game, (game->map.height * IP),
		(game->map.height * IP + 25));
	mlx_string_put(game->mlx_c, game->mlx_w, 0, (game->map.height * IP + 16),
		WHITE, msg);
	free(msg);
	game->player.x = new_x;
	game->player.y = new_y;
	game->map.map[new_y][new_x] = 'P';
	ft_update_player_image(game, new_x, new_y);
}

static void	ft_update_player_image(t_game *game, int new_x, int new_y)
{
	if (!game->player.agu)
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->player.player_img[0], new_x * IP, new_y * IP);
	else
	{
		if (new_y > game->player.y)
			mlx_put_image_to_window(game->mlx_c, game->mlx_w,
				game->player.astronaut[0], new_x * IP, new_y * IP);
		ft_del_prev_msg(game, (game->map.height * IP + 40),
			(game->map.height * IP + 64));
		mlx_string_put(game->mlx_c, game->mlx_w, 0,
			(game->map.height * IP + 56), CORAL,
			"Without a black hole active the AGU suit is heavy and useless!");
		usleep(1000000);
		mlx_do_sync(game->mlx_c);
	}
}

static void	ft_update_map_on_move(t_game *game, int new_x, int new_y)
{
	if (game->map.map[game->player.y][game->player.x] == 'A')
	{
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->agu.agu_img[1], game->agu.x * IP, game->agu.y * IP);
		game->map.map[game->player.y][game->player.x] = 'A';
	}
	else
	{
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->wall.floor_wall_img[0], game->player.x * IP,
			game->player.y * IP);
		game->map.map[game->player.y][game->player.x] = '0';
	}
	if (game->map.map[new_y][new_x] == 'C')
	{
		game->player.ducks++;
		ft_pickup_duck(game, new_x, new_y);
		mlx_do_sync(game->mlx_c);
		if (game->player.ducks == game->map.collectible)
			game->agu.agu = 1;
	}
}

void	ft_handle_exit(t_game *game)
{
	mlx_put_image_to_window(game->mlx_c, game->mlx_w,
		game->wall.floor_wall_img[0], game->player.x * IP,
		game->player.y * IP);
	mlx_put_image_to_window(game->mlx_c, game->mlx_w,
		game->exit.opened[0], (game->exit.x * IP), (game->exit.y * IP));
	ft_del_prev_msg(game, (game->map.height * IP + 40),
		(game->map.height * IP + 60));
	mlx_string_put(game->mlx_c, game->mlx_w, 0,
		(game->map.height * IP + 56), GREEN,
		"The exit is now open!");
	ft_leave_and_win(game);
}

void	ft_handle_astro_transf(t_game *game, int new_x, int new_y)
{
	if (game->map.map[new_y][new_x] == 'A')
	{
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->wall.floor_wall_img[0], game->player.x * IP,
			game->player.y * IP);
		ft_astro_transf(game);
		ft_del_prev_msg(game, (game->map.height * IP + 40),
			(game->map.height * IP + 60));
		mlx_string_put(game->mlx_c, game->mlx_w, 0,
			(game->map.height * IP + 56), GREEN, "The player is safe with"
			" the AGU suit! To undress, press SPACE.");
		usleep(100000);
		mlx_do_sync(game->mlx_c);
		if (!game->bh.stop)
			game->player.stop = 1;
		game->player.agu = 1;
		game->map.map[game->agu.y][game->agu.x] = 'P';
		game->map.map[game->player.y][game->player.x] = '0';
		game->player.x = new_x;
		game->player.y = new_y;
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->player.astronaut[0], game->agu.x * IP, game->agu.y * IP);
		mlx_do_sync(game->mlx_c);
	}
}

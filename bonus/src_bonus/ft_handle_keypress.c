/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_keypress.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:57:12 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 05:25:29 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int			ft_handle_keypress(int keycode, t_game *game);
static void	ft_move_player_left(t_game *game);
static void	ft_move_player_right(t_game *game);
static void	ft_move_player_up(t_game *game);
static void	ft_move_player_down(t_game *game);

int	ft_handle_keypress(int keycode, t_game *game)
{
	if (keycode == 65307)
		ft_close_window(game);
	else if (keycode == 119 || keycode == 65362)
		ft_move_player_up(game);
	else if (keycode == 115 || keycode == 65364)
		ft_move_player_down(game);
	else if (keycode == 97 || keycode == 65361)
		ft_move_player_left(game);
	else if (keycode == 100 || keycode == 65363)
		ft_move_player_right(game);
	else if (keycode == 32 && game->player.agu)
		ft_undress_astronaut(game);
	return (0);
}

static void	ft_move_player_left(t_game *game)
{
	int	new_x;

	new_x = game->player.x - 1;
	game->player.moves++;
	ft_print_count_moves(game);
	if (!game->player.agu)
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->player.player_img[3], game->player.x * IP,
			game->player.y * IP);
	else
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->player.astronaut[3], game->player.x * IP,
			game->player.y * IP);
	ft_move_player(game, new_x, game->player.y);
	ft_move_bh(game, game->bh.x + 1, game->bh.y);
}

static void	ft_move_player_right(t_game *game)
{
	int	new_x;

	new_x = game->player.x + 1;
	game->player.moves++;
	ft_print_count_moves(game);
	if (!game->player.agu)
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->player.player_img[4], game->player.x * IP,
			game->player.y * IP);
	else
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->player.astronaut[2], game->player.x * IP,
			game->player.y * IP);
	ft_move_player(game, new_x, game->player.y);
	ft_move_bh(game, game->bh.x - 1, game->bh.y);
}

static void	ft_move_player_up(t_game *game)
{
	int	new_y;

	new_y = game->player.y - 1;
	game->player.moves++;
	ft_print_count_moves(game);
	if (!game->player.agu)
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->player.player_img[1], game->player.x * IP,
			game->player.y * IP);
	else
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->player.astronaut[1], game->player.x * IP,
			game->player.y * IP);
	ft_move_player(game, game->player.x, new_y);
	ft_move_bh(game, game->bh.x, game->bh.y + 1);
}

static void	ft_move_player_down(t_game *game)
{
	int	new_y;

	new_y = game->player.y + 1;
	game->player.moves++;
	ft_print_count_moves(game);
	if (!game->player.agu)
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->player.player_img[2], game->player.x * IP,
			game->player.y * IP);
	else
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->player.astronaut[0], game->player.x * IP,
			game->player.y * IP);
	ft_move_player(game, game->player.x, new_y);
	ft_move_bh(game, game->bh.x, game->bh.y - 1);
}

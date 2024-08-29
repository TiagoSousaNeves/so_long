/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_bh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 07:57:30 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 07:59:42 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ft_move_bh(t_game *game, int new_x, int new_y);
static void	ft_adjust_coordinates(t_game *game, int *new_x, int *new_y);
static void	ft_start_bh_c(t_game *game);
static void	ft_update_map_and_agu(t_game *game, int new_x, int new_y);
static void	ft_handle_put_agu(t_game *game, int new_x, int new_y);

void	ft_move_bh(t_game *game, int new_x, int new_y)
{
	if (!game->bh.stop)
	{
		ft_adjust_coordinates(game, &new_x, &new_y);
		ft_start_bh_c(game);
		game->bh.code = ft_find_code(game->bh.c);
		ft_handle_swallow_player(game, new_x, new_y);
		ft_handle_swallow_duck(game, new_x, new_y);
		if (game->player.ducks == game->map.collectible
			&& (!game->wall.count_a || !game->wall.count_b)
			&& (game->bh.spin == 0
				|| game->map.map[new_y][new_x] == '0'))
		{
			ft_check_win_and_vanish_bh(game, new_x, new_y);
		}
		ft_handle_put_agu(game, new_x, new_y);
		ft_handle_agu(game, new_x, new_y);
		ft_handle_bh_conditions(game, new_x, new_y);
		ft_print_nb_wall_a(game);
		ft_print_nb_wall_b(game);
	}
}

static void	ft_adjust_coordinates(t_game *game, int *new_x, int *new_y)
{
	if (*new_x < 0 || *new_x >= game->map.width
		|| *new_y < 0 || *new_y >= game->map.height)
	{
		if (*new_x < 0)
			*new_x = game->map.width - 1;
		if (*new_x >= game->map.width)
			*new_x = 0;
		if (*new_y < 0)
			*new_y = game->map.height - 1;
		if (*new_y >= game->map.height)
			*new_y = 0;
	}
}

static void	ft_handle_put_agu(t_game *game, int new_x, int new_y)
{
	char	*msg;

	msg = NULL;
	if (game->player.ducks == game->map.collectible
		&& game->map.map[new_y][new_x] == '0'
		&& game->agu.agu == 1 && !game->bh.stop)
	{
		msg = ft_print_bh_move(game, new_x, new_y);
		ft_del_prev_msg(game, (game->map.height * IP + 20),
			(game->map.height * IP + 40));
		mlx_string_put(game->mlx_c, game->mlx_w, 0,
			(game->map.height * IP + 36), BLUE, msg);
		free(msg);
		ft_del_prev_msg(game, (game->map.height * IP + 40),
			(game->map.height * IP + 60));
		mlx_string_put(game->mlx_c, game->mlx_w, 0, (game->map.height * IP + 56
				), GREEN, "The black hole cast an AGU chest! Get it!");
		ft_update_map_and_agu(game, new_x, new_y);
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->wall.floor_wall_img[game->bh.code],
			game->bh.x * IP, game->bh.y * IP);
		ft_put_agu(game);
		usleep(100000);
		mlx_do_sync(game->mlx_c);
	}
}

static void	ft_update_map_and_agu(t_game *game, int new_x, int new_y)
{
	game->map.map[game->bh.y][game->bh.x] = game->bh.c;
	game->map.map[new_y][new_x] = 'T';
	game->agu.x = new_x;
	game->agu.y = new_y;
}

static void	ft_start_bh_c(t_game *game)
{
	if (game->player.moves == 1)
		game->bh.c = '0';
}

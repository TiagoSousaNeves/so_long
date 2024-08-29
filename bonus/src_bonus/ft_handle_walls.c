/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 01:35:04 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 08:37:39 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ft_handle_walls(t_game *game, int new_x, int new_y);
static void	ft_handle_wall_type_1(t_game *game, int new_x, int new_y);
static void	ft_handle_wall_type_2(t_game *game, int new_x, int new_y);
void		ft_handle_bh_conditions(t_game *game, int new_x, int new_y);
static void	ft_update_exit_message(t_game *game);

void	ft_handle_walls(t_game *game, int new_x, int new_y)
{
	char	*msg;

	msg = ft_print_bh_move(game, new_x, new_y);
	ft_del_prev_msg(game, (game->map.height * IP + 20),
		(game->map.height * IP + 40));
	mlx_string_put(game->mlx_c, game->mlx_w, 0, (game->map.height * IP + 36),
		BLUE, msg);
	free(msg);
	if (game->map.map[new_y][new_x] == '1')
	{
		ft_handle_wall_type_1(game, new_x, new_y);
	}
	else if (game->map.map[new_y][new_x] == '2')
	{
		ft_handle_wall_type_2(game, new_x, new_y);
	}
}

static void	ft_handle_wall_type_1(t_game *game, int new_x, int new_y)
{
	if (game->map.map[new_y][new_x] == '1')
	{
		game->bh.spin = 1;
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->wall.floor_wall_img[game->bh.code],
			(game->bh.x * IP), (game->bh.y * IP));
		game->map.map[game->bh.y][game->bh.x] = game->bh.c;
		game->bh.x = new_x;
		game->bh.y = new_y;
		game->bh.c = game->map.map[new_y][new_x];
		game->map.map[new_y][new_x] = 'B';
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->bh.spin_wall[25], (new_x * IP), (new_y * IP));
		game->wall.count_a--;
		ft_print_nb_wall_a(game);
		game->wall.count_b++;
		ft_print_nb_wall_b(game);
	}
}

static void	ft_handle_wall_type_2(t_game *game, int new_x, int new_y)
{
	if (game->map.map[new_y][new_x] == '2')
	{
		game->bh.spin = 2;
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->wall.floor_wall_img[game->bh.code],
			(game->bh.x * IP), (game->bh.y * IP));
		game->map.map[game->bh.y][game->bh.x] = game->bh.c;
		game->bh.x = new_x;
		game->bh.y = new_y;
		game->bh.c = game->map.map[new_y][new_x];
		game->map.map[new_y][new_x] = 'B';
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->bh.spin_wall[0], (new_x * IP), (new_y * IP));
		game->wall.count_a++;
		ft_print_nb_wall_a(game);
		game->wall.count_b--;
		ft_print_nb_wall_b(game);
	}
}

void	ft_handle_bh_conditions(t_game *game, int new_x, int new_y)
{
	if ((game->map.map[new_y][new_x] == '1'
		|| game->map.map[new_y][new_x] == '2') && !game->bh.stop)
		ft_handle_walls(game, new_x, new_y);
	else if (game->map.map[new_y][new_x] == '0' && !game->bh.stop)
		ft_update_bh_on_floor(game, new_x, new_y);
	if (game->map.map[new_y][new_x] == 'E'
		|| game->map.map[new_y][new_x] == 'A')
		ft_update_bh_spin(game);
	else if (game->bh.c == '1')
		game->bh.c = '2';
	else if (game->bh.c == '2')
		game->bh.c = '1';
	ft_update_exit_message(game);
}

static void	ft_update_exit_message(t_game *game)
{
	static int	open;

	if (game->player.ducks == game->map.collectible
		&& (!game->wall.count_a || !game->wall.count_b) && open == 0)
	{
		open = 1;
		ft_del_prev_msg(game, (game->map.height * IP + 40),
			(game->map.height * IP + 60));
		mlx_string_put(game->mlx_c, game->mlx_w, 0,
			(game->map.height * IP + 56), GREEN, "The exit is now open!");
	}
	else if (game->player.ducks != game->map.collectible
		|| (game->wall.count_a && game->wall.count_b && open == 1))
	{
		open = 0;
		ft_del_prev_msg(game, (game->map.height * IP + 40),
			(game->map.height * IP + 60));
		mlx_string_put(game->mlx_c, game->mlx_w, 0,
			(game->map.height * IP + 56), PURPLE, "The exit is closed!");
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 06:15:50 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 07:59:42 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ft_move_player(t_game *game, int new_x, int new_y);
static int	ft_is_out_of_bounds(t_game *game, int new_x, int new_y);
static void	ft_handle_game_interactions(t_game *game, int new_x, int new_y);
static void	ft_handle_bh(t_game *game, int new_x, int new_y);
static void	ft_handle_open_agu(t_game *game, int new_x, int new_y);

void	ft_move_player(t_game *game, int new_x, int new_y)
{
	if (!game->player.stop)
	{
		game->bh.agu = 0;
		if (ft_is_out_of_bounds(game, new_x, new_y))
			return ;
		ft_handle_game_interactions(game, new_x, new_y);
		if (game->map.map[new_y][new_x] == 'E'
			&& game->player.ducks == game->map.collectible
			&& (!game->wall.count_a || !game->wall.count_b))
		{
			ft_handle_exit(game);
		}
		else if (game->map.map[new_y][new_x] == 'E'
			|| game->map.map[new_y][new_x] == '1'
			|| game->map.map[new_y][new_x] == '2')
		{
			ft_del_prev_msg(game, (game->map.height * IP),
				(game->map.height * IP + 24));
			mlx_string_put(game->mlx_c, game->mlx_w, 0,
				(game->map.height * IP + 16), WHITE,
				"The player cannot move to a wall or exit if"
				" the door is closed!");
		}
	}
}

static void	ft_handle_game_interactions(t_game *game, int new_x, int new_y)
{
	char	map_position;

	map_position = game->map.map[new_y][new_x];
	if ((map_position == 'B'
			|| (new_x == game->bh.x && new_y == game->bh.y))
		&& !game->player.stop && !game->bh.stop)
	{
		ft_handle_bh(game, new_x, new_y);
	}
	else if (map_position == 'T')
	{
		ft_handle_open_agu(game, new_x, new_y);
	}
	else if (map_position == 'A')
	{
		ft_handle_astro_transf(game, new_x, new_y);
	}
	else if (map_position != '1' && map_position != '2'
		&& map_position != 'E')
	{
		ft_handle_player_move(game, new_x, new_y);
	}
}

static int	ft_is_out_of_bounds(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->map.width
		|| new_y < 0 || new_y >= game->map.height)
	{
		ft_handle_error("Error\nAtempt to move out of bounds.\n", game, 1);
		return (1);
	}
	return (0);
}

static void	ft_handle_bh(t_game *game, int new_x, int new_y)
{
	if ((game->map.map[new_y][new_x] == 'B'
		|| (new_x == game->bh.x && new_y == game->bh.y))
		&& !game->player.stop && !game->bh.stop)
	{
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->wall.floor_wall_img[0],
			(game->player.x * IP), (game->player.y * IP));
		ft_swallow_player(game);
		usleep(100000);
		mlx_do_sync(game->mlx_c);
	}
}

static void	ft_handle_open_agu(t_game *game, int new_x, int new_y)
{
	char	*msg;

	if (game->map.map[new_y][new_x] == 'T')
	{
		msg = ft_print_player_move(game, new_x, new_y);
		ft_del_prev_msg(game, (game->map.height * IP),
			(game->map.height * IP + 20));
		mlx_string_put(game->mlx_c, game->mlx_w, 0,
			(game->map.height * IP + 16), WHITE, msg);
		free(msg);
		ft_open_agu(game);
		usleep(100000);
		mlx_do_sync(game->mlx_c);
		game->map.map[game->agu.y][game->agu.x] = 'A';
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->agu.agu_img[1],
			(game->agu.x * IP), (game->agu.y * IP));
		mlx_do_sync(game->mlx_c);
	}
}

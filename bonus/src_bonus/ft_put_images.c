/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:17:17 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 07:20:36 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ft_put_images(t_game *game);
static void	*ft_get_image_for_map_cell(t_game *game, char cell);
void		ft_swallow_player(t_game *game);
void		ft_display_lose_animation(t_game *game);
static void	ft_display_swallow_player_animation(t_game *game, int x, int y);

void	ft_put_images(t_game *game)
{
	int		i;
	int		j;
	void	*img;

	i = 0;
	img = NULL;
	while (i < game->map.height)
	{
		j = -1;
		while (++j < game->map.width)
		{
			img = ft_get_image_for_map_cell(game, game->map.map[i][j]);
			if (img)
				mlx_put_image_to_window(game->mlx_c, game->mlx_w,
					img, j * IP, i * IP);
		}
		i++;
	}
}

static void	*ft_get_image_for_map_cell(t_game *game, char cell)
{
	if (cell == '0')
		return (game->wall.floor_wall_img[0]);
	else if (cell == '1')
		return (game->wall.floor_wall_img[1]);
	else if (cell == '2')
		return (game->wall.floor_wall_img[2]);
	else if (cell == 'P')
		return (game->player.player_img[0]);
	else if (cell == 'C')
		return (game->duck.duck_img);
	else if (cell == 'E')
		return (game->exit.closed[0]);
	else if (cell == 'B')
		return (game->bh.bh_img[0]);
	return (NULL);
}

void	ft_swallow_player(t_game *game)
{
	game->bh.code = ft_find_code(game->bh.c);
	ft_del_prev_msg(game, (game->map.height * IP + 40),
		(game->map.height * IP + 60));
	mlx_string_put(game->mlx_c, game->mlx_w, 0, (game->map.height * IP + 56),
		RED, "The black hole swallowed the player!");
	mlx_put_image_to_window(game->mlx_c, game->mlx_w,
		game->wall.floor_wall_img[game->bh.code], (game->bh.x * IP),
		(game->bh.y * IP));
	ft_display_swallow_player_animation(game, game->player.x, game->player.y);
	sleep(1);
	mlx_destroy_window(game->mlx_c, game->mlx_w);
	game->mlx_w = mlx_new_window(game->mlx_c, END_IP_WIDTH,
			END_IP_HEIGHT, "YOU LOSE");
	ft_check_window_creation(game->mlx_w, game->mlx_c);
	ft_display_lose_animation(game);
	ft_close_window(game);
}

static void	ft_display_swallow_player_animation(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < 28)
	{
		ft_display_animation_frame(game, game->bh.swallow_player[i], x, y);
		i++;
	}
}

void	ft_display_lose_animation(t_game *game)
{
	int	i;
	int	n;

	n = 3;
	while (n >= 0)
	{
		i = 0;
		while (i < 9)
		{
			mlx_put_image_to_window(game->mlx_c, game->mlx_w,
				game->end.lose[i], 0, 0);
			usleep(100000);
			mlx_do_sync(game->mlx_c);
			i++;
		}
		n--;
	}
}

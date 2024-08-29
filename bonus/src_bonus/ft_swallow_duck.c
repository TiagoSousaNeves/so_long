/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swallow_duck.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:32:33 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 07:14:24 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ft_swallow_duck(t_game *game, int x, int y, int code);
static void	ft_display_swallow_duck_animation(t_game *game, int x, int y);
void		ft_display_animation_frame(t_game *game, void *image, int x, int y);
void		ft_pickup_duck(t_game *game, int x, int y);

void	ft_swallow_duck(t_game *game, int x, int y, int code)
{
	mlx_put_image_to_window(game->mlx_c, game->mlx_w,
		game->wall.floor_wall_img[code], (game->bh.x * IP), (game->bh.y * IP));
	ft_display_swallow_duck_animation(game, x, y);
	sleep(1);
	mlx_destroy_window(game->mlx_c, game->mlx_w);
	game->mlx_w = mlx_new_window(game->mlx_c, END_IP_WIDTH,
			END_IP_HEIGHT, "YOU LOSE");
	ft_display_lose_animation(game);
	ft_close_window(game);
}

static void	ft_display_swallow_duck_animation(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < 30)
	{
		ft_display_animation_frame(game, game->bh.swallow_duck[i], x, y);
		i++;
	}
}

void	ft_display_animation_frame(t_game *game, void *image, int x, int y)
{
	int	delay;

	delay = 100000;
	mlx_put_image_to_window(game->mlx_c, game->mlx_w, image,
		(x * IP), (y * IP));
	usleep(delay);
	mlx_do_sync(game->mlx_c);
}

void	ft_pickup_duck(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	ft_del_prev_msg(game, (game->map.height * IP + 40),
		(game->map.height * IP + 60));
	mlx_string_put(game->mlx_c, game->mlx_w, 0, (game->map.height * IP + 56),
		YELLOW, "The player gathered a duck!");
	while (i < 5)
	{
		if (x > game->player.x)
			ft_display_animation_frame(game, game->duck.pick_duck_l[i], x, y);
		else if (x < game->player.x)
			ft_display_animation_frame(game, game->duck.pick_duck_r[i], x, y);
		else if (y > game->player.y)
			ft_display_animation_frame(game, game->duck.pick_duck_f[i], x, y);
		else if (y < game->player.y)
			ft_display_animation_frame(game, game->duck.pick_duck_b[i], x, y);
		i++;
	}
	i = 0;
	while (i < 16)
	{
		ft_display_animation_frame(game, game->duck.pick_duck[i], x, y);
		i++;
	}
}

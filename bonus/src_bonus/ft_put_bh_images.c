/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_bh_images.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:08:47 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/07 04:34:19 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ft_put_bh_images(t_game *game);
static void	ft_handle_spin_1(t_game *game);
static void	ft_handle_spin_2(t_game *game);
static void	ft_handle_spin_3(t_game *game);
static void	ft_handle_spin_4(t_game *game);

void	ft_put_bh_images(t_game *game)
{
	static int	timer = 0;

	if (!game->bh.stop)
	{
		if (game->bh.spin == 0)
		{
			mlx_put_image_to_window(game->mlx_c, game->mlx_w,
				game->bh.bh_img[game->bh.toggle],
				(game->bh.x * IP), (game->bh.y * IP));
			timer++;
			if (timer == 5000)
			{
				game->bh.toggle = 1 - game->bh.toggle;
				timer = 0;
			}
		}
		else if (game->bh.spin == 1)
			ft_handle_spin_1(game);
		else if (game->bh.spin == 2)
			ft_handle_spin_2(game);
		else if (game->bh.spin == 3)
			ft_handle_spin_3(game);
		else if (game->bh.spin == 4)
			ft_handle_spin_4(game);
	}
}

static void	ft_handle_spin_1(t_game *game)
{
	static int	timer = 0;

	mlx_put_image_to_window(game->mlx_c, game->mlx_w,
		game->bh.spin_wall[game->bh.wall_toggle],
		(game->bh.x * IP), (game->bh.y * IP));
	timer++;
	if (timer == 250)
	{
		game->bh.wall_toggle++;
		timer = 0;
	}
	if (game->bh.wall_toggle == 26)
	{
		game->bh.wall_toggle = 0;
	}
}

static void	ft_handle_spin_2(t_game *game)
{
	static int	timer = 0;

	mlx_put_image_to_window(game->mlx_c, game->mlx_w,
		game->bh.spin_wall[game->bh.wall_toggle],
		(game->bh.x * IP), (game->bh.y * IP));
	timer++;
	if (timer == 250)
	{
		game->bh.wall_toggle--;
		timer = 0;
	}
	if (game->bh.wall_toggle == -1)
	{
		game->bh.wall_toggle = 25;
	}
}

static void	ft_handle_spin_3(t_game *game)
{
	static int	timer_b = 0;

	mlx_put_image_to_window(game->mlx_c, game->mlx_w,
		game->bh.bh_astro_anime[game->player.bh_astro_toggle],
		(game->player.x * IP), (game->player.y * IP));
	timer_b++;
	if (timer_b == 5500)
	{
		game->player.bh_astro_toggle++;
		timer_b = 0;
	}
	if (game->player.bh_astro_toggle == 56)
	{
		game->player.bh_astro_toggle = 9;
	}
}

static void	ft_handle_spin_4(t_game *game)
{
	static int	timer = 0;

	mlx_put_image_to_window(game->mlx_c, game->mlx_w,
		game->bh.spin_agu[game->bh.agu_toggle],
		(game->bh.x * IP), (game->bh.y * IP));
	timer++;
	if (timer == 500)
	{
		game->bh.agu_toggle++;
		timer = 0;
	}
	if (game->bh.agu_toggle == 10)
	{
		game->bh.agu_toggle = 0;
	}
}

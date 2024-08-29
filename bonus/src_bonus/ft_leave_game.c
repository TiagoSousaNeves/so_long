/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_leave_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 03:04:45 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 07:17:31 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_leave_game(t_game *game);
void	ft_undress_astro(t_game *game);
void	ft_put_agu(t_game *game);
void	ft_open_agu(t_game *game);
void	ft_astro_transf(t_game *game);

void	ft_leave_game(t_game *game)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->exit.leave[i], game->exit.x * IP, game->exit.y * IP);
		mlx_do_sync(game->mlx_c);
		usleep(200000);
		i++;
	}
}

void	ft_undress_astro(t_game *game)
{
	int	i;

	i = 22;
	while (i > 0)
	{
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->player.astro_trans[i], game->player.x * IP,
			game->player.y * IP);
		mlx_do_sync(game->mlx_c);
		usleep(100000);
		i--;
	}
}

void	ft_put_agu(t_game *game)
{
	int	i;

	i = 0;
	game->agu.agu = 0;
	while (i < 18)
	{
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->bh.put_agu[i], game->agu.x * IP, game->agu.y * IP);
		usleep(100000);
		mlx_do_sync(game->mlx_c);
		i++;
	}
}

void	ft_open_agu(t_game *game)
{
	int	i;

	i = 0;
	ft_del_prev_msg(game, (game->map.height * IP + 40),
		(game->map.height * IP + 60));
	mlx_string_put(game->mlx_c, game->mlx_w, 0, (game->map.height * IP + 56),
		GREEN, "You open the AGU chest!");
	while (i < 25)
	{
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->agu.open[i], game->agu.x * IP, game->agu.y * IP);
		usleep(100000);
		mlx_do_sync(game->mlx_c);
		i++;
	}
	ft_del_prev_msg(game, (game->map.height * IP + 40),
		(game->map.height * IP + 60));
	mlx_string_put(game->mlx_c, game->mlx_w, 0, (game->map.height * IP + 56),
		GREEN, "Dress the AGU suit to be safe against the black hole!");
}

void	ft_astro_transf(t_game *game)
{
	int	i;

	i = 0;
	while (i < 39)
	{
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->player.astro_trans[i], game->agu.x * IP,
			game->agu.y * IP);
		usleep(100000);
		mlx_do_sync(game->mlx_c);
		i++;
	}
}

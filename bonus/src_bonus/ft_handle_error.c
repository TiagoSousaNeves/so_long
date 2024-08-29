/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:22:16 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 16:21:10 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ft_handle_error(char *str, t_game *game, int error);
void		ft_destroy_image(void *mlx_c, void **images, int size);
static void	ft_destroy_images_part1(t_game *game);
static void	ft_destroy_images_part2(t_game *game);
void		ft_destroy_map(t_game *game);

void	ft_destroy_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.map)
	{
		while (i < game->map.height)
		{
			free(game->map.map[i]);
			i++;
		}
		free(game->map.map);
		game->map.map = NULL;
	}
}

void	ft_destroy_image(void *mlx_c, void **images, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (images[i])
		{
			mlx_destroy_image(mlx_c, images[i]);
			images[i] = NULL;
		}
		i++;
	}
	images = NULL;
}

static void	ft_destroy_images_part1(t_game *game)
{
	if (game->duck.duck_img)
	{
		mlx_destroy_image(game->mlx_c, game->duck.duck_img);
		game->duck.duck_img = NULL;
	}
	ft_destroy_image(game->mlx_c, (void **)game->duck.pick_duck_f, 5);
	ft_destroy_image(game->mlx_c, (void **)game->duck.pick_duck_b, 5);
	ft_destroy_image(game->mlx_c, (void **)game->duck.pick_duck_r, 5);
	ft_destroy_image(game->mlx_c, (void **)game->duck.pick_duck_l, 5);
	ft_destroy_image(game->mlx_c, (void **)game->duck.pick_duck, 16);
	ft_destroy_image(game->mlx_c, (void **)game->agu.agu_img, 2);
	ft_destroy_image(game->mlx_c, (void **)game->agu.open, 25);
	ft_destroy_image(game->mlx_c, (void **)game->wall.floor_wall_img, 5);
	ft_destroy_image(game->mlx_c, (void **)game->exit.closed, 8);
	ft_destroy_image(game->mlx_c, (void **)game->exit.leave, 16);
	ft_destroy_image(game->mlx_c, (void **)game->exit.opened, 8);
	ft_destroy_image(game->mlx_c, (void **)game->exit.open, 39);
}

static void	ft_destroy_images_part2(t_game *game)
{
	ft_destroy_image(game->mlx_c, (void **)game->bh.bh_img, 2);
	ft_destroy_image(game->mlx_c, (void **)game->bh.put_agu, 19);
	ft_destroy_image(game->mlx_c, (void **)game->bh.vanish, 23);
	ft_destroy_image(game->mlx_c, (void **)game->bh.swallow_player, 28);
	ft_destroy_image(game->mlx_c, (void **)game->bh.swallow_duck, 30);
	ft_destroy_image(game->mlx_c, (void **)game->bh.spin_wall, 26);
	ft_destroy_image(game->mlx_c, (void **)game->bh.spin_agu, 10);
	ft_destroy_image(game->mlx_c, (void **)game->bh.bh_astro_anime, 56);
	ft_destroy_image(game->mlx_c, (void **)game->player.astronaut, 4);
	ft_destroy_image(game->mlx_c, (void **)game->player.astro_trans, 40);
	ft_destroy_image(game->mlx_c, (void **)game->player.astro_anime, 26);
	ft_destroy_image(game->mlx_c, (void **)game->player.player_img, 5);
	ft_destroy_image(game->mlx_c, (void **)game->end.lose, 9);
	ft_destroy_image(game->mlx_c, (void **)game->end.win, 12);
	ft_destroy_image(game->mlx_c, (void **)game->end.number, 11);
	ft_destroy_image(game->mlx_c, (void **)game->start, 2);
}

void	ft_handle_error(char *str, t_game *game, int error)
{
	ft_printf("%s", str);
	ft_destroy_images_part1(game);
	ft_destroy_images_part2(game);
	ft_destroy_map(game);
	if (game->mlx_w)
	{
		mlx_destroy_window(game->mlx_c, game->mlx_w);
		game->mlx_w = NULL;
	}
	if (game->mlx_c)
	{
		mlx_destroy_display(game->mlx_c);
		free(game->mlx_c);
		game->mlx_c = NULL;
	}
	exit(error);
}

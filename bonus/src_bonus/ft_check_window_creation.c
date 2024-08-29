/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_window_creation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 03:26:29 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 15:35:28 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_check_window_creation(void *mlx_w, void *mlx_c);
int		ft_handle_rules_keypress(int keycode, t_game *game);
void	*ft_load_image(t_game *game, char *file_path, int *width, int *height);
void	ft_create_game_images(t_game *game);

void	ft_check_window_creation(void *mlx_w, void *mlx_c)
{
	if (mlx_w == NULL)
	{
		mlx_destroy_display(mlx_c);
		free(mlx_c);
		ft_printf("Error\nUnable to create window\n");
		exit(1);
	}
}

int	ft_handle_rules_keypress(int keycode, t_game *game)
{
	if (keycode == 65307)
	{
		ft_close_window(game);
	}
	if (keycode == 32)
	{
		game->time.start_time = time(NULL);
		game->bool_start = 0;
		ft_destroy_image(game->mlx_c, game->start, 2);
		mlx_destroy_window(game->mlx_c, game->mlx_w);
		game->mlx_w = mlx_new_window(game->mlx_c,
				game->map.width * IP, (game->map.height * IP + 80),
				"LIKE42 - THE GAME");
		ft_check_window_creation(game->mlx_w, game->mlx_c);
		ft_create_images(game);
		ft_put_images(game);
		ft_get_position(game, 'P');
		ft_get_position(game, 'B');
		mlx_hook(game->mlx_w, 2, 1L << 0, ft_handle_keypress, game);
		mlx_hook(game->mlx_w, 3, 1L << 1, ft_handle_keyrelease, game);
		mlx_hook(game->mlx_w, 17, 1L << 17, ft_close_window, game);
		mlx_loop_hook(game->mlx_c, ft_update, game);
	}
	return (0);
}

void	*ft_load_image(t_game *game, char *file_path, int *width, int *height)
{
	void	*img;

	img = mlx_xpm_file_to_image(game->mlx_c, file_path, width, height);
	if (!img)
	{
		ft_printf("Error\nloading image: %s\n", file_path);
		ft_handle_error("", game, 1);
	}
	return (img);
}

void	ft_create_game_images(t_game *game)
{
	game->wall.floor_wall_img[0] = ft_load_image(game, FLOOR,
			&game->img_width, &game->img_height);
	game->wall.floor_wall_img[1] = ft_load_image(game, WALL_A,
			&game->img_width, &game->img_height);
	game->wall.floor_wall_img[2] = ft_load_image(game, WALL_B,
			&game->img_width, &game->img_height);
	game->wall.floor_wall_img[3] = ft_load_image(game, AGU_T,
			&game->img_width, &game->img_height);
	game->wall.floor_wall_img[4] = ft_load_image(game, AGU_BH,
			&game->img_width, &game->img_height);
	game->agu.agu_img[0] = ft_load_image(game, AGU_T,
			&game->img_width, &game->img_height);
	game->agu.agu_img[1] = ft_load_image(game, AGU,
			&game->img_width, &game->img_height);
	game->start[0] = ft_load_image(game, START1,
			&game->img_width, &game->img_height);
	game->start[1] = ft_load_image(game, START2,
			&game->img_width, &game->img_height);
	game->duck.duck_img = ft_load_image(game, DUCK,
			&game->img_width, &game->img_height);
	game->bh.bh_img[0] = ft_load_image(game, BH_A,
			&game->img_width, &game->img_height);
	game->bh.bh_img[1] = ft_load_image(game, BH_B,
			&game->img_width, &game->img_height);
}

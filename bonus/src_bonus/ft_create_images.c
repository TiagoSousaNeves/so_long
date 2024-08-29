/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_images.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 01:25:47 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 05:19:51 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ft_create_images(t_game *game);
static void	ft_create_images_part1(t_game *game);
static void	ft_create_images_part2(t_game *game);
static void	ft_read_file_and_create_gif(const char *path_file,
				void (*create_gif)(t_game *, int, void **, int),
				t_game *game, void **str);
static void	ft_create_gif(t_game *game, int fd, void **str, int img_count);

void	ft_create_images(t_game *game)
{
	ft_create_game_images(game);
	ft_create_images_part1(game);
	ft_create_images_part2(game);
}

static void	ft_create_images_part1(t_game *game)
{
	ft_read_file_and_create_gif(PLAYER_PATH, ft_create_gif, game,
		game->player.player_img);
	ft_read_file_and_create_gif(OPEN_AGU_IMG_PATH, ft_create_gif, game,
		game->agu.open);
	ft_read_file_and_create_gif(WALL_SPINNING_PATH, ft_create_gif, game,
		game->bh.spin_wall);
	ft_read_file_and_create_gif(EXIT_CLOSED_PATH, ft_create_gif, game,
		game->exit.closed);
	ft_read_file_and_create_gif(SWALLOW_PLAYER_PATH, ft_create_gif, game,
		game->bh.swallow_player);
	ft_read_file_and_create_gif(SWALLOW_DUCK_PATH, ft_create_gif, game,
		game->bh.swallow_duck);
	ft_read_file_and_create_gif(END_WIN_PATH, ft_create_gif, game,
		game->end.win);
	ft_read_file_and_create_gif(PUT_AGU_PATH, ft_create_gif, game,
		game->bh.put_agu);
	ft_read_file_and_create_gif(BH_VANISH_PATH, ft_create_gif, game,
		game->bh.vanish);
	ft_read_file_and_create_gif(ASTRONAUT_PATH, ft_create_gif, game,
		game->player.astronaut);
	ft_read_file_and_create_gif(ASTRO_TRANSF_PATH, ft_create_gif, game,
		game->player.astro_trans);
	ft_read_file_and_create_gif(ASTRO_ANIME_PATH, ft_create_gif, game,
		game->player.astro_anime);
}

static void	ft_create_images_part2(t_game *game)
{
	ft_read_file_and_create_gif(BH_ASTRO_ANIME_PATH, ft_create_gif, game,
		game->bh.bh_astro_anime);
	ft_read_file_and_create_gif(PICK_DUCK_COMMON_PATH, ft_create_gif, game,
		game->duck.pick_duck);
	ft_read_file_and_create_gif(PICK_DUCK_B_PATH, ft_create_gif, game,
		game->duck.pick_duck_b);
	ft_read_file_and_create_gif(PICK_DUCK_F_PATH, ft_create_gif, game,
		game->duck.pick_duck_f);
	ft_read_file_and_create_gif(PICK_DUCK_L_PATH, ft_create_gif, game,
		game->duck.pick_duck_l);
	ft_read_file_and_create_gif(PICK_DUCK_R_PATH, ft_create_gif, game,
		game->duck.pick_duck_r);
	ft_read_file_and_create_gif(SPIN_AGU_PATH, ft_create_gif, game,
		game->bh.spin_agu);
	ft_read_file_and_create_gif(EXIT_OPENING_PATH, ft_create_gif, game,
		game->exit.open);
	ft_read_file_and_create_gif(EXIT_OPEN_PATH, ft_create_gif, game,
		game->exit.opened);
	ft_read_file_and_create_gif(EXIT_LEAVE_PATH, ft_create_gif, game,
		game->exit.leave);
	ft_read_file_and_create_gif(END_LOSE_PATH, ft_create_gif, game,
		game->end.lose);
	ft_read_file_and_create_gif(END_NUMBER_PATH, ft_create_gif, game,
		game->end.number);
}

static void	ft_read_file_and_create_gif(const char *path_file,
	void (*create_gif)(t_game *, int, void **, int), t_game *game, void **str)
{
	int	fd;
	int	img_count;

	fd = open(path_file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nOpening file: %s.\n", path_file);
		ft_handle_error("", game, 1);
	}
	img_count = ft_count_file_lines(fd);
	create_gif(game, fd, str, img_count);
	close(fd);
}

static void	ft_create_gif(t_game *game, int fd, void **str, int img_count)
{
	int		i;
	char	*path;

	i = 0;
	while (i < img_count)
	{
		path = ft_read_path(fd);
		if (!path)
		{
			ft_printf("Error\nReading line %d from file descriptor %d\n",
				i, fd);
			ft_handle_error("", game, 1);
		}
		str[i] = mlx_xpm_file_to_image(game->mlx_c, path,
				&game->img_width, &game->img_height);
		if (!str[i])
		{
			ft_printf("Error\nLoading image: %s\n", path);
			free(path);
			ft_handle_error("", game, 1);
		}
		free(path);
		i++;
	}
}

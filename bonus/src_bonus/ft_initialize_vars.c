/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_vars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:50:54 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/12 15:34:31 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ft_initialize_vars(t_game *game);
static void	ft_initialize_duck_agu_map_wall(t_duck *duck, t_agu *agu,
				t_map *map, t_wall *wall);
static void	ft_initialize_player_end_general(t_player *player, t_end *end,
				t_game *game);
static void	ft_initialize_exit_bh(t_exit *exit, t_bh *bh);
static void	ft_init_array_img(void **img, int n_img);

static void	ft_init_array_img(void **img, int n_img)
{
	int	i;

	i = 0;
	while (i < n_img)
	{
		img[i] = NULL;
		i++;
	}
}

void	ft_initialize_vars(t_game *game) //era void e agora t_game
{
	ft_initialize_duck_agu_map_wall(&game->duck, &game->agu, &game->map,
		&game->wall);
	ft_initialize_exit_bh(&game->exit, &game->bh);
	ft_initialize_player_end_general(&game->player, &game->end, game);
	game->time.start_time = 0;
	game->time.end_time = 0;
	game->time.game_time = 0;
	game->time.min = 0;
	game->time.sec = 0;
	game->move.itoa_str = NULL;
	game->move.tmp_str = NULL;
	game->move.tmp_str2 = NULL;
}

static void	ft_initialize_duck_agu_map_wall(t_duck *duck, t_agu *agu,
				t_map *map, t_wall *wall)
{
	duck->duck_img = NULL;
	ft_init_array_img((void **)duck->pick_duck, 16);
	ft_init_array_img((void **)duck->pick_duck_b, 5);
	ft_init_array_img((void **)duck->pick_duck_f, 5);
	ft_init_array_img((void **)duck->pick_duck_l, 5);
	ft_init_array_img((void **)duck->pick_duck_r, 5);
	ft_init_array_img((void **)agu->agu_img, 2);
	ft_init_array_img((void **)agu->open, 25);
	agu->agu = 0;
	agu->x = -1;
	agu->y = -1;
	map->agu = 0;
	map->bh = 0;
	map->collectible = 0;
	map->exit = 0;
	map->height = 0;
	map->player = 0;
	map->map = NULL;
	map->width = 0;
	wall->count_a = 0;
	wall->count_b = 0;
	ft_init_array_img((void **)wall->floor_wall_img, 5);
}

static void	ft_initialize_player_end_general(t_player *player, t_end *end,
				t_game *game)
{
	player->x = -1;
	player->y = -1;
	player->ducks = 0;
	player->stop = 0;
	player->agu = 0;
	ft_init_array_img((void **)player->astronaut, 4);
	ft_init_array_img((void **)player->astro_trans, 40);
	ft_init_array_img((void **)player->astro_anime, 26);
	ft_init_array_img((void **)player->player_img, 5);
	player->astro_toggle = 0;
	player->bh_astro_toggle = 0;
	player->moves = 0;
	ft_init_array_img((void **)end->lose, 9);
	ft_init_array_img((void **)end->win, 12);
	ft_init_array_img((void **)end->number, 11);
	game->img_height = 0;
	game->img_width = 0;
	game->mlx_c = NULL;
	game->mlx_w = NULL;
	ft_init_array_img((void **)game->start, 2);
	game->bool_start = 0;
	game->bool_start = 1;
	game->mlx_c = NULL;
	game->mlx_w = NULL;
}

static void	ft_initialize_exit_bh(t_exit *exit, t_bh *bh)
{
	exit->toggle = 0;
	exit->x = -1;
	exit->y = -1;
	ft_init_array_img((void **)exit->closed, 8);
	ft_init_array_img((void **)exit->opened, 8);
	ft_init_array_img((void **)exit->open, 39);
	ft_init_array_img((void **)exit->leave, 16);
	bh->x = -1;
	bh->y = -1;
	ft_init_array_img((void **)bh->bh_img, 2);
	ft_init_array_img((void **)bh->put_agu, 19);
	ft_init_array_img((void **)bh->vanish, 23);
	ft_init_array_img((void **)bh->swallow_player, 28);
	ft_init_array_img((void **)bh->swallow_duck, 30);
	ft_init_array_img((void **)bh->spin_wall, 26);
	ft_init_array_img((void **)bh->spin_agu, 10);
	ft_init_array_img((void **)bh->bh_astro_anime, 56);
	bh->agu_toggle = 0;
	bh->toggle = 0;
	bh->wall_toggle = 0;
	bh->spin = 0;
	bh->agu = 0;
	bh->stop = 0;
	bh->c = '\0';
	bh->code = 0;
}

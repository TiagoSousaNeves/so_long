/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_exit_images.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 03:10:00 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 17:18:44 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ft_put_exit_images(t_game *game);
static void	ft_handle_exit_toggle(t_game *game, int *timer);
void		ft_put_astro_anime(t_game *game);
void		ft_vanish_bh(t_game *game);
char		*ft_read_path(int fd);

void	ft_put_exit_images(t_game *game)
{
	static int	timer;

	if (game->player.ducks != game->map.collectible
		|| (game->wall.count_a && game->wall.count_b))
	{
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->exit.closed[game->exit.toggle],
			(game->exit.x * IP), (game->exit.y * IP));
		timer++;
		ft_handle_exit_toggle(game, &timer);
	}
	else if (game->player.ducks == game->map.collectible
		&& (!game->wall.count_a || !game->wall.count_b))
	{
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->exit.opened[game->exit.toggle],
			(game->exit.x * IP), (game->exit.y * IP));
		timer++;
		ft_handle_exit_toggle(game, &timer);
	}
}

static void	ft_handle_exit_toggle(t_game *game, int *timer)
{
	if (*timer == 4000)
	{
		game->exit.toggle++;
		*timer = 0;
		if (game->exit.toggle == 8)
			game->exit.toggle = 0;
	}
}

void	ft_vanish_bh(t_game *game)
{
	int	i;

	i = 0;
	ft_del_prev_msg(game, (game->map.height * IP + 40),
		(game->map.height * IP + 60));
	mlx_string_put(game->mlx_c, game->mlx_w, 0, (game->map.height * IP + 56),
		GREEN, "The black hole vanished!");
	ft_del_prev_msg(game, (game->map.height * IP + 20),
		(game->map.height * IP + 40));
	game->map.map[game->bh.y][game->bh.x] = '0';
	while (i < 23)
	{
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->bh.vanish[i], game->bh.x * IP, game->bh.y * IP);
		usleep(100000);
		mlx_do_sync(game->mlx_c);
		i++;
	}
	ft_del_prev_msg(game, (game->map.height * IP + 40),
		(game->map.height * IP + 60));
	mlx_string_put(game->mlx_c, game->mlx_w, 0, (game->map.height * IP + 56),
		GREEN, "The exit is now open!");
	return ;
}

void	ft_put_astro_anime(t_game *game)
{
	static unsigned int	timer;

	if (game->player.stop && game->bh.spin != 3
		&& !game->bh.stop)
	{
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->player.astro_anime[game->player.astro_toggle],
			(game->player.x * IP), (game->player.y * IP));
		timer++;
		if (timer == 5000)
		{
			game->player.astro_toggle++;
			timer = 0;
		}
		if (game->player.astro_toggle == 25)
			game->player.astro_toggle = 0;
	}
	return ;
}

char	*ft_read_path(int fd)
{
	char	*line;
	char	*new_line;

	line = ft_get_next_line(fd);
	if (line == NULL)
		return (NULL);
	new_line = ft_strrchr(line, '\n');
	if (new_line)
		*new_line = '\0';
	return (line);
}

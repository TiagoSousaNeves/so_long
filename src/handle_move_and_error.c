/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_move_and_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 02:44:33 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/12 15:48:28 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void		ft_handle_error(char *str, t_game *game, int error);
int			ft_close_window(t_game *game);
int			ft_handle_keypress(int keycode, t_game *game);
static void	ft_move_player(t_game *game, int new_x, int new_y);
void		ft_put_images(t_game *game);

void	ft_handle_error(char *str, t_game *game, int error)
{
	int	i;

	i = -1;
	ft_printf("%s", str);
	while (++i < 5)
	{
		if (game->images[i])
		{
			mlx_destroy_image(game->mlx_c, game->images[i]);
			game->images[i] = NULL;
		}
	}
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

int	ft_handle_keypress(int keycode, t_game *game)
{
	if (keycode == 65307)
		ft_handle_error("Bye, bye!\n", game, 0);
	else if (keycode == 119 || keycode == 65362)
		ft_move_player(game, game->player.x, game->player.y - 1);
	else if (keycode == 115 || keycode == 65364)
		ft_move_player(game, game->player.x, game->player.y + 1);
	else if (keycode == 97 || keycode == 65361)
		ft_move_player(game, game->player.x - 1, game->player.y);
	else if (keycode == 100 || keycode == 65363)
		ft_move_player(game, game->player.x + 1, game->player.y);
	return (0);
}

static void	ft_move_player(t_game *game, int new_x, int new_y)
{
	if (game->map.map[new_y][new_x] != '1'
		&& game->map.map[new_y][new_x] != 'E')
	{
		game->player.moves++;
		ft_printf("The player did %i moves.\n", game->player.moves);
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->images[0], game->player.x * IP, game->player.y * IP);
		if (game->map.map[new_y][new_x] == 'C')
			game->player.ducks++;
		game->player.x = new_x;
		game->player.y = new_y;
		game->map.map[new_y][new_x] = 'P';
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->images[2], new_x * IP, new_y * IP);
	}
	if (game->map.map[new_y][new_x] == 'E'
		&& game->map.collectible == game->player.ducks)
	{
		game->player.moves++;
		ft_printf("The player did %i moves!\n", game->player.moves);
		ft_handle_error("You Win!\n", game, 0);
	}
	if (game->map.map[new_y][new_x] == '1'
		|| game->map.map[new_y][new_x] == 'E')
		ft_printf("The player can't move to a wall\n");
}

int	ft_close_window(t_game *game)
{
	ft_handle_error("Bye, bye!\n", game, 0);
	exit(1);
}

void	ft_put_images(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map.height)
	{
		j = -1;
		while (++j < game->map.width)
		{
			if (game->map.map[i][j] == '0')
				game->img = game->images[0];
			else if (game->map.map[i][j] == '1')
				game->img = game->images[1];
			else if (game->map.map[i][j] == 'P')
				game->img = game->images[2];
			else if (game->map.map[i][j] == 'C')
				game->img = game->images[3];
			else if (game->map.map[i][j] == 'E')
				game->img = game->images[4];
			if (game->img)
				mlx_put_image_to_window(game->mlx_c, game->mlx_w,
					game->img, j * IP, i * IP);
		}
	}
}

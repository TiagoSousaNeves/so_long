/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_stings_display.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:39:29 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 07:59:42 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ft_print_count_moves(t_game *game);
char		*ft_print_player_move(t_game *game, int new_x, int new_y);
char		*ft_print_bh_move(t_game *game, int new_x, int new_y);
void		ft_print_nb_wall_a(t_game *game);
void		ft_print_nb_wall_b(t_game *game);

void	ft_print_count_moves(t_game *game)
{
	int		i;
	int		j;

	i = game->map.height * IP + 67;
	j = 3 * IP + 40;
	game->move.itoa_str = ft_itoa(game->player.moves);
	game->move.tmp_str = ft_strjoin("Click to move = ", game->move.itoa_str);
	free(game->move.itoa_str);
	while (i < game->map.height * IP + 80)
	{
		j = 3 * IP + 40;
		while (j < game->map.width * IP)
		{
			mlx_pixel_put(game->mlx_c, game->mlx_w, j, i, BLACK);
			j++;
		}
		i++;
	}
	mlx_string_put(game->mlx_c, game->mlx_w, (3 * IP + 40),
		(game->map.height * IP + 76), AQUA, game->move.tmp_str);
	free(game->move.tmp_str);
}

char	*ft_print_player_move(t_game *game, int new_x, int new_y)
{
	game->move.itoa_str = ft_itoa(game->player.x);
	game->move.tmp_str = ft_strjoin("The player moved from(",
			(const char *)game->move.itoa_str);
	free(game->move.itoa_str);
	game->move.tmp_str2 = ft_strjoin(game->move.tmp_str, ", ");
	free(game->move.tmp_str);
	game->move.itoa_str = ft_itoa(game->player.y);
	game->move.tmp_str = ft_strjoin(game->move.tmp_str2, game->move.itoa_str);
	free(game->move.tmp_str2);
	free(game->move.itoa_str);
	game->move.tmp_str2 = ft_strjoin(game->move.tmp_str, ") to (");
	free(game->move.tmp_str);
	game->move.itoa_str = ft_itoa(new_x);
	game->move.tmp_str = ft_strjoin(game->move.tmp_str2, game->move.itoa_str);
	free(game->move.tmp_str2);
	free(game->move.itoa_str);
	game->move.tmp_str2 = ft_strjoin(game->move.tmp_str, ", ");
	free(game->move.tmp_str);
	game->move.itoa_str = ft_itoa(new_y);
	game->move.tmp_str = ft_strjoin(game->move.tmp_str2, game->move.itoa_str);
	free(game->move.tmp_str2);
	free(game->move.itoa_str);
	game->move.tmp_str2 = ft_strjoin(game->move.tmp_str, ").");
	free(game->move.tmp_str);
	return (game->move.tmp_str2);
}

void	ft_print_nb_wall_a(t_game *game)
{
	int		i;
	int		j;

	i = game->map.height * IP + 67;
	j = 0;
	game->move.itoa_str = ft_itoa(game->wall.count_a);
	game->move.tmp_str = ft_strjoin("Wall_A = ", game->move.itoa_str);
	free(game->move.itoa_str);
	while (i < game->map.height * IP + 80)
	{
		j = 0;
		while (j < IP + 32)
		{
			mlx_pixel_put(game->mlx_c, game->mlx_w, j, i, BLACK);
			j++;
		}
		i++;
	}
	mlx_string_put(game->mlx_c, game->mlx_w, 0,
		(game->map.height * IP + 76), ORANGE, game->move.tmp_str);
	free(game->move.tmp_str);
}

void	ft_print_nb_wall_b(t_game *game)
{
	int		i;
	int		j;

	i = game->map.height * IP + 65;
	j = IP + 40;
	game->move.itoa_str = ft_itoa(game->wall.count_b);
	game->move.tmp_str = ft_strjoin("Wall_B = ", game->move.itoa_str);
	free(game->move.itoa_str);
	while (i < game->map.height * IP + 78)
	{
		j = IP + 40;
		while (j < 3 * IP)
		{
			mlx_pixel_put(game->mlx_c, game->mlx_w, j, i, BLACK);
			j++;
		}
		i++;
	}
	mlx_string_put(game->mlx_c, game->mlx_w, (IP + 44),
		(game->map.height * IP + 76), SILVER, game->move.tmp_str);
	free(game->move.tmp_str);
}

char	*ft_print_bh_move(t_game *game, int new_x, int new_y)
{
	game->move.itoa_str = ft_itoa(game->bh.x);
	game->move.tmp_str = ft_strjoin("The black hole moved from(",
			(const char *)game->move.itoa_str);
	free(game->move.itoa_str);
	game->move.tmp_str2 = ft_strjoin(game->move.tmp_str, ", ");
	free(game->move.tmp_str);
	game->move.itoa_str = ft_itoa(game->bh.y);
	game->move.tmp_str = ft_strjoin(game->move.tmp_str2, game->move.itoa_str);
	free(game->move.tmp_str2);
	free(game->move.itoa_str);
	game->move.tmp_str2 = ft_strjoin(game->move.tmp_str, ") to (");
	free(game->move.tmp_str);
	game->move.itoa_str = ft_itoa(new_x);
	game->move.tmp_str = ft_strjoin(game->move.tmp_str2, game->move.itoa_str);
	free(game->move.tmp_str2);
	free(game->move.itoa_str);
	game->move.tmp_str2 = ft_strjoin(game->move.tmp_str, ", ");
	free(game->move.tmp_str);
	game->move.itoa_str = ft_itoa(new_y);
	game->move.tmp_str = ft_strjoin(game->move.tmp_str2, game->move.itoa_str);
	free(game->move.tmp_str2);
	free(game->move.itoa_str);
	game->move.tmp_str2 = ft_strjoin(game->move.tmp_str, ").");
	free(game->move.tmp_str);
	return (game->move.tmp_str2);
}

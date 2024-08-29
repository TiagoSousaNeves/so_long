/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_so_long_mlx_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 02:13:15 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 17:14:42 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_initialize_mlx(t_game *game);
void	ft_update_bh_spin(t_game *game);

void	ft_initialize_mlx(t_game *game)
{
	game->mlx_c = mlx_init();
	if (game->mlx_c == NULL)
	{
		ft_handle_error("Error\nUnable to initialize MLX\n", game, 1);
	}
}

void	ft_update_bh_spin(t_game *game)
{
	ft_del_prev_msg(game, (game->map.height * IP + 20),
		(game->map.height * IP + 40));
	mlx_string_put(game->mlx_c, game->mlx_w, 0, (game->map.height * IP + 36),
		BLUE, "Black hole cannot move to the exit or the AGU suit!");
	if (game->bh.c == '1')
		game->bh.spin = 2;
	else if (game->bh.c == '2')
		game->bh.spin = 1;
}

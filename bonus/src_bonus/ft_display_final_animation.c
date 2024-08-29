/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_final_animation.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 21:51:40 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/05 14:01:05 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ft_display_final_animation(t_game *game, char *moves,
				char *game_time_str);
static void	ft_put_time(t_game *game, char *game_time_str);
static void	ft_put_moves(t_game *game, char *moves);

void	ft_display_final_animation(t_game *game, char *moves,
		char *game_time_str)
{
	int	n;
	int	i;

	n = 1;
	while (n >= 0)
	{
		i = 0;
		while (i < 12)
		{
			mlx_put_image_to_window(game->mlx_c, game->mlx_w,
				game->end.win[i], 0, 0);
			usleep(225000);
			mlx_do_sync(game->mlx_c);
			ft_put_moves(game, moves);
			ft_put_time(game, game_time_str);
			mlx_do_sync(game->mlx_c);
			i++;
		}
		n--;
	}
}

static void	ft_put_time(t_game *game, char *game_time_str)
{
	int	j;
	int	len;
	int	digit;

	j = 0;
	len = ft_strlen(game_time_str);
	while (j < len)
	{
		if (game_time_str[j] == ':')
		{
			mlx_put_image_to_window(game->mlx_c, game->mlx_w,
				game->end.number[10],
				(END_IP_WIDTH - 32 * (len - j)),
				(END_IP_HEIGHT - IP * 8));
		}
		else
		{
			digit = game_time_str[j] - '0';
			mlx_put_image_to_window(game->mlx_c, game->mlx_w,
				game->end.number[digit],
				(END_IP_WIDTH - 32 * (len - j)),
				(END_IP_HEIGHT - IP * 8));
		}
		j++;
	}
}

static void	ft_put_moves(t_game *game, char *moves)
{
	int	j;
	int	len;
	int	digit;

	j = 0;
	len = ft_strlen(moves);
	while (j < len)
	{
		digit = moves[j] - '0';
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->end.number[digit],
			(END_IP_WIDTH - 32 * (len - j)),
			(END_IP_HEIGHT - IP * 9));
		j++;
	}
}

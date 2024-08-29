/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_leave_and_win.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 05:51:10 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 07:17:31 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ft_leave_and_win(t_game *game);
static void	ft_display_victory_screen(t_game *game);
static char	*ft_format_game_time(t_game *game);
static char	*ft_print_time_msg(char *time_msg);
static char	*ft_print_moves_msg(char *moves_msg);

void	ft_leave_and_win(t_game *game)
{
	char	*game_time_str;
	char	*player_moves_str;
	char	*msg;

	game_time_str = ft_format_game_time(game);
	player_moves_str = ft_itoa(game->player.moves);
	ft_del_prev_msg(game, (game->map.height * IP),
		(game->map.height * IP + 60));
	mlx_string_put(game->mlx_c, game->mlx_w, 0, (game->map.height * IP + 16),
		GREEN, "Congratulations! You win!");
	msg = ft_print_moves_msg(player_moves_str);
	mlx_string_put(game->mlx_c, game->mlx_w, 0, (game->map.height * IP + 36),
		WHITE, msg);
	free(msg);
	msg = ft_print_time_msg(game_time_str);
	mlx_string_put(game->mlx_c, game->mlx_w, 0, (game->map.height * IP + 56),
		WHITE, msg);
	free(msg);
	ft_display_victory_screen(game);
	ft_display_final_animation(game, player_moves_str, game_time_str);
	free(game_time_str);
	free(player_moves_str);
	ft_close_window(game);
}

static char	*ft_print_moves_msg(char *moves_msg)
{
	char	*msg;
	char	*temp_msg;

	temp_msg = ft_strjoin("You pressed the move buttons ", moves_msg);
	msg = ft_strjoin(temp_msg, " times to win the game!");
	free(temp_msg);
	return (msg);
}

static char	*ft_print_time_msg(char *time_msg)
{
	char	*msg;
	char	*temp_msg;

	temp_msg = ft_strjoin("You took ", time_msg);
	msg = ft_strjoin(temp_msg, " to win the game!");
	free(temp_msg);
	return (msg);
}

static void	ft_display_victory_screen(t_game *game)
{
	char	*moves;

	moves = ft_itoa(game->player.moves);
	if (game->player.agu)
	{
		ft_undress_astro(game);
		mlx_put_image_to_window(game->mlx_c, game->mlx_w,
			game->agu.agu_img[1], game->player.x * IP,
			game->player.y * IP);
		mlx_do_sync(game->mlx_c);
	}
	usleep(80000);
	ft_leave_game(game);
	mlx_do_sync(game->mlx_c);
	usleep(50000);
	mlx_destroy_window(game->mlx_c, game->mlx_w);
	game->mlx_w = mlx_new_window(game->mlx_c, END_IP_WIDTH, END_IP_HEIGHT,
			"YOU WIN");
	free(moves);
}

static char	*ft_format_game_time(t_game *game)
{
	char	*min_str;
	char	*temp;
	char	*game_time_str;

	min_str = NULL;
	temp = NULL;
	game_time_str = NULL;
	game->time.end_time = time(NULL);
	game->time.game_time = (int)difftime(game->time.end_time,
			game->time.start_time);
	game->time.min = (int)game->time.game_time / 60;
	game->time.sec = (int)game->time.game_time % 60;
	min_str = ft_itoa(game->time.min);
	temp = ft_strjoin(min_str, ":");
	free(min_str);
	min_str = NULL;
	min_str = ft_itoa(game->time.sec);
	game_time_str = ft_strjoin(temp, min_str);
	free(min_str);
	free(temp);
	return (game_time_str);
}

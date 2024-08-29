/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:27:02 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 18:19:40 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int			main(int argc, char **argv);
static void	ft_check_arguments(int argc);
static void	ft_load_start_images(t_game *game, void **start_images,
				int *img_width, int *img_height);
static void	ft_print_instructions_part1(t_game *game);
static void	ft_print_instructions_part2(t_game *game);

int	main(int argc, char **argv)
{
	t_game	game;

	ft_check_arguments(argc);
	ft_check_mapfile(argv[1]);
	ft_initialize_vars(&game);
	ft_initialize_mlx(&game);
	game.mlx_w = mlx_new_window(game.mlx_c, END_IP_WIDTH,
			END_IP_HEIGHT + 400, "LIKE42 - Game Instructions");
	ft_handle_map(argv[1], &game);
	ft_get_position(&game, 'B');
	ft_get_position(&game, 'E');
	ft_check_window_creation(game.mlx_w, game.mlx_c);
	ft_load_start_images(&game, game.start, &game.img_width,
		&game.img_height);
	ft_print_instructions_part1(&game);
	ft_print_instructions_part2(&game);
	mlx_loop_hook(game.mlx_c, (int (*)(void *))ft_put_start, &game);
	mlx_hook(game.mlx_w, 2, 1L << 0, ft_handle_rules_keypress, &game);
	mlx_hook(game.mlx_w, 17, 1L << 17, ft_close_window, &game);
	mlx_loop(game.mlx_c);
	ft_handle_error("Thank you for playing Like42\n", &game, 0);
	return (0);
}

static void	ft_print_instructions_part1(t_game *game)
{
	mlx_string_put(game->mlx_c, game->mlx_w, (END_IP_WIDTH / 2) - (3 * IP / 2),
		END_IP_HEIGHT + 16, YELLOW, "Welcome to LIKE42 - THE GAME!");
	mlx_string_put(game->mlx_c, game->mlx_w, 2.8 * IP, END_IP_HEIGHT + 32,
		WHITE, "Please pay close attention to the game instructions,"
		" or you may be defeated on your first attempt!");
	mlx_string_put(game->mlx_c, game->mlx_w, 16, END_IP_HEIGHT + 64,
		GREEN, "To win the game:");
	mlx_string_put(game->mlx_c, game->mlx_w, 16, END_IP_HEIGHT + 80,
		GREEN, "- The player must gather all the ducks.");
	mlx_string_put(game->mlx_c, game->mlx_w, 16, END_IP_HEIGHT + 96,
		GREEN, "- The black hole (bh) must turn all the walls (aka 42 "
		"students) into the same position (either front or back).");
	mlx_string_put(game->mlx_c, game->mlx_w, 16, END_IP_HEIGHT + 128,
		CORAL, "Key Movements:");
	mlx_string_put(game->mlx_c, game->mlx_w, 16, END_IP_HEIGHT + 144,
		CORAL, "- The black hole moves in the opposite direction of the "
		"player's movement.");
	mlx_string_put(game->mlx_c, game->mlx_w, 16, END_IP_HEIGHT + 160,
		CORAL, "- The black hole has no barriers except the exit and the "
		"content of the AGU chest.");
	mlx_string_put(game->mlx_c, game->mlx_w, 16, END_IP_HEIGHT + 176,
		CORAL, "- The player cannot pass through the walls or exit while "
		"is closed.");
}

static void	ft_print_instructions_part2(t_game *game)
{
	mlx_string_put(game->mlx_c, game->mlx_w, 16, END_IP_HEIGHT + 192,
		CORAL, "- To release the AGU, press SPACE (it is heavy and useless"
		" if the black hole is gone).");
	mlx_string_put(game->mlx_c, game->mlx_w, 16, END_IP_HEIGHT + 224,
		PURPLE, "Important Rules:");
	mlx_string_put(game->mlx_c, game->mlx_w, 16, END_IP_HEIGHT + 240,
		PURPLE, "- If the black hole swallows a duck, you lose.");
	mlx_string_put(game->mlx_c, game->mlx_w, 16, END_IP_HEIGHT + 256,
		PURPLE, "- If the black hole swallows the player, you lose.");
	mlx_string_put(game->mlx_c, game->mlx_w, 16, END_IP_HEIGHT + 272,
		PURPLE, "- Each time the BH moves through a wall, it will rotate.");
	mlx_string_put(game->mlx_c, game->mlx_w, 16, END_IP_HEIGHT + 288,
		PURPLE, "- The AGU chest will be available when the player gathers "
		"all the ducks. Besides that, the bh must be on the floor!");
	mlx_string_put(game->mlx_c, game->mlx_w, 16, END_IP_HEIGHT + 304,
		PURPLE, "- When active, the AGU protects the player from the bh, "
		"however, the player cannot move while bh exists.");
	mlx_string_put(game->mlx_c, game->mlx_w, 16, END_IP_HEIGHT + 336,
		AQUA, "Keep an eye on the UI display region, as it will"
		" provide useful information during the game.");
	mlx_string_put(game->mlx_c, game->mlx_w, 16, END_IP_HEIGHT + 352,
		AQUA, "The number of times you press the move buttons and the game"
		" time will be presented to you in case of victory.");
	mlx_string_put(game->mlx_c, game->mlx_w, 16, END_IP_HEIGHT + 384,
		WHITE, "Press SPACE and Good duck! :P");
}

static void	ft_check_arguments(int argc)
{
	if (argc != 2)
	{
		ft_printf("Error\nIncorrect number of arguments\n");
		exit(1);
	}
}

static void	ft_load_start_images(t_game *game, void **start_images,
		int *img_width, int *img_height)
{
	start_images[0] = ft_load_image(game, START1, img_width, img_height);
	start_images[1] = ft_load_image(game, START2, img_width, img_height);
	if (!start_images[0] || !start_images[1])
	{
		ft_handle_error("Error\nLoading images\n", game, 1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 02:44:33 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/08 19:10:44 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int			main(int argc, char **argv);
static void	ft_check_arguments(int argc);
static void	ft_initialize_mlx(void **mlx_c, t_game *game);
static void	ft_initialize_vars(t_game *game);
static void	ft_create_images(t_game *game);

int	main(int argc, char **argv)
{
	t_game	game;

	ft_check_arguments(argc);
	ft_initialize_mlx(&game.mlx_c, &game);
	ft_initialize_vars(&game);
	ft_handle_map(argv[1], &game);
	ft_create_images(&game);
	game.mlx_w = mlx_new_window(game.mlx_c, game.map.width * IP,
			game.map.height * IP, "Like42");
	if (game.mlx_w == NULL)
		ft_handle_error("Error\nUnable to create window\n", &game, 1);
	ft_put_images(&game);
	ft_get_player_position(&game);
	mlx_hook(game.mlx_w, 2, 1L << 0, ft_handle_keypress, &game);
	mlx_hook(game.mlx_w, 17, 1L << 17, ft_close_window, &game);
	mlx_loop(game.mlx_c);
	ft_handle_error("Thank you for playing Like42\n", &game, 0);
	return (0);
}

static void	ft_check_arguments(int argc)
{
	if (argc != 2)
	{
		ft_printf("Error\nIncorrect number of arguments\n");
		exit(1);
	}
}

static void	ft_initialize_mlx(void **mlx_c, t_game *game)
{
	*mlx_c = mlx_init();
	if (*mlx_c == NULL)
	{
		ft_handle_error("Error\nUnable to initialize MLX\n", game, 1);
	}
}

static void	ft_initialize_vars(t_game *game)
{
	game->map.map = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.player = 0;
	game->map.collectible = 0;
	game->map.exit = 0;
	game->player.x = 0;
	game->player.y = 0;
	game->player.ducks = 0;
	game->player.moves = 0;
	game->images[0] = NULL;
	game->images[1] = NULL;
	game->images[2] = NULL;
	game->images[3] = NULL;
	game->images[4] = NULL;
	game->images[5] = NULL;
	game->img = NULL;
	game->mlx_w = NULL;
}

static void	ft_create_images(t_game *game)
{
	int	img_width;
	int	img_height;

	img_height = 0;
	img_width = 0;
	game->images[0] = mlx_xpm_file_to_image(game->mlx_c, FLOOR, &img_width,
			&img_height);
	if (!game->images[0])
		ft_handle_error("Error\nloading image: floor.xpm\n", game, 1);
	game->images[1] = mlx_xpm_file_to_image(game->mlx_c, WALL, &img_width,
			&img_height);
	if (!game->images[1])
		ft_handle_error("Error\nloading image: wall.xpm\n", game, 1);
	game->images[2] = mlx_xpm_file_to_image(game->mlx_c, PLAYER, &img_width,
			&img_height);
	if (!game->images[2])
		ft_handle_error("Error\nloading image: player.xpm\n", game, 1);
	game->images[3] = mlx_xpm_file_to_image(game->mlx_c, DUCK, &img_width,
			&img_height);
	if (!game->images[3])
		ft_handle_error("Error\nloading image: duck.xpm\n", game, 1);
	game->images[4] = mlx_xpm_file_to_image(game->mlx_c, EXIT, &img_width,
			&img_height);
	if (!game->images[4])
		ft_handle_error("Error\nloading image: exit.xpm\n", game, 1);
}

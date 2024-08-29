/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_playability.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:59:08 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 04:43:19 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ft_check_map_playability(t_game *game);
static char	**ft_copy_map(t_game *game, int i, int j);
static void	ft_check_map_content(char **map, int height,
				int width, t_game *game);
int			ft_put_start(t_game *game);

void	ft_check_map_playability(t_game *game)
{
	char	**map_temp;
	int		i;
	int		j;

	i = -1;
	j = -1;
	ft_get_position(game, 'P');
	map_temp = ft_copy_map(game, i, j);
	if (!map_temp)
		ft_handle_error("Error\nCopying map\n", game, 1);
	ft_check_map_content(map_temp, game->map.height, game->map.width, game);
	ft_check_ducks_gathering(map_temp, game, game->map.collectible, 'F');
	while (++i < game->map.height)
		free(map_temp[i]);
	free(map_temp);
}

static char	**ft_copy_map(t_game *game, int i, int j)
{
	char	**map_temp;

	map_temp = malloc(sizeof(char *) * (game->map.height + 1));
	if (map_temp == NULL)
		ft_handle_error("Error\nAllocating memory for map copy\n", game, 1);
	while (++i < game->map.height)
	{
		map_temp[i] = malloc(game->map.width + 1);
		if (map_temp[i] == NULL)
		{
			while (--i >= 0)
				free(map_temp[i]);
			free(map_temp);
			ft_handle_error("Error\nAllocating memory for map copy\n", game,
				1);
		}
		j = -1;
		while (++j < game->map.width)
			map_temp[i][j] = game->map.map[i][j];
		map_temp[i][game->map.width] = '\0';
	}
	map_temp[game->map.height] = NULL;
	return (map_temp);
}

static void	ft_check_map_content(char **map, int height,
				int width, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'E' &&
				map[i][j] != 'P' && map[i][j] != 'C' && map[i][j] != 'B' &&
				map[i][j] != '2')
			{
				ft_printf("Error\nVerifying the map, map must only contain "
					"'1', '2', '0', 'P', 'C', 'E' and 'B'\n");
				ft_destroy_map(game);
				exit(1);
			}
			j++;
		}
		i++;
	}
}

int	ft_put_start(t_game *game)
{
	static int	img_index = 0;
	static int	timer = 0;

	if (timer++ == 500)
	{
		timer = 0;
		img_index = (img_index + 1) % 2;
	}
	mlx_put_image_to_window(game->mlx_c, game->mlx_w,
		game->start[img_index], 0, 0);
	return (0);
}

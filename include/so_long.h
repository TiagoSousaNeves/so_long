/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:24:55 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/12 16:22:16 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../lib/minilibx-linux/mlx.h"
# include "../lib/ft_printf/ft_printf.h"
# include <stdlib.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <unistd.h>

# define IP 48
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define FLOOR	"textures/floor.xpm"
# define WALL	"textures/wall.xpm"
# define PLAYER	"textures/player.xpm"
# define DUCK	"textures/duck.xpm"
# define EXIT	"textures/exit.xpm"

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
	int		player;
	int		collectible;
	int		exit;
}			t_map;

typedef struct s_player
{
	int		x;
	int		y;
	int		ducks;
	int		moves;
}			t_player;

typedef struct s_game
{
	void		*mlx_c;
	void		*mlx_w;
	t_map		map;
	void		*images[6];
	void		*img;
	t_player	player;
}			t_game;

void	ft_handle_map(char *str, t_game *game);
void	ft_put_images(t_game *game);
char	*ft_get_next_line(int fd);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *str);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *str);
int		ft_handle_keypress(int keycode, t_game *game);
int		ft_close_window(t_game *game);
void	ft_check_map(t_game *game);
void	ft_check_map_errors(t_game *game);
void	ft_get_player_position(t_game *game);
void	ft_handle_error(char *str, t_game *game, int error);
void	ft_destroy_map(t_game *game);
void	ft_check_map_playability(t_game *game);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:19:51 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/12 16:22:16 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../../lib/minilibx-linux/mlx.h"
# include "../../lib/ft_printf/ft_printf.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <time.h>

/*	Image Paths */
# define AGU	"bonus/textures_bonus/AGU/agu.xpm"
# define AGU_T	"bonus/textures_bonus/AGU/tresure.xpm"
# define AGU_BH	"bonus/textures_bonus/Player/astrounaut_anime/1A.xpm"
# define BH_A	"bonus/textures_bonus/BH/bh_A.xpm"
# define BH_B	"bonus/textures_bonus/BH/bh_B.xpm"
# define DUCK	"bonus/textures_bonus/Duck/duck.xpm"
# define FLOOR	"bonus/textures_bonus/Floor/floor.xpm"
# define START1	"bonus/textures_bonus/Start/start1.xpm"
# define START2	"bonus/textures_bonus/Start/start2.xpm"
# define WALL_A	"bonus/textures_bonus/Wall/wall_B.xpm"
# define WALL_B	"bonus/textures_bonus/Wall/wall_F.xpm"

/*	Config Paths */
# define ASTRONAUT_PATH			"bonus/config_binus/astronaut_img_path.txt"
# define ASTRO_ANIME_PATH		"bonus/config_binus/astro_anime_img_path.txt"
# define ASTRO_TRANSF_PATH		"bonus/config_binus/astro_transf_img_path.txt"
# define BH_ASTRO_ANIME_PATH	"bonus/config_binus/bh_astro_anime_img_path.txt"
# define BH_VANISH_PATH			"bonus/config_binus/bh_vanish_img_path.txt"
# define END_LOSE_PATH			"bonus/config_binus/end_lose_img_paths.txt"
# define END_NUMBER_PATH		"bonus/config_binus/end_numbers_img_paths.txt"
# define END_WIN_PATH			"bonus/config_binus/end_win_img_paths.txt"
# define EXIT_CLOSED_PATH		"bonus/config_binus/exit_closed_img_path.txt"
# define EXIT_LEAVE_PATH		"bonus/config_binus/exit_leave_img_path.txt"
# define EXIT_OPEN_PATH			"bonus/config_binus/exit_open_img_path.txt"
# define EXIT_OPENING_PATH		"bonus/config_binus/exit_opening_img_path.txt"
# define OPEN_AGU_IMG_PATH		"bonus/config_binus/agu_open_img_path.txt"
# define PICK_DUCK_B_PATH		"bonus/config_binus/pick_duck_B_img_path.txt"
# define PICK_DUCK_COMMON_PATH \
	"bonus/config_binus/pick_duck_common_img_path.txt"
# define PICK_DUCK_F_PATH		"bonus/config_binus/pick_duck_F_img_path.txt"
# define PICK_DUCK_L_PATH		"bonus/config_binus/pick_duck_L_img_path.txt"
# define PICK_DUCK_R_PATH		"bonus/config_binus/pick_duck_R_img_path.txt"
# define PLAYER_PATH			"bonus/config_binus/player_img_paths.txt"
# define PUT_AGU_PATH			"bonus/config_binus/put_agu_img_path.txt"
# define SPIN_AGU_PATH			"bonus/config_binus/agu_spinning_img_paths.txt"
# define SWALLOW_DUCK_PATH \
	"bonus/config_binus/ducks_swallowed_img_paths.txt"
# define SWALLOW_PLAYER_PATH \
	"bonus/config_binus/player_swallowed_img_paths.txt"
# define WALL_SPINNING_PATH		"bonus/config_binus/wall_spinning_img_paths.txt"

/*	Color Definitions */
# define AQUA	0x00FFFF
# define BLACK	0x000000
# define BLUE	0x0000FF
# define CORAL	0xFF7F50
# define GREEN	0x00FF00
# define ORANGE	0xFFA500
# define PURPLE	0xFF00FF
# define RED	0xFF0000
# define SILVER	0xC0C0C0
# define WHITE	0xFFFFFF
# define YELLOW	0xFFFF00

/*	Constants */
# define IP						64
# define END_IP_WIDTH				960
# define END_IP_HEIGHT				600
# define BUFFER_SIZE				1

/*	Struct Definitions */
typedef struct s_print_moves
{
	char	*tmp_str;
	char	*tmp_str2;
	char	*itoa_str;
}	t_pmoves;

typedef struct s_time
{
	time_t	start_time;
	time_t	end_time;
	time_t	game_time;
	int		min;
	int		sec;
}	t_time;

typedef struct s_duck
{
	void	*duck_img;
	void	*pick_duck_f[5];
	void	*pick_duck_b[5];
	void	*pick_duck_r[5];
	void	*pick_duck_l[5];
	void	*pick_duck[16];
}	t_duck;

typedef struct s_agu
{
	void	*agu_img[2];
	void	*open[25];
	int		agu;
	int		x;
	int		y;
}	t_agu;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
	int		player;
	int		collectible;
	int		exit;
	int		bh;
	int		agu;
}	t_map;

typedef struct s_wall
{
	void	*floor_wall_img[5];
	int		count_a;
	int		count_b;
}	t_wall;

typedef struct s_exit
{
	int		x;
	int		y;
	int		toggle;
	void	*closed[8];
	void	*leave[16];
	void	*opened[8];
	void	*open[39];
}	t_exit;

typedef struct s_bh
{
	int		x;
	int		y;
	void	*bh_img[2];
	void	*put_agu[19];
	void	*vanish[23];
	void	*swallow_player[28];
	void	*swallow_duck[30];
	void	*spin_wall[26];
	void	*spin_agu[10];
	void	*bh_astro_anime[56];
	int		agu_toggle;
	int		toggle;
	int		wall_toggle;
	int		spin;
	int		agu;
	int		stop;
	char	c;
	int		code;
}	t_bh;

typedef struct s_player
{
	int		x;
	int		y;
	int		ducks;
	int		stop;
	int		agu;
	void	*astronaut[4];
	void	*astro_trans[40];
	void	*astro_anime[26];
	int		astro_toggle;
	int		bh_astro_toggle;
	void	*player_img[5];
	size_t	moves;
}	t_player;

typedef struct s_end
{
	void	*lose[9];
	void	*win[12];
	void	*number[11];
}	t_end;

typedef struct s_game
{
	void		*mlx_c;
	void		*mlx_w;
	int			img_width;
	int			img_height;
	int			bool_start;
	void		*start[2];
	t_time		time;
	t_duck		duck;
	t_agu		agu;
	t_map		map;
	t_wall		wall;
	t_exit		exit;
	t_player	player;
	t_bh		bh;
	t_end		end;
	t_pmoves	move;
}	t_game;

/*	Function Prototypes */
void	ft_astro_transf(t_game *game);
void	ft_check_ducks_gathering(char **map, t_game *game, int ducks, char c);
void	ft_check_map_errors(t_game *game);
void	ft_check_map_playability(t_game *game);
void	ft_check_map(t_game *game);
void	ft_check_mapfile(char *str);
void	ft_check_win_and_vanish_bh(t_game *game, int new_x, int new_y);
void	ft_check_window_creation(void *mlx_w, void *mlx_c);
int		ft_close_window(t_game *game);
int		ft_count_file_lines(int fd);
void	ft_count_walls(t_game *game);
void	ft_create_game_images(t_game *game);
void	ft_create_images(t_game *game);
void	ft_del_prev_msg(t_game *game, int start, int end);
void	ft_destroy_image(void *mlx_c, void **images, int size);
void	ft_destroy_map(t_game *game);
void	ft_display_animation_frame(t_game *game, void *image, int x, int y);
void	ft_display_final_animation(t_game *game, char *moves,
			char *game_time_str);
void	ft_display_lose_animation(t_game *game);
int		ft_find_code(char c);
char	*ft_get_next_line(int fd);
void	ft_get_position(t_game *game, char c);
void	ft_handle_agu(t_game *game, int new_x, int new_y);
void	ft_handle_astro_transf(t_game *game, int new_x, int new_y);
void	ft_handle_bh_conditions(t_game *game, int new_x, int new_y);
void	ft_handle_error(char *str, t_game *game, int error);
void	ft_handle_exit(t_game *game);
int		ft_handle_keypress(int keycode, t_game *game);
int		ft_handle_keyrelease(int keycode, t_game *game);
void	ft_handle_map(char *str, t_game *game);
void	ft_handle_player_move(t_game *game, int new_x, int new_y);
int		ft_handle_rules_keypress(int keycode, t_game *game);
void	ft_handle_swallow_duck(t_game *game, int new_x, int new_y);
void	ft_handle_swallow_player(t_game *game, int new_x, int new_y);
void	ft_handle_walls(t_game *game, int new_x, int new_y);
void	ft_initialize_mlx(t_game *game);
void	ft_initialize_vars(t_game *game);
char	*ft_itoa(int n);
void	ft_leave_and_win(t_game *game);
void	ft_leave_game(t_game *game);
void	*ft_load_image(t_game *game, char *file_path, int *width, int *height);
void	ft_move_bh(t_game *game, int new_x, int new_y);
void	ft_move_player(t_game *game, int new_x, int new_y);
void	ft_open_agu(t_game *game);
void	ft_pickup_duck(t_game *game, int x, int y);
char	*ft_print_bh_move(t_game *game, int new_x, int new_y);
void	ft_print_count_moves(t_game *game);
void	ft_print_nb_wall_a(t_game *game);
void	ft_print_nb_wall_b(t_game *game);
char	*ft_print_player_move(t_game *game, int new_x, int new_y);
void	ft_put_agu(t_game *game);
void	ft_put_astro_anime(t_game *game);
void	ft_put_bh_images(t_game *game);
void	ft_put_exit_images(t_game *game);
void	ft_put_images(t_game *game);
int		ft_put_start(t_game *game);
char	*ft_read_path(int fd);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *str);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *str);
char	*ft_strrchr(const char *str, int c);
void	ft_swallow_duck(t_game *game, int x, int y, int code);
void	ft_swallow_player(t_game *game);
void	ft_undress_astro(t_game *game);
void	ft_undress_astronaut(t_game *game);
void	ft_update_bh_on_floor(t_game *game, int new_x, int new_y);
void	ft_update_bh_spin(t_game *game);
int		ft_update(t_game *game);
void	ft_vanish_bh(t_game *game);

#endif

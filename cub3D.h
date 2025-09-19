/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:27:22 by nico              #+#    #+#             */
/*   Updated: 2025/09/17 23:13:36 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define RESET "\033[0m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# define PASS 0
# define FAIL 1

# define WIN_WIDTH 1024
# define WIN_HEIGHT 640

# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define ESC_KEY 65307
# define LEFT_KEY 65361
# define RIGHT_KEY 65363

# define MOVE_SPEED 0.015
# define ROT_SPEED 0.02

# define PI 3.1415926535

# define BG_CEILING 0x00FFFF
# define BG_FLOOR 0x0000FF

/******************************************************************************/
/*                                 STRUCTS                                    */
/******************************************************************************/

enum				e_dir
{
	UP = 1,
	DOWN = 2,
	LEFT = 3,
	RIGHT = 4,
	ROT_L = 5,
	ROT_R = 6,
};

typedef struct s_fill
{
	int				x;
	int				y;
}					t_fill;

typedef struct s_keys
{
	int				up;
	int				down;
	int				left;
	int				right;
	int				l_arw;
	int				r_arw;
}					t_keys;

typedef struct s_int
{
	int				x;
	int				y;
}					t_int;

typedef struct s_dbl
{
	double			x;
	double			y;
}					t_dbl;

typedef struct s_img
{
	void			*img;
	int				*addr;
	int				bpp;
	int				line;
	int				endian;
}					t_img;

typedef struct s_text
{
	// Texture file paths
	char			*txt_n;  // North texture
	char			*txt_s;  // South texture
	char			*txt_w;  // West texture
	char			*txt_e;  // East texture
	unsigned long	*rgb_g;
	unsigned long	*rgb_c;
	int				size;
	int				indx;
	double			step;
	double			pos;
	t_int			ref;
}					t_text;

typedef struct s_map
{
	char			**og_map;
	char			**fl_map;
	//int				max_x;
	//int				max_y;
	//int				player_x;
	//int				player_y;
	//char			player_dir;
	//int				line;
	int				high;   // Map height
	int				wide;   // Map width
	int				eom;    // End of map flag
	int				start_index;  // Index where map data begins (after parameters)
}					t_map;

typedef struct s_track
{
	double			cam_x;
	double			wall;
	double			walx;
	int				side;
	int				high;
	int				strt;
	int				end;
	t_int			map;
	t_int			stp;
	t_dbl			dir;
	t_dbl			sid;
	t_dbl			dlt;
}					t_track;

// typedef struct s_track
// {
// 	double			pos_x;
// 	double			pos_y;
// 	double			dir_x;
// 	double			dir_y;
// 	double			plane_x;
// 	double			plane_y;
// 	double			ray_dir_x;
// 	double			ray_dir_y;
// 	double			side_dist_x;
// 	double			side_dist_y;
// 	double			delta_dist_x;
// 	double			delta_dist_y;
// 	double			perp_wall_dist;
// 	int				map_x;
// 	int				map_y;
// 	int				step_x;
// 	int				step_y;
// 	int				hit;
// 	int				side;
// 	int				line_height;
// 	int				draw_start;
// 	int				draw_end;
// 	int				tex_x;
// 	int				tex_y;
// 	double			wall_x;
// 	double			step;
// 	double			tex_pos;
	
// 	// Nested structures used by raycast engine
// 	t_dbl			dir;		// For t.dir.x, t.dir.y access
// 	t_int			map;		// For t.map.x, t.map.y access  
// 	t_dbl			dlt;		// For t.dlt.x, t.dlt.y access (delta distances)
// 	t_dbl			sid;		// For t.sid.x, t.sid.y access (side distances)
// 	t_int			stp;		// For t.stp.x, t.stp.y access (step directions)
// 	t_dbl			pln;		// For t.pln.x, t.pln.y access (plane vectors)
	
// 	// Additional members used by raycast engine
// 	double			cam_x;		// Camera X position
// 	int				high;		// Line height
// 	int				strt;		// Start position
// 	int				end;		// End position
// 	double			walx;		// Wall X coordinate
// }					t_track;

typedef struct s_play
{
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			move_speed;
	double			rot_speed;
	char			s_dir;  // Player direction character
	t_dbl			pos;    // Player position (use .pos.x, .pos.y)
	int				check;
	int				rot;
}					t_play;

typedef struct s_data
{
	int				mapx;
	int				mapy;
	int				**pxl;
	int				**txt;
	t_text			text;
	t_map			map;
	t_img			mini;
	t_keys			key;
	t_play			play;
	t_track			track;
	void			*wind;
	void			*mlx;
	// Parsing state for function constraint compliance
	int				curr_line_index;
	int				param_count;
	int				map_start_index;
}					t_data;

typedef struct s_map_dims
{
    int max_x;
    int max_y;
}               t_map_dims;

typedef struct s_mini
{
	char			**og_mini;
	t_img			*mini_m;
	int				size;
	int				off_x;
	int				off_y;
	int				dist;
	int				tile;
}					t_mini;

/******************************************************************************/
/*                              INITIATE_DATA                                 */
/******************************************************************************/

void				ft_key_init(t_keys *key);
void				ft_img_init(t_img *img);
void				ft_play_init(t_play *play);
void				ft_text_init(t_text *text);
void				ft_map_init(t_map *map);

void				ft_mini_init(t_img *mini);
void				ft_track_init(t_track *track);
void				ft_data_init(t_data *data);

/******************************************************************************/
/*                             DATA_VALIDATION                                */
/******************************************************************************/

// Game initialization and texture loading functions
char	*ft_direction_id(t_data *d, int dir);
int		*ft_fill_texture(t_data *d, t_img *pic, int size);
void	ft_img_start(t_data *d, t_img *p, char *path, int size);
void	ft_direction_text(t_data *d, int dir, int size);
void	ft_game_start(t_data *d);

// Data validation functions
int ft_data_validation(t_data *data, int argc, char **argv);
int ft_validate_arguments(int argc, char **argv);
int ft_extension_check(char *file);
int ft_load_and_validate_file(t_data *data, char *filepath);
int ft_validate_map_structure(t_data *data);

int ft_process_param_line(t_data *data, char *line);
int ft_is_rgb_within_range(int r, int g, int b);
unsigned long ft_convert_rgb_to_int(int r, int g, int b);

// File reading and initial map storage (ft_file_reader.c)
char **ft_read_lines_into_array(int fd);
int ft_check_for_empty_file(char **map_array, char *path);
char **ft_get_raw_map_data(char *path);

// Parameter parsing and validation (ft_param_parser.c)
int ft_process_param_line(t_data *data, char *line);

// Texture utilities (ft_texture_utils.c)
int ft_is_valid_param(char *line);
int ft_check_duplicate_param(t_data *data, char *type_id);
int ft_parse_texture_path(t_data *data, char *line, char *type_id);

// RGB utilities (ft_rgb_utils.c)
int ft_is_rgb_within_range(int r, int g, int b);
unsigned long ft_convert_rgb_to_int(int r, int g, int b);
int ft_parse_color_values(t_data *data, char *line, char *type_id);

// Map structure validation (ft_map_validation.c)
int ft_check_map_config(t_data *data);
int ft_identify_map_properties(t_data *data, int start_index);
int ft_parse_file_structure(t_data *data, int *map_start_index);

// Map content parsing (ft_map_parser.c)
int ft_parse_map_content(t_data *data, int line_index, int start_index);
int ft_process_file_line(t_data *data, char *trimmed_line);

// Map processing for flood-fill (ft_map_prep.c)
int ft_prepare_map_for_flood_fill(t_data *data);
void ft_set_initial_player_view(t_data *data);

// Map content validation (ft_prepare_to_fill.c)
//int ft_find_map_dimensions(t_data *data);
int convert_to_flood_map(t_data *data);

// Map enclosure validation (ft_map_enclosure.c)
int ft_validate_map_enclosure(t_data *data);
char **ft_create_temp_flood_map(t_data *data);
void ft_perform_flood_fill(char **map, int x, int y, t_map_dims dims);
int ft_check_enclosed_borders(char **map, t_map_dims dims);

// Image utilities (ft_utils.c)
void ft_img_init(t_img *img);

// String utilities (ft_string_utils.c)
char *ft_whitetrim(char *str);
char *ft_strip_line_endings(char *str);
char *ft_strndup(const char *str, size_t n);
int ft_is_num(char *str);

// Validation utilities (ft_validation_utils.c)
int ft_is_empty_line(char *line);
int ft_is_valid_map_char(char c);
int ft_error_msg(char *cmd, char *msg, char *dtl, int err_code);
void ft_safe_array(void ***array);

// Memory cleanup functions
void ft_safe_ptr(void *str);
void ft_free_int_arr(int ***mat_ptr, int rows);
void ft_free_text(t_text *t);
void ft_free_img(t_img *i);
void ft_free_map(t_map *m);
void ft_free_mini(t_mini *m);
void ft_free_all(t_data *data);

// Additional initialization functions
void ft_data_init(t_data *data);

/******************************************************************************/
/*                              PLAYER_ACTION                                 */
/******************************************************************************/

int					ft_terminate_game(t_data *d);
int					ft_key_press(int keycode, t_data *d);
int					ft_key_release(int keycode, t_data *d);

int					ft_position_check(t_data *d, double mve_x, double mve_y);
int					ft_move_check(t_data *d, double mve_x, double mve_y);
int					ft_move_player(t_data *d, int key);
int					ft_rotdir(int key);
int					ft_rotate_player(t_data *d, int key);
void				ft_player_action(t_data *d);

/******************************************************************************/
/*                             RAYCAST_ENGINE                                 */
/******************************************************************************/

int					ft_dda_prep(t_track *t, t_play *p);
int					ft_ray_check(t_data *d, t_track *t);
void				ft_line_len(t_data *d, t_track *t, t_play *p);
void				ft_dda_algo(t_data *d, t_track *t, t_play *p);

void				ft_update_pxl(t_data *d, t_text *x, t_track *t, int a);
void				*ft_pxl_init(size_t count, size_t size);
void				ft_pxl_fill(t_data *d);
void				ft_display_wind(t_data *d, t_img *p, int x, int y);
void				ft_display(t_data *d);

int					ft_direction_check(t_track *t);
void				ft_compute_refx(t_track *t, t_text *x);
void				ft_step_calculate(t_text *x, t_track *t, t_data *d);
void				ft_ray_cast(t_play *p, t_data *d);
void				ft_raycasting(t_data *data);

/******************************************************************************/
/*                              EXIT_&_ERROR                                  */
/******************************************************************************/

void				ft_free_text(t_text *t);
void				ft_free_img(t_img *i);
void				ft_free_map(t_map *m);
void				ft_free_mini(t_mini *m);

void				ft_safe_ptr(void *str);
void				ft_safe_array(void ***array);
void				ft_free_int_arr(int ***mat_ptr, int rows);
void				ft_free_data(t_data *d);
void				ft_freedom(t_data *d);

// Messaging and error handling functions
char				*ft_dup_or_join(char *s1, char *s2);
char				*ft_add_quotes(char *final, char *cmd, char *dtl);
void				ft_correct_form(int err_code, char *dtl);

/******************************************************************************/
/*                                  GNL                                       */
/******************************************************************************/

char				*get_next_line(int fd);
char				*ft_read_to_temp(char *temporary, int fd);
char				*ft_join_to_temp(char *temporary, char *read_result);
int					ft_str_len(char *str);
int					ft_new_line(char *read_result);
char				*ft_mem_alloc_fill(int nb, int size);
char				*ft_temp_to_extract(char *temporary);
char				*ft_clear_for_next(char *temporary);

/******************************************************************************/
/*                                 UTILS                                      */
/******************************************************************************/

int					ft_raycast_check(t_data *d);
void				ft_print_welcome(void);
void				ft_print_exit(void);

#endif
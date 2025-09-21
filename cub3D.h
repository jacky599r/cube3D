/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:27:22 by nico              #+#    #+#             */
/*   Updated: 2025/09/22 06:17:19 by nico             ###   ########.fr       */
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
# include <sys/time.h>
# include <time.h>
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
# define E_KEY 101
# define ESC_KEY 65307
# define LEFT_KEY 65361
# define RIGHT_KEY 65363

# define MOVE_SPEED 0.015
# define ROT_SPEED 0.02
# define PLAYER_RADIUS 0.2
# define DOOR_COLOR 0x8A5525
# define DOOR_IDX 4
# define COIN_FRAME_COUNT 8
# define MOUSE_DEAD_ZONE_WIDTH 100
# define COIN_SPRITE_SCALE 0.45
# define COIN_ANIM_SPEED 3.0
# define COIN_TEXTURE_SIZE 0
# define MM_PLAYER_COLOR 0xFF4444
# define MM_VIEW_COLOR 0xFFAA33
# define MM_BASE_TILE 12
# define MM_MIN_TILE 4
# define MM_DIV_X 3
# define MM_DIV_Y 3
# define MM_OFF_X 20
# define MM_OFF_Y_MARGIN 80
# define MM_OFF_Y_MIN 20

# define PI 3.1415926535

# define BG_CEILING 0x00FFFF
# define BG_FLOOR 0x0000FF

/******************************************************************************/
/*                                 STRUCTS                                    */
/******************************************************************************/

enum					e_dir
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
	int					x;
	int					y;
}						t_fill;

typedef struct s_keys
{
	int					up;
	int					down;
	int					left;
	int					right;
	int					l_arw;
	int					r_arw;
	int					use;
}						t_keys;

typedef struct s_door
{
	int					x;
	int					y;
	int					is_open;
}						t_door;

typedef struct s_int
{
	int					x;
	int					y;
}						t_int;

typedef struct s_dbl
{
	double				x;
	double				y;
}						t_dbl;

typedef struct s_img
{
	void				*img;
	int					*addr;
	int					bpp;
	int					line;
	int					endian;
}						t_img;

typedef struct s_coin_frame
{
	int					width;
	int					height;
	int					*pixels;
}						t_coin_frame;

typedef struct s_coin
{
	double				world_x;
	double				world_y;
	int					grid_x;
	int					grid_y;
	bool				alive;
}						t_coin;

typedef struct s_coin_anim
{
	int					frame_a;
	int					frame_b;
	double				alpha;
}						t_coin_anim;

typedef struct s_coin_spr
{
	double				tx;
	double				ty;
	int					screen_x;
	int					w;
	int					h;
	int					sx;
	int					ex;
	int					sy;
	int					ey;
	int					left_x;
	int					base_y;
	double				inv_w;
	double				inv_h;
	int					stride;
}						t_coin_spr;

typedef struct s_coin_tex
{
	const t_coin_frame	*a;
	const t_coin_frame	*b;
	int					tw;
	int					th;
	double				alpha;
}						t_coin_tex;

typedef struct s_coin_batch
{
	int					*order;
	int					alive;
}						t_coin_batch;

typedef struct s_mouse
{
	int					x;
	int					y;
	int					dir;
	double				scale;
	bool				inside;
}						t_mouse;

typedef struct s_text
{
	char				*txt_n;
	char				*txt_s;
	char				*txt_w;
	char				*txt_e;
	char				*txt_d;
	unsigned long		*rgb_g;
	unsigned long		*rgb_c;
	int					size;
	int					indx;
	double				step;
	double				pos;
	t_int				ref;
}						t_text;

typedef struct s_map
{
	char				**og_map;
	char				**fl_map;
	int					high;
	int					wide;
	int					eom;
	int					start_index;
}						t_map;

typedef struct s_track
{
	double				cam_x;
	double				wall;
	double				walx;
	char				tile;
	int					side;
	int					high;
	int					strt;
	int					end;
	t_int				map;
	t_int				stp;
	t_dbl				dir;
	t_dbl				sid;
	t_dbl				dlt;
}						t_track;

typedef struct s_play
{
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				move_speed;
	double				rot_speed;
	char				s_dir;
	t_dbl				pos;
	int					check;
	int					rot;
}						t_play;

typedef struct s_data
{
	int					mapx;
	int					mapy;
	int					**pxl;
	int					**txt;
	t_text				text;
	t_map				map;
	t_img				mini;
	t_door				*doors;
	int					door_count;
	int					door_cap;
	t_coin				*coins;
	int					coin_count;
	int					coin_capacity;
	int					coin_alive;
	t_coin_frame		coin_frames[COIN_FRAME_COUNT];
	t_coin_anim			coin_anim;
	double				*zbuffer;
	int					mini_tile;
	int					mini_width;
	int					mini_height;
	int					mini_off_x;
	int					mini_off_y;
	t_keys				key;
	t_play				play;
	t_mouse				mouse;
	t_track				track;
	void				*wind;
	void				*mlx;
	int					curr_line_index;
	int					param_count;
	int					map_start_index;
}						t_data;

typedef struct s_map_dims
{
	int					max_x;
	int					max_y;
}						t_map_dims;

typedef struct s_mini
{
	char				**og_mini;
	t_img				*mini_m;
	int					size;
	int					off_x;
	int					off_y;
	int					dist;
	int					tile;
}						t_mini;

/******************************************************************************/
/*                              INITIATE_DATA                                 */
/******************************************************************************/

void					ft_key_init(t_keys *key);
void					ft_img_init(t_img *img);
void					ft_play_init(t_play *play);
void					ft_text_init(t_text *text);
void					ft_map_init(t_map *map);

void					ft_init_coin_frames(t_data *d);
void					ft_init_world_entities(t_data *d);
void					ft_mini_init(t_data *data);
void					ft_track_init(t_track *track);
void					ft_init_window_and_buffers(t_data *d);

void					ft_key_init(t_keys *key);
void					ft_data_init(t_data *data);
void					ft_init_modules(t_data *d);

/******************************************************************************/
/*                             DATA_VALIDATION                                */
/******************************************************************************/

// Game initialization and texture loading functions
char					*ft_direction_id(t_data *d, int dir);
int						*ft_fill_texture(t_data *d, t_img *pic, int size);
void					ft_img_start(t_data *d, t_img *p, char *path, int size);
void					ft_direction_text(t_data *d, int dir, int size);
void					ft_game_start(t_data *d);

void					ft_mm_fill_row(t_data *d, int y, int sx, int ex);
void					ft_mm_fill_square(t_data *d, int cx, int cy,
							int spread);
void					ft_draw_tile(t_data *data, int map_x, int map_y,
							int color);
void					ft_draw_label(t_data *data, int y, int fg, char *msg);
int						ft_minimap_stride(t_img *img);

int						ft_mm_coin_spread(const t_data *d);
void					ft_mm_coin_center(const t_data *d, const t_coin *c,
							int *cx, int *cy);
void					ft_draw_coin_marker(t_data *d, t_coin *coin);
void					ft_draw_coin_markers(t_data *data);
void					ft_clear_minimap(t_data *data);

void					ft_minimap_setup(t_data *d);
void					ft_mm_set_offsets(t_data *d, int w, int h);
void					ft_mm_alloc_image(t_data *d, int w, int h);
int						ft_mm_choose_tile(const t_data *d);
int						ft_mm_setup_guard(const t_data *d);
int						ft_pick_color(char tile);

void					ft_minimap_setup(t_data *data);
void					ft_render_minimap(t_data *data);

// Data validation functions
int						ft_data_validation(t_data *data, int argc, char **argv);
int						ft_validate_arguments(int argc, char **argv);
int						ft_extension_check(char *file);
int						ft_load_and_validate_file(t_data *data, char *filepath);
int						ft_validate_map_structure(t_data *data);

int						ft_process_param_line(t_data *data, char *line);
int						ft_is_rgb_within_range(int r, int g, int b);
unsigned long			ft_convert_rgb_to_int(int r, int g, int b);

// File reading and initial map storage (ft_file_reader.c)
char					**ft_read_lines_into_array(int fd);
int						ft_check_for_empty_file(char **map_array, char *path);
char					**ft_get_raw_map_data(char *path);

// Parameter parsing and validation (ft_param_parser.c)
int						ft_process_param_line(t_data *data, char *line);

// Texture utilities (ft_texture_utils.c)
int						ft_is_valid_param(char *line);
int						ft_check_duplicate_param(t_data *data, char *type_id);
int						ft_parse_texture_path(t_data *data, char *line,
							char *type_id);

// RGB utilities (ft_rgb_utils.c)
int						ft_is_rgb_within_range(int r, int g, int b);
unsigned long			ft_convert_rgb_to_int(int r, int g, int b);
int						ft_parse_color_values(t_data *data, char *line,
							char *type_id, unsigned long colour);

// Map structure validation (ft_map_validation.c)
int						ft_check_map_config(t_data *data);
int						ft_identify_map_properties(t_data *data,
							int start_index);
int						ft_parse_file_structure(t_data *data,
							int *map_start_index);

// Map content parsing (ft_map_parser.c)
int						ft_process_player_info(t_data *data, char player_char,
							int x_pos, int y_idx);
int						ft_parse_map_content(t_data *data, int line_index,
							int start_index);
int						ft_process_file_line(t_data *data, char *trimmed_line);
void					ft_update_map_dims(t_data *data, char *line);
int						ft_scan_map_line(t_data *data, const char *line,
							int map_y);
int						ft_handle_tile(t_data *data, char c, int x, int y);

// Map processing for flood-fill (ft_map_prep.c)
int						ft_prepare_map_for_flood_fill(t_data *data);
void					ft_set_initial_player_view(t_data *data);

// Map content validation (ft_prepare_to_fill.c)
// int ft_find_map_dimensions(t_data *data);
int						convert_to_flood_map(t_data *data);

// Map enclosure validation (ft_map_enclosure.c)
int						ft_validate_map_enclosure(t_data *data);
char					**ft_create_temp_flood_map(t_data *data);
void					ft_perform_flood_fill(char **map, int x, int y,
							t_map_dims dims);
int						ft_check_enclosed_borders(char **map, t_map_dims dims);

// Image utilities (ft_utils.c)
void					ft_img_init(t_img *img);

// String utilities (ft_string_utils.c)
char					*ft_whitetrim(char *str);
char					*ft_strip_line_endings(char *str);
char					*ft_strndup(const char *str, size_t n);
int						ft_is_num(char *str);

// Validation utilities (ft_validation_utils.c)
int						ft_is_empty_line(char *line);
int						ft_is_valid_map_char(char c);
int						ft_error_msg(char *cmd, char *msg, int err_code);
void					ft_safe_array(void ***array);

// Memory cleanup functions
void					ft_safe_ptr(void *str);
void					ft_free_int_arr(int ***mat_ptr, int rows);
void					ft_free_text(t_text *t);
void					ft_free_img(t_img *i);
void					ft_free_map(t_map *m);
void					ft_free_mini(t_mini *m);
void					ft_free_doors(t_data *data);
void					ft_free_all(t_data *data);

// Additional initialization functions
void					ft_data_init(t_data *data);
void					ft_free_coins(t_data *data);
int						ft_spawn_coins(t_data *data);
void					ft_load_coin_textures(t_data *data);
t_coin_anim				ft_coin_anim_state(void);
int						ft_coin_update_anim(t_data *data, t_coin_anim next);
int						ft_collect_coin(t_data *data);

/******************************************************************************/
/*                              PLAYER_ACTION                                 */
/******************************************************************************/
int						ft_raycast_check(t_data *d);
int						ft_terminate_game(t_data *d);
int						ft_key_press(int keycode, t_data *d);
int						ft_key_release(int keycode, t_data *d);

int						ft_position_check(t_data *d, double mve_x,
							double mve_y);
int						ft_move_check(t_data *d, double mve_x, double mve_y);
int						ft_move_player(t_data *d, int key, double mve_x,
							double mve_y);
int						ft_rotdir(int key);
int						ft_rotate_player_angle(t_data *d, double angle);
int						ft_rotate_player(t_data *d, int key);
void					ft_player_action(t_data *d);
int						ft_interact_door(t_data *data);
int						ft_register_door(t_data *data, int x, int y);
t_door					*ft_find_door(t_data *data, int x, int y);
int						ft_mouse_move(int x, int y, t_data *data);
int						ft_mouse_leave(t_data *data);
int						ft_rotate_player_mouse(t_data *data);

/******************************************************************************/
/*                             RAYCAST_ENGINE                                 */
/******************************************************************************/

/*DDA*/
int						ft_dda_prep(t_track *t, t_play *p);
int						ft_ray_check(t_data *d, t_track *t);
void					ft_line_len(t_data *d, t_track *t, t_play *p);
double					ft_delta_dist(double dir);
void					ft_dda_step(t_track *t);

void					ft_dda_algo(t_data *d, t_track *t, t_play *p);

void					ft_prepare_texture(t_data *d, t_text *x, t_track *t);
void					ft_clamp_scan(const t_data *d, const t_track *t, int *y,
							int *y_end);
int						ft_sample_color(const t_data *d, const t_text *x,
							const t_track *t, int ty);
void					ft_update_pxl(t_data *d, t_text *x, t_track *t, int a);

/*Raycaster*/
void					ft_die_alloc(t_data *d, const char *msg);
void					*ft_xinit(t_data *d, size_t count, size_t size);
void					ft_free_framebuffers(t_data *d);
void					ft_alloc_pxl_rows(t_data *d);
void					ft_alloc_zbuffer(t_data *d);

void					*ft_pxl_init(size_t count, size_t size);
void					ft_pxl_fill(t_data *d);
void					ft_display_wind(t_data *d, t_img *p, int x, int y);
void					ft_display(t_data *d);

int						ft_direction_check(t_track *t);
void					ft_compute_refx(t_track *t, t_text *x);
void					ft_step_calculate(t_text *x, t_track *t, t_data *d);
void					ft_ray_cast(t_play *p, t_data *d);
void					ft_raycasting(t_data *data);

/*coin_render*/

void					ft_render_coins(t_data *d, t_img *img);
void					ft_coins_draw(const t_data *d, t_img *img,
							t_coin_batch b, t_coin_anim anim);
t_coin_anim				ft_coins_anim(const t_data *d);
int						ft_coins_gather(const t_data *d, int *order,
							double *dist);
int						ft_coins_tmp_alloc(const t_data *d, int **order,
							double **dist);

int						ft_coin_sample(const t_coin_frame *frame, int x, int y);
int						ft_blend_colour(int base, int next, double alpha);
void					ft_sort_coins(int *order, double *dist, int count);
int						ft_coin_pick_frames(const t_data *d, t_coin_anim anim,
							t_coin_tex *t);
int						ft_coin_transform(const t_data *d, const t_coin *c,
							t_coin_spr *s);

void					ft_coin_bounds(const t_data *d, t_img *img,
							t_coin_spr *s);
void					ft_coin_draw_column(t_img *img, const t_coin_spr *s,
							const t_coin_tex *t, int stripe);
void					ft_coin_render(t_data *d, t_img *img,
							const t_coin_spr *s, const t_coin_tex *t);
void					ft_draw_coin(t_data *d, t_img *img, t_coin *coin,
							t_coin_anim anim);

/******************************************************************************/
/*                              EXIT_&_ERROR                                  */
/******************************************************************************/

void					ft_free_text(t_text *t);
void					ft_free_img(t_img *i);
void					ft_free_map(t_map *m);
void					ft_free_mini(t_mini *m);

void					ft_safe_ptr(void *str);
void					ft_safe_array(void ***array);
void					ft_free_int_arr(int ***mat_ptr, int rows);
void					ft_free_data(t_data *d);
void					ft_freedom(t_data *d);
char					*ft_dup_or_join(char *s1, char *s2);
char					*ft_add_quotes(char *final, char *dtl);
void					ft_correct_form(int err_code);

/******************************************************************************/
/*                                  GNL                                       */
/******************************************************************************/

char					*get_next_line(int fd);
char					*ft_read_to_temp(char *temporary, int fd);
char					*ft_join_to_temp(char *temporary, char *read_result);
int						ft_str_len(char *str);
int						ft_new_line(char *read_result);
char					*ft_mem_alloc_fill(int nb, int size);
char					*ft_temp_to_extract(char *temporary);
char					*ft_clear_for_next(char *temporary);

/******************************************************************************/
/*                                 UTILS                                      */
/******************************************************************************/

int						ft_raycast_check(t_data *d);
void					ft_print_welcome(void);
void					ft_print_exit(void);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:27:22 by nico              #+#    #+#             */
/*   Updated: 2025/08/12 17:57:30 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include "mlx.h"

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

#define WIN_WIDTH 1024
#define WIN_HEIGHT 512

#define W_KEY 119
#define A_KEY 97
#define S_KEY 115
#define D_KEY 100
#define ESC_KEY 65307
#define LEFT_KEY 65361
#define RIGHT_KEY 65363

#define move_speed 0.1
#define rot_speed 0.2

#define PI 3.1415926535

#define BG_CEILING 0x00FFFF
#define BG_FLOOR   0x0000FF

/******************************************************************************/
/*                                 STRUCTS                                    */
/******************************************************************************/

typedef struct s_fill
{
	int		x;
	int		y;
}			t_fill;

// typedef struct s_keys
// {
//     int up;
//     int down;
//     int left;
//     int right;
// 	int	l_arw;
// 	int r_arw;
// } 			t_keys;


typedef struct s_int
{
	int		x;
	int		y;
}			t_int;

typedef struct s_dbl
{
	double	x;
	double	y;
}			t_dbl;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bpp;
	int		line;
	int		endian;
}				t_img;

typedef struct s_text
{
	char			*txt_n;
	char			*txt_s;
	char			*txt_w;
	char			*txt_e;
	int				*txt_g;
	int				*txt_c;
	unsigned long	*rgb_g;
	unsigned long	*rgb_c;
	int				size;
	int				indx;
	double			step;
	double			pos;
	t_int			ref;
}				t_text;

typedef struct s_mini
{
	char 	**og_mini;
	t_img	*mini_m;
	int		size;
	int		off_x;
	int		off_y;
	int		dist;
	int		tile;
}			t_mini;

typedef struct s_map
{
	int		fd;
	int		max;
	int		high;
	int		wide;
	char	*m_ref;
	char 	**og_map;
	int		eom;
}				t_map;

typedef struct s_track
{
	double		cam_x;
	double		wall;
	double		walx;
	int			side;
	int			high;
	int			strt;
	int			end;
	t_int		map;
	t_int		stp;
	t_dbl		dir;
	t_dbl		sid;
	t_dbl		dlt;
}			t_track;

typedef struct s_play
{
	char	s_dir;
	t_int	mve;
	t_dbl	pos;
	t_dbl	dir;
	t_dbl	pln;
	int		check;
	int		rot;
}			t_play;

typedef	struct s_data
{
	int 	mapx;
	int		mapy;
	int		**pxl;
	int		**txt;
	t_text	text;
	t_map	map;
	t_img	mini;
	char	**og_map;
	char	**fl_map;
	t_play	play;
	t_track	track;
	void	*wind;
	void	*mlx;
}			t_data;

typedef struct s_play
{
	char	s_dir;
	t_int	mve;
	t_dbl	pos;
	t_dbl	dir;
	t_dbl	pln;
	int		check;
	int		rot;
}			t_play;

// typedef struct s_data
// {
//     t_maps	m_data;
// 	t_img	m_mini;
// 	t_img	m_fog;
// 	t_img	frame;
// 	t_ent	player;
// 	t_keys	key;
// 	int		mapY;
// 	int		mapX;
// 	int		mapS;
// 	void		*wind;
// 	void	*mlx;
// }               t_data;

typedef struct s_map_dims
{
    int max_x;
    int max_y;
}               t_map_dims;

/******************************************************************************/
/*                              INITIATE_DATA                                 */
/******************************************************************************/



/******************************************************************************/
/*                             DATA_VALIDATION                                */
/******************************************************************************/

int ft_is_num(char *str);
int ft_process_param_line(t_data *data, char *line);
int ft_is_rgb_within_range(int r, int g, int b);
unsigned long ft_convert_rgb_to_int(int r, int g, int b);
int ft_validate_rgb(char *rgb_string, int r, int g, int b, char *line);
int ft_read_map(t_data *data, char *path);
int ft_parse_map_data(t_data *data);

// File reading and initial map storage (ft_file_reader.c)
int ft_open_map_file(char *path);
char **ft_read_lines_into_array(int fd);
char **ft_add_line_to_array(char **current_map, char *new_line, int current_size);
int ft_check_for_empty_file(char **map_array, char *path);
char **ft_get_raw_map_data(char *path);

// Parameter parsing and validation (ft_param_parser.c)
static int ft_is_valid_param_identifier(char *line);
static int ft_check_duplicate_param(t_data *data, char *type_id);
int ft_parse_texture_path(t_data *data, char *line, char *type_id);
static int ft_validate_rgb_and_convert(char *rgb_str, int *r, int *g, int *b);
int ft_parse_color_values(t_data *data, char *line, char *type_id);

// Map structure validation (ft_map_validator.c)
int ft_check_map_config(t_data *data);
static int ft_validate_map_characters(char *line);
static int ft_process_player_info(t_data *data, char player_char, int x, int y, int *player_count);
int ft_identify_map_properties(t_data *data, int start_index);
static int ft_is_map_line(char *line);

// Map processing for flood fill & player init (ft_map_processor.c)
int ft_prepare_map_for_flood_fill(t_data *data);
void ft_set_initial_player_view(t_data *data);

// Map enclosure validation (ft_map_enclosure.c)
char **ft_create_temp_flood_map(t_data *data);
void ft_perform_flood_fill(char **map, int x, int y, t_map_dims dims);
int ft_check_enclosed_borders(char **map, t_map_dims dims);
int ft_validate_map_enclosure(t_data *data);

// General Utility Functions (ft_utils.c)
int ft_is_empty_line(char *line);
int ft_error_msg(char *err_type, char *msg, char *context, int ret_code);
void ft_safe_array(void ***arr);
static int ft_is_num(char *str);

/******************************************************************************/
/*                              PLAYER_ACTION                                 */
/******************************************************************************/




/******************************************************************************/
/*                             RAYCAST_ENGINE                                 */
/******************************************************************************/




/******************************************************************************/
/*                              EXIT_&_ERROR                                  */
/******************************************************************************/



/******************************************************************************/
/*                                  GNL                                       */
/******************************************************************************/

char	*get_next_line(int fd);
char	*ft_read_to_temp(char *temporary, int fd);
char	*ft_join_to_temp(char *temporary, char *read_result);
int		ft_str_len(char *str);
int		ft_new_line(char *read_result);
char	*ft_mem_alloc_fill(int nb, int size);
char	*ft_temp_to_extract(char *temporary);
char	*ft_clear_for_next(char *temporary);

/******************************************************************************/
/*                                 UTILS                                      */
/******************************************************************************/



#endif
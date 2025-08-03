/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:27:22 by nico              #+#    #+#             */
/*   Updated: 2025/07/23 21:17:34 by nico             ###   ########.fr       */
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

/******************************************************************************/
/*                              INITIATE_DATA                                 */
/******************************************************************************/



/******************************************************************************/
/*                             DATA_VALIDATION                                */
/******************************************************************************/




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
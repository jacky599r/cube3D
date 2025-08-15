/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:47:21 by nico              #+#    #+#             */
/*   Updated: 2025/08/15 12:22:27 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_play_init(t_play *play)
{
	play->s_dir = '\0';
	play->check = 0;
	play->rot = 0;
	play->pos.x = 0.0;
	play->pos.y = 0.0;
	play->pos_x = 0.0;
	play->pos_y = 0.0;
	play->dir_x = 0.0;
	play->dir_y = 0.0;
	play->plane_x = 0.0;
	play->plane_y = 0.0;
	play->move_speed = MOVE_SPEED;
	play->rot_speed = ROT_SPEED;
}

void	ft_text_init(t_text *text)
{
	text->txt_n = NULL;
	text->txt_s = NULL;
	text->txt_w = NULL;
	text->txt_e = NULL;
	text->rgb_g = NULL;
	text->rgb_c = NULL;
	text->img = NULL;
	text->addr = NULL;
	text->bpp = 0;
	text->line = 0;
	text->endian = 0;
	text->width = 0;
	text->height = 0;
	text->size = 64;
	text->indx = 0;
	text->step = 0.0;
	text->pos = 0.0;
	text->ref.x = 0;
	text->ref.y = 0;
}

void	ft_map_init(t_map *map)
{
	map->high = 0;
	map->wide = 0;
	map->eom = 0;
	map->og_map = NULL;
	map->fl_map = NULL;
	map->max_x = 0;
	map->max_y = 0;
	map->player_x = 0;
	map->player_y = 0;
	map->player_dir = '\0';
	map->start_index = -1;  // Initialize to -1 (not set)
}

void    ft_mini_init(t_img *mini)
{
    mini->img = NULL;
    mini->addr = NULL;
    mini->line = 0;
    mini->bpp = 0;
    mini->endian = 0;    
}

void    ft_data_init(t_data *data)
{
    data->mapx = WIN_HEIGHT;
    data->mapy = WIN_WIDTH;
    data->pxl = NULL;
    data->txt = NULL;
    data->og_map = NULL;
    data->fl_map = NULL; // used for flood fill if necessary
    data->wind = NULL;
    data->mlx = NULL;
    ft_play_init(&data->play);
    ft_text_init(&data->text);
    ft_map_init(&data->map);
    ft_mini_init(&data->mini);
}

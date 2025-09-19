/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:16:11 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/19 15:01:52 by nsamarin         ###   ########.fr       */
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
	text->txt_d = NULL;
	text->rgb_g = NULL;
	text->rgb_c = NULL;
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
	map->start_index = -1;
}

void	ft_track_init(t_track *track)
{
	if (!track)
		return ;
	track->cam_x = 0.0;
	track->wall = 0.0;
	track->walx = 0.0;
	track->tile = '0';
	track->side = 0;
	track->high = 0;
	track->strt = 0;
	track->end = 0;
	track->map.x = 0;
	track->map.y = 0;
	track->stp.x = 0;
	track->stp.y = 0;
	track->dir.x = 0.0;
	track->dir.y = 0.0;
	track->sid.x = 0.0;
	track->sid.y = 0.0;
	track->dlt.x = 0.0;
	track->dlt.y = 0.0;
}

void	ft_mini_init(t_data *data)
{
	ft_img_init(&data->mini);
	data->mini_tile = 0;
	data->mini_width = 0;
	data->mini_height = 0;
	data->mini_off_x = 0;
	data->mini_off_y = 0;
}

void	ft_data_init(t_data *data)
{
	data->mapx = WIN_WIDTH;
	data->mapy = WIN_HEIGHT;
	data->pxl = NULL;
	data->txt = NULL;
	data->wind = NULL;
	data->mlx = NULL;
	data->doors = NULL;
	data->door_count = 0;
	data->door_cap = 0;
	data->fog = NULL;
	ft_play_init(&data->play);
	ft_text_init(&data->text);
	ft_map_init(&data->map);
	ft_key_init(&data->key);
	ft_track_init(&data->track);
	ft_mini_init(data);
	ft_key_init(&data->key);
}

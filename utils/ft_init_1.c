/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:16:11 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/22 05:35:57 by nico             ###   ########.fr       */
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

void	ft_init_modules(t_data *d)
{
	ft_play_init(&d->play);
	ft_text_init(&d->text);
	ft_map_init(&d->map);
	ft_key_init(&d->key);
	ft_track_init(&d->track);
	ft_mini_init(d);
}

void	ft_data_init(t_data *d)
{
	ft_init_window_and_buffers(d);
	ft_init_world_entities(d);
	ft_init_coin_frames(d);
	ft_init_modules(d);
}

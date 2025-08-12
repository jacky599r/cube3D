/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:47:21 by nico              #+#    #+#             */
/*   Updated: 2025/08/13 00:12:55 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    ft_img_init(t_img *img)
{
    img->img = NULL;
    img->addr = NULL;
    img->bpp = 0;
    img->line = 0;
    img->endian = 0;
}

void    ft_play_init(t_play *play)
{
    play->s_dir = '0';
    play->check = 0;
    play->rot = 0;
    play->mve.x = 0;
    play->mve.y = 0;
    play->pos.x = 0.0;
    play->pos.y = 0.0;
    play->dir.x = 0.0;
    play->dir.y = 0.0;
    play->pln.x = 0.0;
    play->pln.y = 0.0;
}

void    ft_text_init(t_text *text)
{
    text->txt_n = NULL;
    text->txt_s = NULL;
    text->txt_w = NULL;
    text->txt_e = NULL;
    text->txt_g = 0;
    text->txt_c = 0;
    text->rgb_g = 0x0;
    text->rgb_c = 0x0;
    text->size = 64;
    text->indx = 0;
    text->step = 0.0;
    text->pos = 0.0;
    text->ref.x = 0;
    text->ref.y = 0;
}

void    ft_map_init(t_map *map)
{
    map->fd = 0;
    map->max = 0;
    map->high = 0;
    map->wide = 0;
    map->eom = 0;
    map->m_ref = NULL;
    map->og_map = NULL;
}

void    ft_mini_init(t_img *mini)
{
    mini->img = NULL;
    mini->addr = NULL;
    mini->line = 0;
    mini->bpp = 0;
    mini->endian = 0;    
}

void ft_track_init(t_track *track)
{
    track->cam_x = 0.0;
    track->wall = 0.0;
    track->walx = 0.0;
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
    ft_track_init(&data->track);
}

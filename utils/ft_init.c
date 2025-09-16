/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:47:21 by nico              #+#    #+#             */
/*   Updated: 2025/09/16 16:38:16 by nsamarin         ###   ########.fr       */
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

void	ft_mini_init(t_img *mini)
{
	mini->img = NULL;
	mini->addr = NULL;
	mini->line = 0;
	mini->bpp = 0;
	mini->endian = 0;
}

void	ft_track_init(t_track *track)
{
	track->pos_x = 0.0;
	track->pos_y = 0.0;
	track->dir_x = 0.0;
	track->dir_y = 0.0;
	track->plane_x = 0.0;
	track->plane_y = 0.0;
	track->ray_dir_x = 0.0;
	track->ray_dir_y = 0.0;
	track->side_dist_x = 0.0;
	track->side_dist_y = 0.0;
	track->delta_dist_x = 0.0;
	track->delta_dist_y = 0.0;
	track->perp_wall_dist = 0.0;
	track->map_x = 0;
	track->map_y = 0;
	track->step_x = 0;
	track->step_y = 0;
	track->hit = 0;
	track->side = 0;
	track->line_height = 0;
	track->draw_start = 0;
	track->draw_end = 0;
	track->tex_x = 0;
	track->tex_y = 0;
	track->wall_x = 0.0;
	track->step = 0.0;
	track->tex_pos = 0.0;
	
	// Initialize nested structures
	track->dir.x = 0.0;
	track->dir.y = 0.0;
	track->map.x = 0;
	track->map.y = 0;
	track->dlt.x = 0.0;
	track->dlt.y = 0.0;
	track->sid.x = 0.0;
	track->sid.y = 0.0;
	track->stp.x = 0;
	track->stp.y = 0;
	track->pln.x = 0.0;
	track->pln.y = 0.0;
	track->cam_x = 0.0;
	track->high = 0;
	track->strt = 0;
	track->end = 0;
	track->walx = 0.0;
}

void	ft_data_init(t_data *data)
{
	data->mapx = WIN_HEIGHT;
	data->mapy = WIN_WIDTH;
	data->pxl = NULL;
	data->txt = NULL;
	// Map arrays are initialized in ft_map_init()
	data->wind = NULL;
	data->mlx = NULL;
	ft_play_init(&data->play);
	ft_text_init(&data->text);
	ft_map_init(&data->map);
	ft_mini_init(&data->mini);
	ft_track_init(&data->track);
}

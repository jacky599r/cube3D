/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:31:02 by nico              #+#    #+#             */
/*   Updated: 2025/08/14 19:31:44 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
}

void	ft_data_init(t_data *data)
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
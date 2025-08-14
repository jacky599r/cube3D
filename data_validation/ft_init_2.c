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
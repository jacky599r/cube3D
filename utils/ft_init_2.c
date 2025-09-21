/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 05:33:20 by nico              #+#    #+#             */
/*   Updated: 2025/09/22 06:18:56 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	ft_init_window_and_buffers(t_data *d)
{
	d->mapx = WIN_WIDTH;
	d->mapy = WIN_HEIGHT;
	d->mlx = NULL;
	d->wind = NULL;
	d->pxl = NULL;
	d->zbuffer = NULL;
	d->txt = NULL;
}

void	ft_init_world_entities(t_data *d)
{
	d->doors = NULL;
	d->door_count = 0;
	d->door_cap = 0;
	d->coins = NULL;
	d->coin_count = 0;
	d->coin_capacity = 0;
	d->coin_alive = 0;
	d->mouse.x = WIN_WIDTH / 2;
	d->mouse.y = WIN_HEIGHT / 2;
	d->mouse.dir = 0;
	d->mouse.scale = 0.0;
	d->mouse.inside = false;
}

void	ft_init_coin_frames(t_data *d)
{
	int	i;

	i = 0;
	while (i < COIN_FRAME_COUNT)
	{
		d->coin_frames[i].pixels = NULL;
		d->coin_frames[i].width = 0;
		d->coin_frames[i].height = 0;
		i++;
	}
	d->coin_anim.frame_a = -1;
	d->coin_anim.frame_b = -1;
	d->coin_anim.alpha = 0.0;
}

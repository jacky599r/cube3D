/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycaster_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:14:27 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/22 04:30:16 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_direction_check(t_track *t)
{
	int	dir;

	if (t->side == 0)
	{
		if (t->dir.x < 0)
			dir = 3;
		else
			dir = 2;
	}
	else
	{
		if (t->dir.y > 0)
			dir = 1;
		else
			dir = 0;
	}
	return (dir);
}

void	ft_compute_refx(t_track *t, t_text *x)
{
	int	tw;

	tw = x->size;
	x->ref.x = (int)(t->walx * tw);
	if ((t->side == 0 && t->dir.x < 0) || (t->side == 1 && t->dir.y > 0))
		x->ref.x = tw - x->ref.x - 1;
	if (x->ref.x < 0)
		x->ref.x = 0;
	if (x->ref.x >= tw)
		x->ref.x = tw - 1;
}

void	ft_step_calculate(t_text *x, t_track *t, t_data *d)
{
	x->step = (double)x->size / (double)t->high;
	x->pos = (t->strt - d->mapy / 2.0 + t->high / 2.0) * x->step;
}

void	ft_ray_cast(t_play *p, t_data *d)
{
	t_track	t;
	int		a;

	a = 0;
	t = d->track;
	while (a < d->mapx)
	{
		ft_track_init(&t);
		t.cam_x = (2.0 * a) / (double)d->mapx - 1.0;
		t.dir.x = p->dir_x + p->plane_x * t.cam_x;
		t.dir.y = p->dir_y + p->plane_y * t.cam_x;
		t.map.x = (int)p->pos.x;
		t.map.y = (int)p->pos.y;
		t.dlt.x = ft_delta_dist(t.dir.x);
		t.dlt.y = ft_delta_dist(t.dir.y);
		ft_dda_algo(d, &t, p);
		ft_update_pxl(d, &d->text, &t, a);
		if (d->zbuffer && a < d->mapx)
			d->zbuffer[a] = t.wall;
		a++;
	}
}

void	ft_raycasting(t_data *data)
{
	ft_pxl_fill(data);
	ft_track_init(&data->track);
	ft_ray_cast(&data->play, data);
	ft_display(data);
}

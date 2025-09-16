/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycaster_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:03:26 by nico              #+#    #+#             */
/*   Updated: 2025/09/16 16:33:57 by nsamarin         ###   ########.fr       */
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
	x->ref.x = (int)(t->walx * x->size);
	if ((t->side == 0 && t->dir.x < 0) || (t->side == 1 && t->dir.y > 0))
		x->ref.x = x->size - x->ref.x - 1;
	// valid range check in case
	if (x->ref.x < 0)
		x->ref.x = 0;
	if (x->ref.x >= x->size)
		x->ref.x = x->size - 1;
}

void	ft_step_calculate(t_text *x, t_track *t, t_data *d)
{
	x->step = 1.0 * x->size / t->high;
	x->pos = (t->strt - d->mapy / 2 + t->high / 2) * x->step;
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
		t.cam_x = 2 * a / 640 - 1;
		t.dir.x = p->dir_x + p->plane_x * t.cam_x;
		t.dir.y = p->dir_y + p->plane_y * t.cam_x;
		t.map.x = (int)p->pos.x;
		t.map.y = (int)p->pos.y;
		t.dlt.x = fabs(1 / t.dir.x);
		t.dlt.y = fabs(1 / t.dir.y);
		ft_dda_algo(d, &t, p);
		ft_update_pxl(d, &d->text, &t, a);
		a++;
	}
}

void	ft_raycasting(t_data *data)
{
	printf("ray1\n");
	ft_pxl_fill(data);
	printf("ray2\n");
	ft_track_init(&data->track);
	printf("ray3\n");
	ft_ray_cast(&data->play, data);
	printf("ray4\n");
	ft_display(data);
	printf("ray done\n");
}
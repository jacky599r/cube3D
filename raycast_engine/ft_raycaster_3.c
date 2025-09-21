/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycaster_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 04:28:15 by nico              #+#    #+#             */
/*   Updated: 2025/09/22 04:30:12 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_prepare_texture(t_data *d, t_text *x, t_track *t)
{
	x->indx = ft_direction_check(t);
	if (t->tile == 'D')
		x->indx = DOOR_IDX;
	ft_compute_refx(t, x);
	ft_step_calculate(x, t, d);
}

void	ft_clamp_scan(const t_data *d, const t_track *t, int *y, int *y_end)
{
	*y = t->strt;
	*y_end = t->end;
	if (*y < 0)
		*y = 0;
	if (*y_end >= d->mapy)
		*y_end = d->mapy - 1;
}

int	ft_sample_color(const t_data *d, const t_text *x, const t_track *t, int ty)
{
	int	color;

	if (t->tile == 'D')
	{
		color = d->txt[DOOR_IDX][x->size * ty + x->ref.x];
		if (t->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		return (color);
	}
	color = d->txt[x->indx][x->size * ty + x->ref.x];
	if (x->indx == 0 || x->indx == 3)
		color = (color >> 1) & 0x7F7F7F;
	return (color);
}

void	ft_update_pxl(t_data *d, t_text *x, t_track *t, int a)
{
	int	y;
	int	y_end;
	int	ty;
	int	color;

	ft_prepare_texture(d, x, t);
	ft_clamp_scan(d, t, &y, &y_end);
	while (y <= y_end)
	{
		ty = (int)x->pos & (x->size - 1);
		x->pos += x->step;
		color = ft_sample_color(d, x, t, ty);
		d->pxl[y][a] = color;
		y++;
	}
}

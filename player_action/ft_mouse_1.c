/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouse_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 06:56:49 by nico              #+#    #+#             */
/*   Updated: 2025/09/22 07:07:02 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_mouse_clamp_xy(t_data *d, int *x, int *y)
{
	if (*x < 0)
	{
		*x = 0;
	}
	if (*y < 0)
	{
		*y = 0;
	}
	if (*x > d->mapx)
	{
		*x = d->mapx;
	}
	if (*y > d->mapy)
	{
		*y = d->mapy;
	}
}

static void	ft_mouse_deadzone(const t_data *d, t_deadzone *z)
{
	int	half;

	z->center = d->mapx / 2;
	half = MOUSE_DEAD_ZONE_WIDTH / 2;
	if (half > z->center)
	{
		half = z->center;
	}
	z->left = z->center - half;
	z->right = z->center + half;
}

static void	ft_mouse_dir_and_offset(t_data *d, int x,
		const t_deadzone *z, double *offset)
{
	double	off;

	*offset = 0.0;
	d->mouse.dir = 0;
	if (x < z->left)
	{
		d->mouse.dir = -1;
		off = (double)(z->left - x);
		*offset = off;
	}
	else if (x > z->right)
	{
		d->mouse.dir = 1;
		off = (double)(x - z->right);
		*offset = off;
	}
}

static void	ft_mouse_apply_scale(t_data *d, const t_deadzone *z, double offset)
{
	double	scale;

	d->mouse.scale = 0.0;
	if (offset > 0.0 && z->center > 0)
	{
		scale = offset / (double)z->center;
		if (scale > 2.0)
		{
			scale = 2.0;
		}
		d->mouse.scale = scale;
	}
}

int	ft_mouse_move(int x, int y, t_data *d)
{
	t_deadzone	z;
	double		offset;

	if (!d)
	{
		return (0);
	}
	ft_mouse_clamp_xy(d, &x, &y);
	d->mouse.x = x;
	d->mouse.y = y;
	d->mouse.inside = true;
	d->mouse.dir = 0;
	d->mouse.scale = 0.0;
	ft_mouse_deadzone(d, &z);
	ft_mouse_dir_and_offset(d, x, &z, &offset);
	ft_mouse_apply_scale(d, &z, offset);
	return (0);
}

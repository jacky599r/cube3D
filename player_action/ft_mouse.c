/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 11:45:02 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/21 11:45:02 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_mouse_move(int x, int y, t_data *data)
{
	int		center;
	int		half_dead;
	int		left_bound;
	int		right_bound;
	double	offset;

	if (!data)
		return (0);
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x > data->mapx)
		x = data->mapx;
	if (y > data->mapy)
		y = data->mapy;
	data->mouse.x = x;
	data->mouse.y = y;
	data->mouse.inside = true;
	data->mouse.dir = 0;
	data->mouse.scale = 0.0;
	center = data->mapx / 2;
	half_dead = MOUSE_DEAD_ZONE_WIDTH / 2;
	if (half_dead > center)
		half_dead = center;
	left_bound = center - half_dead;
	right_bound = center + half_dead;
	offset = 0.0;
	if (x < left_bound)
	{
		data->mouse.dir = -1;
		offset = (double)(left_bound - x);
	}
	else if (x > right_bound)
	{
		data->mouse.dir = 1;
		offset = (double)(x - right_bound);
	}
	if (offset > 0.0 && center > 0)
	{
		data->mouse.scale = offset / (double)center;
		if (data->mouse.scale > 2.0)
			data->mouse.scale = 2.0;
	}
	return (0);
}

int	ft_mouse_leave(t_data *data)
{
	if (!data)
		return (0);
	data->mouse.inside = false;
	data->mouse.dir = 0;
	data->mouse.scale = 0.0;
	return (0);
}

int	ft_rotate_player_mouse(t_data *data)
{
	double	angle;
	double	base;

	if (!data || !data->mouse.inside || data->mouse.dir == 0)
		return (0);
	base = data->play.rot_speed;
	angle = base * (1.0 + data->mouse.scale);
	if (angle > base * 5.0)
		angle = base * 5.0;
	if (data->mouse.dir < 0)
		angle *= -1.0;
	return (ft_rotate_player_angle(data, angle));
}

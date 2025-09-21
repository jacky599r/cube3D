/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movment_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 07:00:58 by nico              #+#    #+#             */
/*   Updated: 2025/09/22 07:02:46 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_rotdir(int key)
{
	if (key == ROT_L)
		return (-1);
	return (1);
}

int	ft_rotate_player_angle(t_data *d, double angle)
{
	double	c;
	double	s;
	double	tmp;

	if (angle == 0.0)
		return (0);
	c = cos(angle);
	s = sin(angle);
	tmp = d->play.dir_x;
	d->play.dir_x = d->play.dir_x * c - d->play.dir_y * s;
	d->play.dir_y = tmp * s + d->play.dir_y * c;
	tmp = d->play.plane_x;
	d->play.plane_x = d->play.plane_x * c - d->play.plane_y * s;
	d->play.plane_y = tmp * s + d->play.plane_y * c;
	return (1);
}

int	ft_rotate_player(t_data *d, int key)
{
	double	ang;

	ang = ROT_SPEED * ft_rotdir(key);
	return (ft_rotate_player_angle(d, ang));
}

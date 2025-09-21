/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouse_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 11:45:02 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/22 06:58:27 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

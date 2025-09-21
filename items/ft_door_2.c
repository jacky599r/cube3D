/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_door_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 06:21:48 by nico              #+#    #+#             */
/*   Updated: 2025/09/22 06:29:40 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_interact_door(t_data *data)
{
	t_door	*door;
	int		target_x;
	int		target_y;

	target_x = (int)(data->play.pos.x + data->play.dir_x * 0.8);
	target_y = (int)(data->play.pos.y + data->play.dir_y * 0.8);
	door = ft_find_door(data, target_x, target_y);
	if (!door)
		door = ft_find_door(data, (int)data->play.pos.x, (int)data->play.pos.y);
	if (!door)
		return (0);
	return (ft_toggle_door_state(data, door));
}

void	ft_free_doors(t_data *data)
{
	if (!data)
		return ;
	free(data->doors);
	data->doors = NULL;
	data->door_cap = 0;
	data->door_count = 0;
}

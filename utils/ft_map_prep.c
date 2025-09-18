/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_prep.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:50:23 by jacky599r         #+#    #+#             */
/*   Updated: 2025/09/17 20:27:09 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int ft_allocate_flood_map(t_data *data)
{
	int y;

	data->map.fl_map = (char **)ft_calloc(data->map.high + 1, sizeof(char *));
	if (!data->map.fl_map)
		return (ft_error_msg("Error", "Memory allocation failed", NULL, FAIL));
	y = 0;
	while (y < data->map.high)
	{
		data->map.fl_map[y] = (char *)ft_calloc(data->map.wide + 1, sizeof(char));
		if (!data->map.fl_map[y])
		{
			ft_safe_array((void ***)&data->map.fl_map);
			return (ft_error_msg("Error", "Memory allocation failed", NULL, FAIL));
		}
		y++;
	}
	data->map.fl_map[y] = NULL;
	return (PASS);
}

int ft_prepare_map_for_flood_fill(t_data *data)
{
	if (ft_allocate_flood_map(data) == FAIL)
		return (FAIL);
	if (convert_to_flood_map(data) == FAIL)
	{
		ft_safe_array((void ***)&data->map.fl_map);
		return (FAIL);
	}
	return (PASS);
}

void ft_set_initial_player_view(t_data *data)
{
	data->play.dir_x = 0;
	data->play.dir_y = 0;
	data->play.plane_x = 0;
	data->play.plane_y = 0;
	if (data->play.s_dir == 'N')
	{
		data->play.dir_y = -1;
		data->play.plane_x = 0.66;
	}
	else if (data->play.s_dir == 'S')
	{
		data->play.dir_y = 1;
		data->play.plane_x = -0.66;
	}
	else if (data->play.s_dir == 'E')
	{
		data->play.dir_x = 1;
		data->play.plane_y = 0.66;
	}
	else if (data->play.s_dir == 'W')
	{
		data->play.dir_x = -1;
		data->play.plane_y = -0.66;
	}
}

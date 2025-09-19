/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_door.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 10:11:37 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/20 10:11:37 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_grow_doors(t_data *data)
{
	t_door	*next;
	int		new_cap;

	if (data->door_count < data->door_cap)
		return (PASS);
	new_cap = 8;
	if (data->door_cap > 0)
		new_cap = data->door_cap * 2;
	next = ft_calloc(new_cap, sizeof(t_door));
	if (!next)
		return (ft_error_msg("Error", "Door allocation failed", FAIL));
	if (data->doors && data->door_count > 0)
		ft_memcpy(next, data->doors, sizeof(t_door) * data->door_count);
	free(data->doors);
	data->doors = next;
	data->door_cap = new_cap;
	return (PASS);
}

int	ft_register_door(t_data *data, int x, int y)
{
	if (ft_grow_doors(data) == FAIL)
		return (FAIL);
	data->doors[data->door_count].x = x;
	data->doors[data->door_count].y = y;
	data->doors[data->door_count].is_open = 0;
	data->door_count++;
	return (PASS);
}

t_door	*ft_find_door(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->door_count)
	{
		if (data->doors[i].x == x && data->doors[i].y == y)
			return (&data->doors[i]);
		i++;
	}
	return (NULL);
}

static int	ft_player_on_tile(t_data *data, t_door *door)
{
	return ((int)data->play.pos.x == door->x
		&& (int)data->play.pos.y == door->y);
}

static int	ft_toggle_door_state(t_data *data, t_door *door)
{
	if (door->is_open)
	{
		if (ft_player_on_tile(data, door))
			return (0);
		data->map.fl_map[door->y][door->x] = 'D';
		door->is_open = 0;
	}
	else
	{
		data->map.fl_map[door->y][door->x] = '0';
		door->is_open = 1;
	}
	return (1);
}

int	ft_interact_door(t_data *data)
{
	t_door	*door;
	int		target_x;
	int		target_y;

	target_x = (int)(data->play.pos.x + data->play.dir_x * 0.8);
	target_y = (int)(data->play.pos.y + data->play.dir_y * 0.8);
	door = ft_find_door(data, target_x, target_y);
	if (!door)
		door = ft_find_door(data, (int)data->play.pos.x,
			(int)data->play.pos.y);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_enclosure.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:50:12 by jacky599r         #+#    #+#             */
/*   Updated: 2025/09/19 16:15:32 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**ft_create_temp_flood_map(t_data *data)
{
	char	**temp_map;
	int		y;

	temp_map = (char **)ft_calloc(data->map.high + 1, sizeof(char *));
	if (!temp_map)
		return (NULL);
	y = 0;
	while (y < data->map.high)
	{
		temp_map[y] = ft_strdup(data->map.fl_map[y]);
		if (!temp_map[y])
		{
			ft_safe_array((void ***)&temp_map);
			return (NULL);
		}
		y++;
	}
	temp_map[y] = NULL;
	return (temp_map);
}

void	ft_perform_flood_fill(char **map, int x, int y, t_map_dims dims)
{
	if (x < 0 || x >= dims.max_x || y < 0 || y >= dims.max_y)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'X' || map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	ft_perform_flood_fill(map, x + 1, y, dims);
	ft_perform_flood_fill(map, x - 1, y, dims);
	ft_perform_flood_fill(map, x, y + 1, dims);
	ft_perform_flood_fill(map, x, y - 1, dims);
}

int	ft_check_enclosed_borders(char **map, t_map_dims dims)
{
	int	y;
	int	x;

	y = 0;
	while (y < dims.max_y)
	{
		if (map[y][0] == 'V' || map[y][dims.max_x - 1] == 'V')
			return (FAIL);
		x = 0;
		while (x < dims.max_x)
		{
			if ((y == 0 || y == dims.max_y - 1) && map[y][x] == 'V')
				return (FAIL);
			x++;
		}
		y++;
	}
	return (PASS);
}

static int	ft_validate_single_map(t_data *data, char **flood_map)
{
	t_map_dims	dims;
	int			result;

	dims.max_x = data->map.wide;
	dims.max_y = data->map.high;
	ft_perform_flood_fill(flood_map, (int)data->play.pos.x,
		(int)data->play.pos.y, dims);
	result = ft_check_enclosed_borders(flood_map, dims);
	return (result);
}

int	ft_validate_map_enclosure(t_data *data)
{
	char	**temp_map;
	int		result;

	temp_map = ft_create_temp_flood_map(data);
	if (!temp_map)
		return (FAIL);
	result = ft_validate_single_map(data, temp_map);
	ft_safe_array((void ***)&temp_map);
	if (result == FAIL)
		return (ft_error_msg("Error", "Map is not surrounded by walls", 5));
	return (PASS);
}

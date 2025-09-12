/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_enclosure.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:50:12 by jacky599r         #+#    #+#             */
/*   Updated: 2025/08/14 17:21:37 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char **ft_create_temp_flood_map(t_data *data)
{
    char **temp_map;
    int y;

    temp_map = (char **)ft_calloc(data->map.high + 1, sizeof(char *));
    if (!temp_map)
    {
        ft_error_msg("Error", "Memory allocation failed for temp map", NULL, FAIL);
        return (NULL);
    }
    y = 0;
    while (y < data->map.high)
    {
        temp_map[y] = ft_strdup(data->fl_map[y]);
        if (!temp_map[y])
        {
            ft_safe_array((void ***)&temp_map);
            ft_error_msg("Error", "Memory allocation failed for temp map row", NULL, FAIL);
            return (NULL);
        }
        y++;
    }
    temp_map[y] = NULL;
    return (temp_map);
}

void ft_perform_flood_fill(char **map, int x, int y, t_map_dims dims)
{
    if (x < 0 || x >= dims.max_x || y < 0 || y >= dims.max_y || map[y][x] == '1' || map[y][x] == 'V')
        return;

    map[y][x] = 'V';

    ft_perform_flood_fill(map, x + 1, y, dims);
    ft_perform_flood_fill(map, x - 1, y, dims);
    ft_perform_flood_fill(map, x, y + 1, dims);
    ft_perform_flood_fill(map, x, y - 1, dims);
}

int ft_check_enclosed_borders(char **map, t_map_dims dims)
{
    int y;
    int x;

    y = 0;
    while (y < dims.max_y)
    {
        x = 0;
        if (map[y][0] == '0' || map[y][dims.max_x - 1] == '0')
            return (FAIL);
        while (x < dims.max_x)
        {
            if ((y == 0 || y == dims.max_y - 1) && map[y][x] == '0')
                return (FAIL);
            x++;
        }
        y++;
    }
    return (PASS);
}

int ft_validate_map_enclosure(t_data *data)
{
    char **temp_map;
    t_map_dims dims;
    int ret;

    temp_map = ft_create_temp_flood_map(data);
    if (!temp_map)
        return (FAIL);

    dims.max_x = data->map.wide;
    dims.max_y = data->map.high;

    ft_perform_flood_fill(temp_map, (int)data->play.pos.x, (int)data->play.pos.y, dims);

    ret = ft_check_enclosed_borders(temp_map, dims);
    ft_safe_array((void ***)&temp_map);
    
    if (ret == FAIL)
        return (ft_error_msg("Error", "Map is not surrounded by walls", NULL, FAIL));
    return (PASS);
}

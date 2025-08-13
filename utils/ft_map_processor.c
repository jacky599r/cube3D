/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_processor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:50:23 by jacky599r         #+#    #+#             */
/*   Updated: 2025/08/12 17:57:20 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int ft_prepare_map_for_flood_fill(t_data *data)
{
    int y;
    int x;
    char *temp_line;

    data->fl_map = (char **)ft_calloc(sizeof(char *) * (data->map.high + 1));
    if (!data->fl_map)
        return (ft_error_msg("Error", "Memory allocation failed for fl_map", NULL, FAIL));

    y = 0;
    while (y < data->map.high)
    {
        data->fl_map[y] = (char *)ft_calloc(sizeof(char) * (data->map.wide + 1));
        if (!data->fl_map[y])
        {
            ft_safe_array((void ***)&data->fl_map);
            return (ft_error_msg("Error", "Memory allocation failed for fl_map row", NULL, FAIL));
        }
        temp_line = data->map.og_map[y];
        x = 0;
        while (x < data->map.wide)
        {
            if (x < ft_strlen(temp_line) && (temp_line[x] == '0' || temp_line[x] == '1' || ft_strchr("NSEW", temp_line[x])))
                data->fl_map[y][x] = temp_line[x];
            else if (x < ft_strlen(temp_line) && temp_line[x] == ' ')
                data->fl_map[y][x] = '1';
            else
                data->fl_map[y][x] = '1';
            x++;
        }
        data->fl_map[y][x] = '\0';
        y++;
    }
    data->fl_map[y] = NULL;
    return (PASS);
}

void ft_set_initial_player_view(t_data *data)
{
    double dir_x, dir_y, pln_x, pln_y;

    dir_x = 0; dir_y = 0; pln_x = 0; pln_y = 0;
    if (data->play.s_dir == 'N') { dir_y = -1; pln_x = 0.66; }
    else if (data->play.s_dir == 'S') { dir_y = 1; pln_x = -0.66; }
    else if (data->play.s_dir == 'E') { dir_x = 1; pln_y = 0.66; }
    else if (data->play.s_dir == 'W') { dir_x = -1; pln_y = -0.66; }
    
    data->play.dir.x = dir_x;
    data->play.dir.y = dir_y;
    data->play.pln.x = pln_x;
    data->play.pln.y = pln_y;
}

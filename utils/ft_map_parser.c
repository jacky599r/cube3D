/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:30:00 by jacky599r         #+#    #+#             */
/*   Updated: 2025/09/17 21:50:26 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int ft_is_map_line(char *line)
{
    int i;
    
    i = 0;
    while(line[i])
    {
        if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && 
            line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != ' ')
            return (0);
        i++;
    }
    return (1);
}

static int ft_validate_map_characters(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (!ft_is_valid_map_char(line[i]))
            return (ft_error_msg("Error", "Invalid character in map", line, FAIL));
        i++;
    }
    return (PASS);
}

static int ft_process_player_info(t_data *data, char player_char, int x_pos, int y_idx)
{
    if (data->play.s_dir != '\0')
        return (ft_error_msg("Error", "Only 1 player allowed", NULL, FAIL));
    data->play.s_dir = player_char;
    data->play.pos.x = (double)x_pos + 0.5;
    data->play.pos.y = (double)y_idx + 0.5;
    return (PASS);
}

int ft_parse_map_content(t_data *data, int line_index, int start_index)
{
    char *line;
    int i;
    int current_width;

    line = data->map.og_map[line_index];
    if (ft_validate_map_characters(line) != PASS)
        return (FAIL);
    i = 0;
    while (line[i])
    {
        if (ft_strchr("NSEW", line[i]))
        {
            if (ft_process_player_info(data, line[i], i, line_index - start_index) != PASS)
                return (FAIL);
        }
        i++;
    }
    ft_strip_line_endings(line);
    current_width = ft_strlen(line);
    if (current_width > data->map.wide)
        data->map.wide = current_width;
    data->map.high++;
    return (PASS);
}

int ft_process_file_line(t_data *data, char *trimmed_line)
{
    if (data->map_start_index == -1 && ft_is_valid_param(trimmed_line))
    {
        if (ft_process_param_line(data, trimmed_line) != PASS)
            return (FAIL);
        data->param_count++;
    }
    else if (data->map_start_index == -1 && ft_is_map_line(trimmed_line))
        data->map_start_index = data->curr_line_index;
    else if (data->map_start_index != -1 && data->map.eom)
        return (ft_error_msg("Error", "Data after map data", NULL, FAIL));
    else if (data->map_start_index == -1 && !ft_is_valid_param(trimmed_line))
        return (ft_error_msg("Error", "Invalid line in file", trimmed_line, FAIL));
    return (PASS);
}

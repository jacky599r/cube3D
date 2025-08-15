/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:50:57 by jacky599r         #+#    #+#             */
/*   Updated: 2025/08/15 12:22:27 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Placeholder for ft_is_map_line (will be moved/refactored from ft_map_validation.c)
static int ft_is_map_line(char *line)
{
    int i = 0;
    while(line[i])
    {
        if (ft_strchr("01NSEW ", line[i]) == NULL)
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
        if (!ft_strchr("01NSEW \n\t\v\f\r", line[i]))
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

int ft_identify_map_properties(t_data *data, int start_index)
{
    int current_line_index;
    char *line;
    int i;
    int current_width;

    current_line_index = start_index;
    data->map.high = 0;
    data->map.wide = 0;
    while (data->map.og_map[current_line_index])
    {
        char *trimmed_check = ft_strtrim(data->map.og_map[current_line_index], " \n\t\v\f\r");
        if (ft_is_empty_line(trimmed_check))
        {
            free(trimmed_check);
            break;
        }
        free(trimmed_check);
        
        line = data->map.og_map[current_line_index];
        if (ft_validate_map_characters(line) != PASS)
            return (FAIL);
        i = 0;
        while (line[i])
        {
            if (ft_strchr("NSEW", line[i]))
            {
                if (ft_process_player_info(data, line[i], i, current_line_index - start_index) != PASS)
                    return (FAIL);
            }
            i++;
        }
        char *trimmed_width = ft_strtrim(line, " \n\t\v\f\r");
        current_width = ft_strlen(trimmed_width);
        free(trimmed_width);
        if (current_width > data->map.wide)
            data->map.wide = current_width;
        data->map.high++;
        current_line_index++;
    }
    if (data->play.s_dir == '\0')
        return (ft_error_msg("Error", "No player found in map", NULL, FAIL));
    return (PASS);
}

int ft_check_map_config(t_data *data)
{
    int i;
    int param_count;
    int map_start_index;
    int error_code;
    char *trimmed_line;

    i = 0;
    param_count = 0;
    map_start_index = -1;
    error_code = PASS;
    while (data->map.og_map[i] && error_code == PASS)
    {
        trimmed_line = ft_strtrim(data->map.og_map[i], " \n\t\r\v\f");
        if (ft_is_empty_line(trimmed_line))
        {
            if (map_start_index != -1 && !data->map.eom)
                data->map.eom = 1;
            free(trimmed_line);
            i++;
            continue;
        }
        if (map_start_index == -1 && ft_is_valid_param_identifier(trimmed_line))
        {
            if (ft_process_param_line(data, trimmed_line) != PASS)
                error_code = FAIL;
            param_count++;
        }
        else if (map_start_index == -1 && ft_is_map_line(trimmed_line))
            map_start_index = i;
        else if (map_start_index != -1 && data->map.eom)
            error_code = ft_error_msg("Error", "Data after map data", NULL, FAIL);
        else if (map_start_index == -1 && !ft_is_valid_param_identifier(trimmed_line))
            error_code = ft_error_msg("Error", "Invalid line in file", trimmed_line, FAIL);
        free(trimmed_line);
        i++;
    }
    if (param_count != 6 && error_code == PASS)
        error_code = ft_error_msg("Error", "Missing or Dup texture/colours params", NULL, FAIL);
    if (map_start_index == -1 && error_code == PASS)
        error_code = ft_error_msg("Error", "No map found in file", NULL, FAIL);
    if (error_code == PASS)
    {
        data->map.start_index = map_start_index;  // Store the map start index
        error_code = ft_identify_map_properties(data, map_start_index);
    }
    return (error_code);
}

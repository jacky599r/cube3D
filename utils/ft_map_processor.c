/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_processor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:50:23 by jacky599r         #+#    #+#             */
/*   Updated: 2025/09/16 15:14:46 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int ft_prepare_map_for_flood_fill(t_data *data)
{
    int y;
    int x;
    char *temp_line;
    int current_line_length;
    int max_line_length;

    // First pass: find the maximum line length and earliest content start
    max_line_length = 0;
    int earliest_content_start = 999;  // Track the earliest non-space character position
    y = 0;
    while (y < data->map.high)
    {
        temp_line = data->map.og_map[y + data->map.start_index];
        current_line_length = ft_strlen(temp_line);
        
        // Remove only trailing newlines/carriage returns, keep spaces
        while (current_line_length > 0 && 
               (temp_line[current_line_length - 1] == '\n' || 
                temp_line[current_line_length - 1] == '\r'))
        {
            current_line_length--;
        }
        
        // Find the first non-space character to determine content start
        int content_start = 0;
        while (content_start < current_line_length && temp_line[content_start] == ' ')
            content_start++;
        
        // Only consider lines with actual content (not empty)
        if (content_start < current_line_length)
        {
            if (content_start < earliest_content_start)
                earliest_content_start = content_start;
        }
        
        if (current_line_length > max_line_length)
            max_line_length = current_line_length;
        y++;
    }

    // Handle edge case where no content was found
    if (earliest_content_start == 999)
        earliest_content_start = 0;
    
    // Pre-padding validation: check if original content is properly walled
    y = 0;
    while (y < data->map.high)
    {
        temp_line = data->map.og_map[y + data->map.start_index];
        current_line_length = ft_strlen(temp_line);
        
        // Remove only trailing newlines/carriage returns
        while (current_line_length > 0 && 
               (temp_line[current_line_length - 1] == '\n' || 
                temp_line[current_line_length - 1] == '\r'))
        {
            current_line_length--;
        }
        
        // Skip empty lines
        if (current_line_length == 0)
        {
            y++;
            continue;
        }
        
        // Find actual content boundaries (excluding leading/trailing spaces)
        int content_start = 0;
        int content_end = current_line_length - 1;
        
        while (content_start < current_line_length && temp_line[content_start] == ' ')
            content_start++;
        while (content_end >= content_start && temp_line[content_end] == ' ')
            content_end--;
        
        // Check if this line has actual content
        if (content_start <= content_end)
        {
            // Only check that the content area has valid map characters
            // Allow gapped perimeters - flood-fill will handle escape validation
            int x = content_start;
            while (x <= content_end)
            {
                if (temp_line[x] != '0' && temp_line[x] != '1' && 
                    !ft_strchr("NSEW", temp_line[x]) && temp_line[x] != ' ')
                {
                    return (ft_error_msg("Error", "Invalid character in map", NULL, FAIL));
                }
                x++;
            }
        }
        y++;
    }
    
    // Update the map width to the actual maximum line length
    data->map.wide = max_line_length;

    // Second pass: create the flood fill map with padding
    data->map.fl_map = (char **)ft_calloc(data->map.high + 1, sizeof(char *));
    if (!data->map.fl_map)
        return (ft_error_msg("Error", "Memory allocation failed for fl_map", NULL, FAIL));

    y = 0;
    while (y < data->map.high)
    {
        data->map.fl_map[y] = (char *)ft_calloc(data->map.wide + 1, sizeof(char));
        if (!data->map.fl_map[y])
        {
            ft_safe_array((void ***)&data->map.fl_map);
            return (ft_error_msg("Error", "Memory allocation failed for fl_map row", NULL, FAIL));
        }
        
        temp_line = data->map.og_map[y + data->map.start_index];
        current_line_length = ft_strlen(temp_line);
        
        // Remove only trailing newlines/carriage returns, keep spaces
        while (current_line_length > 0 && 
               (temp_line[current_line_length - 1] == '\n' || 
                temp_line[current_line_length - 1] == '\r'))
        {
            current_line_length--;
        }
        
        // Find the first non-space character in this line
        int line_content_start = 0;
        while (line_content_start < current_line_length && temp_line[line_content_start] == ' ')
            line_content_start++;
        
        x = 0;
        while (x < data->map.wide)
        {
            if (x < current_line_length)
            {
                // Pad leading spaces that occur before the content starts on this line
                // AND when other lines start earlier (earliest_content_start)
                if (x < line_content_start && temp_line[x] == ' ')
                    data->map.fl_map[y][x] = 'X';
                // Copy the original character for content area
                else if (temp_line[x] == '0' || temp_line[x] == '1' || ft_strchr("NSEW", temp_line[x]))
                    data->map.fl_map[y][x] = temp_line[x];
                else if (temp_line[x] == ' ')
                    data->map.fl_map[y][x] = ' ';  // Keep internal spaces as spaces for now
                else if (temp_line[x] == '\t')
                    data->map.fl_map[y][x] = ' ';  // Convert tabs to spaces
                else
                    data->map.fl_map[y][x] = '1';  // Convert any other chars to walls
            }
            else
            {
                // Pad with 'X' where the line is shorter than max width
                data->map.fl_map[y][x] = 'X';
            }
            x++;
        }
        data->map.fl_map[y][x] = '\0';
        y++;
    }
    data->map.fl_map[y] = NULL;
    
    // Third pass: convert all remaining spaces to 'X' padding
    y = 0;
    while (y < data->map.high)
    {
        x = 0;
        while (x < data->map.wide)
        {
            if (data->map.fl_map[y][x] == ' ')
            {
                // Convert all spaces (internal, trailing, etc.) to 'X' padding
                data->map.fl_map[y][x] = 'X';
            }
            x++;
        }
        y++;
    }
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
	
	data->play.dir_x = dir_x;
	data->play.dir_y = dir_y;
	data->play.plane_x = pln_x;
	data->play.plane_y = pln_y;
}

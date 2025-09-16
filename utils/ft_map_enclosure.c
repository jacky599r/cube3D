/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_enclosure.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:50:12 by jacky599r         #+#    #+#             */
/*   Updated: 2025/09/16 14:59:07 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Debug function to print the map with player location
static void ft_debug_print_map(char **map, t_map_dims dims, int player_x, int player_y)
{
    int y;
    int x;

    printf("\n=== DEBUG: Map State ===\n");
    printf("Map dimensions: %d x %d\n", dims.max_x, dims.max_y);
    printf("Player position: (%d, %d)\n", player_x, player_y);
    printf("Map contents:\n");
    
    y = 0;
    while (y < dims.max_y)
    {
        printf("%2d: ", y);
        x = 0;
        while (x < dims.max_x)
        {
            if (x == player_x && y == player_y)
                printf("P");  // Mark player position
            else
                printf("%c", map[y][x]);
            x++;
        }
        printf("\n");
        y++;
    }
    printf("=== End Map State ===\n\n");
}

// Debug function to print flood fill progress
static void ft_debug_flood_fill_step(char **map, int x, int y, t_map_dims dims, int depth)
{
    if (depth > 100)  // Prevent infinite recursion debug spam
        return;
    
    printf("Flood fill step %d: visiting (%d, %d) = '%c'\n", depth, x, y, map[y][x]);
    
    // Print small area around current position
    int start_y = (y - 2 > 0) ? y - 2 : 0;
    int end_y = (y + 2 < dims.max_y) ? y + 2 : dims.max_y - 1;
    int start_x = (x - 2 > 0) ? x - 2 : 0;
    int end_x = (x + 2 < dims.max_x) ? x + 2 : dims.max_x - 1;
    
    printf("  Area around (%d, %d):\n", x, y);
    int debug_y = start_y;
    while (debug_y <= end_y)
    {
        printf("    %2d: ", debug_y);
        int debug_x = start_x;
        while (debug_x <= end_x)
        {
            if (debug_x == x && debug_y == y)
                printf("[%c]", map[debug_y][debug_x]);
            else
                printf(" %c ", map[debug_y][debug_x]);
            debug_x++;
        }
        printf("\n");
        debug_y++;
    }
    printf("\n");
}

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
        temp_map[y] = ft_strdup(data->map.fl_map[y]);
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
    static int debug_depth = 0;
    
    if (x < 0 || x >= dims.max_x || y < 0 || y >= dims.max_y || map[y][x] == '1' || map[y][x] == 'X' || map[y][x] == ' ' || map[y][x] == 'V')
    {
        if (debug_depth < 5)  // Only show first few boundary checks
        {
            printf("Flood fill boundary check: (%d, %d) - ", x, y);
            if (x < 0) printf("X < 0");
            else if (x >= dims.max_x) printf("X >= %d", dims.max_x);
            else if (y < 0) printf("Y < 0");
            else if (y >= dims.max_y) printf("Y >= %d", dims.max_y);
            else if (map[y][x] == '1') printf("Wall at (%d, %d)", x, y);
            else if (map[y][x] == 'X') printf("Padding wall at (%d, %d)", x, y);
            else if (map[y][x] == ' ') printf("Space wall at (%d, %d)", x, y);
            else if (map[y][x] == 'V') printf("Already visited at (%d, %d)", x, y);
            printf("\n");
        }
        return;
    }
    
    debug_depth++;
    ft_debug_flood_fill_step(map, x, y, dims, debug_depth);
    map[y][x] = 'V';

    ft_perform_flood_fill(map, x + 1, y, dims);
    ft_perform_flood_fill(map, x - 1, y, dims);
    ft_perform_flood_fill(map, x, y + 1, dims);
    ft_perform_flood_fill(map, x, y - 1, dims);
    
    debug_depth--;
}

// Check if flood fill reached any position that was originally a space
int ft_check_space_reachability(char **flood_map, t_data *data, t_map_dims dims)
{
    int y;
    int x;
    char *temp_line;
    int found_space_reach = 0;
    int current_line_length;

    printf("\n=== DEBUG: Checking space reachability ===\n");
    
    y = 0;
    while (y < dims.max_y)
    {
        temp_line = data->map.og_map[y + data->map.start_index];
        current_line_length = ft_strlen(temp_line);
        
        // Remove trailing newlines/carriage returns
        while (current_line_length > 0 && 
               (temp_line[current_line_length - 1] == '\n' || 
                temp_line[current_line_length - 1] == '\r'))
        {
            current_line_length--;
        }
        
        x = 0;
        while (x < dims.max_x)
        {
            // Check if this position was originally a space/tab AND flood fill reached it
            int was_originally_space = 0;
            if (x < current_line_length)
            {
                if (temp_line[x] == ' ' || temp_line[x] == '\t')
                    was_originally_space = 1;
            }
            else
            {
                // Position beyond original line length (would be padded)
                was_originally_space = 1;
            }
            
            if (was_originally_space && flood_map[y][x] == 'V')
            {
                printf("FAIL: Flood fill reached position (%d, %d) that was originally a space/padding\n", x, y);
                printf("      Original char at (%d, %d): '%c' (or beyond line end)\n", x, y, 
                       (x < current_line_length) ? temp_line[x] : ' ');
                found_space_reach = 1;
            }
            x++;
        }
        y++;
    }
    
    if (!found_space_reach)
        printf("PASS: Flood fill only reached valid walkable areas\n");
    else
        printf("FAIL: Player can reach areas that were originally spaces/padding\n");
    
    printf("=== End space reachability check ===\n\n");
    
    return (found_space_reach ? FAIL : PASS);
}

int ft_check_enclosed_borders(char **map, t_map_dims dims)
{
    int y;
    int x;
    int found_escape = 0;

    printf("\n=== DEBUG: Checking enclosed borders ===\n");
    
    y = 0;
    while (y < dims.max_y)
    {
        x = 0;
        if (map[y][0] == '0' || map[y][0] == 'V' || map[y][dims.max_x - 1] == '0' || map[y][dims.max_x - 1] == 'V')
        {
            printf("FAIL: Found unwalled opening on vertical border at row %d: left='%c', right='%c'\n", 
                   y, map[y][0], map[y][dims.max_x - 1]);
            found_escape = 1;
        }
        while (x < dims.max_x)
        {
            if ((y == 0 || y == dims.max_y - 1) && (map[y][x] == '0' || map[y][x] == 'V'))
            {
                printf("FAIL: Found unwalled opening on horizontal border at (%d, %d) = '%c'\n", x, y, map[y][x]);
                found_escape = 1;
            }
            x++;
        }
        y++;
    }
    
    if (!found_escape)
        printf("PASS: All borders are properly walled\n");
    else
        printf("FAIL: Map has escape routes through borders\n");
    
    printf("=== End border check ===\n\n");
    
    return (found_escape ? FAIL : PASS);
}

// Create original map without padding for validation
char **ft_create_original_flood_map(t_data *data)
{
    char **temp_map;
    int y;
    int x;
    char *temp_line;
    int current_line_length;

    temp_map = (char **)ft_calloc(data->map.high + 1, sizeof(char *));
    if (!temp_map)
        return (NULL);

    y = 0;
    while (y < data->map.high)
    {
        temp_map[y] = (char *)ft_calloc(data->map.wide + 1, sizeof(char));
        if (!temp_map[y])
        {
            ft_safe_array((void ***)&temp_map);
            return (NULL);
        }
        
        temp_line = data->map.og_map[y + data->map.start_index];
        current_line_length = ft_strlen(temp_line);
        
        // Remove trailing newlines/carriage returns
        while (current_line_length > 0 && 
               (temp_line[current_line_length - 1] == '\n' || 
                temp_line[current_line_length - 1] == '\r'))
        {
            current_line_length--;
        }
        
        x = 0;
        while (x < data->map.wide)
        {
            if (x < current_line_length)
            {
                if (temp_line[x] == '0' || temp_line[x] == '1' || ft_strchr("NSEW", temp_line[x]))
                    temp_map[y][x] = temp_line[x];
                else if (temp_line[x] == ' ' || temp_line[x] == '\t')
                    temp_map[y][x] = '0';  // Treat spaces as openings for validation
                else
                    temp_map[y][x] = '1';
            }
            else
            {
                temp_map[y][x] = '1';  // Pad short lines with walls for validation
            }
            x++;
        }
        temp_map[y][x] = '\0';
        y++;
    }
    temp_map[y] = NULL;
    return (temp_map);
}

int ft_validate_map_enclosure(t_data *data)
{
    char **original_map;
    char **padded_map;
    t_map_dims dims;
    int ret;

    printf("\n=== DEBUG: Starting map enclosure validation ===\n");
    printf("Player position: (%d, %d)\n", (int)data->play.pos.x, (int)data->play.pos.y);
    printf("Map dimensions: %d x %d\n", data->map.wide, data->map.high);

    // First validate original map structure (spaces treated as openings)
    printf("\n=== VALIDATING ORIGINAL MAP STRUCTURE ===\n");
    original_map = ft_create_original_flood_map(data);
    if (!original_map)
        return (FAIL);

    dims.max_x = data->map.wide;
    dims.max_y = data->map.high;

    printf("\n--- BEFORE flood fill (original structure) ---");
    ft_debug_print_map(original_map, dims, (int)data->play.pos.x, (int)data->play.pos.y);

    printf("--- Starting flood fill on original structure ---\n");
    ft_perform_flood_fill(original_map, (int)data->play.pos.x, (int)data->play.pos.y, dims);
    printf("--- Flood fill completed ---\n");

    printf("\n--- AFTER flood fill (original structure) ---");
    ft_debug_print_map(original_map, dims, (int)data->play.pos.x, (int)data->play.pos.y);

    // Check both border escape and space reachability
    int border_check = ft_check_enclosed_borders(original_map, dims);
    int space_check = ft_check_space_reachability(original_map, data, dims);
    
    ret = (border_check == FAIL || space_check == FAIL) ? FAIL : PASS;
    ft_safe_array((void ***)&original_map);
    
    if (ret == FAIL)
        return (ft_error_msg("Error", "Map allows player to reach invalid areas (spaces/padding)", NULL, FAIL));

    // If original structure is valid, check padded map for consistency
    printf("\n=== VALIDATING PADDED MAP STRUCTURE ===\n");
    padded_map = ft_create_temp_flood_map(data);
    if (!padded_map)
        return (FAIL);

    printf("\n--- BEFORE flood fill (padded structure) ---");
    ft_debug_print_map(padded_map, dims, (int)data->play.pos.x, (int)data->play.pos.y);

    printf("--- Starting flood fill on padded structure ---\n");
    ft_perform_flood_fill(padded_map, (int)data->play.pos.x, (int)data->play.pos.y, dims);
    printf("--- Flood fill completed ---\n");

    printf("\n--- AFTER flood fill (padded structure) ---");
    ft_debug_print_map(padded_map, dims, (int)data->play.pos.x, (int)data->play.pos.y);

    ret = ft_check_enclosed_borders(padded_map, dims);
    ft_safe_array((void ***)&padded_map);
    
    if (ret == FAIL)
        return (ft_error_msg("Error", "Map is not surrounded by walls", NULL, FAIL));
    
    printf("=== Map enclosure validation PASSED ===\n\n");
    return (PASS);
}

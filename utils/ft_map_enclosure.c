/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_enclosure.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:50:12 by jacky599r         #+#    #+#             */
/*   Updated: 2025/08/15 13:15:18 by jacky599r        ###   ########.fr       */
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
        if (map[y][0] == '0' || map[y][dims.max_x - 1] == '0')
        {
            printf("FAIL: Found '0' on vertical border at row %d: left='%c', right='%c'\n", 
                   y, map[y][0], map[y][dims.max_x - 1]);
            found_escape = 1;
        }
        while (x < dims.max_x)
        {
            if ((y == 0 || y == dims.max_y - 1) && map[y][x] == '0')
            {
                printf("FAIL: Found '0' on horizontal border at (%d, %d) = '%c'\n", x, y, map[y][x]);
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

int ft_validate_map_enclosure(t_data *data)
{
    char **temp_map;
    t_map_dims dims;
    int ret;

    printf("\n=== DEBUG: Starting map enclosure validation ===\n");
    printf("Player position: (%d, %d)\n", (int)data->play.pos.x, (int)data->play.pos.y);
    printf("Map dimensions: %d x %d\n", data->map.wide, data->map.high);

    temp_map = ft_create_temp_flood_map(data);
    if (!temp_map)
        return (FAIL);

    dims.max_x = data->map.wide;
    dims.max_y = data->map.high;

    // Print map before flood fill
    printf("\n--- BEFORE flood fill ---");
    ft_debug_print_map(temp_map, dims, (int)data->play.pos.x, (int)data->play.pos.y);

    // Perform flood fill
    printf("--- Starting flood fill from player position ---\n");
    ft_perform_flood_fill(temp_map, (int)data->play.pos.x, (int)data->play.pos.y, dims);
    printf("--- Flood fill completed ---\n");

    // Print map after flood fill
    printf("\n--- AFTER flood fill ---");
    ft_debug_print_map(temp_map, dims, (int)data->play.pos.x, (int)data->play.pos.y);

    ret = ft_check_enclosed_borders(temp_map, dims);
    ft_safe_array((void ***)&temp_map);
    
    if (ret == FAIL)
        return (ft_error_msg("Error", "Map is not surrounded by walls", NULL, FAIL));
    
    printf("=== Map enclosure validation PASSED ===\n\n");
    return (PASS);
}

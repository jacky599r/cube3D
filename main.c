/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:43:43 by nico              #+#    #+#             */
/*   Updated: 2025/09/16 15:20:55 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Function declarations
int ft_extension_check(char *file);
int ft_open_file(char *path);
int ft_process_map(t_data *data, char **argv);
void ft_game_start(t_data *data);
void ft_raycasting(t_data *data);
int ft_key_press(int keycode, t_data *data);
int ft_key_release(int keycode, t_data *data);
int ft_raycast_check(t_data *data);

int ft_extension_check(char *file)
{
    int len;

    if (!file)
        return (ft_error_msg("Error", "No file specified", NULL, FAIL));
    
    len = ft_strlen(file);
    if (len < 5)
        return (ft_error_msg("Error", "File name too short", file, FAIL));
    
    if (ft_strncmp(file + len - 4, ".cub", 4) != 0)
        return (ft_error_msg("Error", "Invalid file extension", file, FAIL));
    
    return (PASS);
}

int ft_open_file(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_error_msg("Error", "Cannot open file", path, FAIL));
	close(fd);
	return (PASS);
}

int ft_data_validation(t_data *data, int argc, char **argv)
{
    ft_data_init(data);
    
    // Validate argument count
    if (argc != 2)
        return (ft_error_msg("Error", "Invalid number of arguments", NULL, FAIL));
    
    // Validate file path is not NULL
    if (!argv[1])
        return (ft_error_msg("Error", "No file specified", NULL, FAIL));
    
    // Validate file extension
    if (ft_extension_check(argv[1]) != PASS)
        return (FAIL);
    
    // Validate file accessibility
    if (ft_open_file(argv[1]) != PASS)
        return (FAIL);
    
    // Read and validate file content
    data->map.og_map = ft_get_raw_map_data(argv[1]);
    if (!data->map.og_map)
        return (FAIL);
    
    // Validate map configuration
    if (ft_check_map_config(data) == FAIL)
    {
        ft_safe_array((void ***)&data->map.og_map);
        return (FAIL);
    }
    
    // Prepare map for flood-fill validation
    if (ft_prepare_map_for_flood_fill(data) == FAIL)
    {
        ft_safe_array((void ***)&data->map.og_map);
        return (FAIL);
    }
    
    // Set initial player view
    ft_set_initial_player_view(data);
    
    // Validate map enclosure
    if (ft_validate_map_enclosure(data) == FAIL)
    {
        ft_safe_array((void ***)&data->map.og_map);
        ft_safe_array((void ***)&data->map.fl_map);
        return (FAIL);
    }
    return (PASS);
}

// Simple implementation of ft_process_map for now
int ft_process_map(t_data *data, char **argv)
{
	(void)data; // Suppress unused parameter warning
	(void)argv; // Suppress unused parameter warning
	// For now, just return PASS - this can be enhanced later
	// This function would typically process the map data for rendering
	return (PASS);
}

// Raycast check function - handles player movement and raycasting updates
int ft_raycast_check(t_data *d)
{
	ft_player_action(d);
	if (d->play.check == 0)
		return (0);
	ft_raycasting(d);
	return (0);
}

// ft_key_press and ft_key_release are implemented in player_action/ft_keyhook.c

// Stub implementations for missing functions
void ft_print_welcome(void)
{
	printf("Welcome to Cub3D!\n");
}

void ft_print_exit(void)
{
	printf("Exiting Cub3D...\n");
}


int	main(int argc, char **argv)
{
	t_data	*data;
	int		err_code;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	
	err_code = ft_data_validation(data, argc, argv);
	if (err_code != PASS)
		return (ft_freedom(data), err_code);
	
	err_code = ft_process_map(data, argv);
	if (err_code != PASS)
		return (ft_freedom(data), err_code);
	
	// Initialize MLX and start the game
	ft_game_start(data);
	ft_raycasting(data);
	mlx_hook(data->wind, 2, 1L << 0, ft_key_press, data);
	mlx_hook(data->wind, 3, 1L << 1, ft_key_release, data);
	mlx_loop_hook(data->mlx, ft_raycast_check, data);
	mlx_loop(data->mlx);
	
	return (0);
}

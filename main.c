/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:43:43 by nico              #+#    #+#             */
/*   Updated: 2025/09/16 11:08:09 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Function declarations
int ft_extension_check(char *file, char *ext);
int ft_open_file(char *path);
int ft_process_map(t_data *data, char **argv);
void ft_game_start(t_data *data);
void ft_raycasting(t_data *data);
int ft_key_press(int keycode, t_data *data);
int ft_key_release(int keycode, t_data *data);
int ft_raycast_check(t_data *data);
void ft_freedom(t_data *data);

// Extension check function (commented out for now)
/*
int ft_extension_check(char *file, char *ext)
{
	int len;

	len = ft_strlen(file);
	if (len < 5)
		return (ft_error_msg("Error File Name", file, NULL, 3));
	if (ft_strncmp(file + len - 4, ext, 4) != 0)
		return (ft_error_msg("Error File Name", file, NULL, 3));
	return(0);
}
*/

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
	if (argc != 2)
		return (ft_error_msg("Error", "Invalid number of arguments", NULL, FAIL));
	if (ft_strncmp(argv[0], "./cub3D", 7) != 0)
		return (ft_error_msg("Error", "Incorrect executable name", NULL, FAIL));
	// Temporarily skip extension check until function is implemented
	// if (ft_extension_check(argv[1], ".cub") != PASS)
	// 	return (FAIL);
	if (ft_open_file(argv[1]) != PASS)
		return (FAIL);
	data->map.og_map = ft_get_raw_map_data(argv[1]);
	if (!data->map.og_map)
		return (FAIL);
	if (ft_check_map_config(data) == FAIL)
		return (FAIL);
	if (ft_prepare_map_for_flood_fill(data) == FAIL)
		return (FAIL);
	ft_set_initial_player_view(data);
	if (ft_validate_map_enclosure(data) == FAIL)
		return (FAIL);
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

// Simple implementation of ft_raycast_check for now
int ft_raycast_check(t_data *data)
{
	(void)data; // Suppress unused parameter warning
	// For now, just return 0 - this can be enhanced later
	// This function would typically handle raycasting updates
	return (0);
}

// Simple implementation of ft_key_press for now
int ft_key_press(int keycode, t_data *data)
{
	(void)data; // Suppress unused parameter warning
	if (keycode == ESC_KEY)
		exit(0);
	// For now, just return 0 - this can be enhanced later
	return (0);
}

// Simple implementation of ft_key_release for now
int ft_key_release(int keycode, t_data *data)
{
	(void)keycode; // Suppress unused parameter warning
	(void)data; // Suppress unused parameter warning
	// For now, just return 0 - this can be enhanced later
	return (0);
}

// Stub implementations for missing functions
void ft_print_welcome(void)
{
	printf("Welcome to Cub3D!\n");
}

void ft_print_exit(void)
{
	printf("Exiting Cub3D...\n");
}

// Simple implementation of ft_freedom for now
void ft_freedom(t_data *data)
{
	if (!data)
		return;
	
	printf("Freeing memory...\n");
	
	// For now, just free the main data structure
	// This can be enhanced later with proper cleanup
	free(data);
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
	
	// Temporarily disabled MLX functionality for testing
	printf("Cub3D initialized successfully!\n");
	printf("Map validation completed.\n");
	
	// Clean up and exit
	ft_freedom(data);
	return (0);
}

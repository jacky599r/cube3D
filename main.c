/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeong <zyeong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:43:43 by nico              #+#    #+#             */
/*   Updated: 2025/09/18 15:44:56 by zyeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Function declarations
int ft_process_map(t_data *data, char **argv);
void ft_game_start(t_data *data);
void ft_raycasting(t_data *data);
int ft_key_press(int keycode, t_data *data);
int ft_key_release(int keycode, t_data *data);
int ft_raycast_check(t_data *data);

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
	ft_game_start(data);
	ft_raycasting(data);
	mlx_hook(data->wind, 2, 1L << 0, ft_key_press, data);
	mlx_hook(data->wind, 3, 1L << 1, ft_key_release, data);
	mlx_loop_hook(data->mlx, ft_raycast_check, data);
	mlx_loop(data->mlx);
	
	return (0);
}

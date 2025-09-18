/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_standalone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:00:00 by jacky599r         #+#    #+#             */
/*   Updated: 2025/09/17 21:45:32 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Stub implementations for functions we don't need for validation testing
void ft_game_start(t_data *data) { (void)data; }
void ft_raycasting(t_data *data) { (void)data; }
int ft_key_press(int keycode, t_data *data) { (void)keycode; (void)data; return 0; }
int ft_key_release(int keycode, t_data *data) { (void)keycode; (void)data; return 0; }
int ft_raycast_check(t_data *data) { (void)data; return 0; }
void ft_print_welcome(void) { }
void ft_print_exit(void) { }
void ft_player_action(t_data *data) { (void)data; }

// MLX stub functions
void *mlx_init(void) { return (void *)1; }
void *mlx_new_window(void *mlx, int width, int height, char *title) 
{ 
    (void)mlx; (void)width; (void)height; (void)title; 
    return (void *)1; 
}
int mlx_hook(void *win, int x_event, int x_mask, int (*funct)(), void *param)
{
    (void)win; (void)x_event; (void)x_mask; (void)funct; (void)param;
    return 0;
}
int mlx_loop_hook(void *mlx, int (*funct)(), void *param)
{
    (void)mlx; (void)funct; (void)param;
    return 0;
}
int mlx_loop(void *mlx)
{
    (void)mlx;
    return 0;
}

int main(int argc, char **argv)
{
    t_data *data;
    int err_code;

    data = malloc(sizeof(t_data));
    if (!data)
    {
        printf("Memory allocation failed\n");
        return (1);
    }
    
    // Run validation only
    printf("Starting validation...\n");
    err_code = ft_data_validation(data, argc, argv);
    printf("Validation returned: %d\n", err_code);
    
    // Clean up
    printf("Cleaning up resources...\n");
    ft_freedom(data);
    
    if (err_code != PASS)
    {
        printf("Validation failed with error code: %d\n", err_code);
        return (1);
    }
    
    printf("Validation passed successfully\n");
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:20:00 by jacky599r         #+#    #+#             */
/*   Updated: 2025/09/17 23:13:36 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Stub implementations for MLX functions when MLX is not available
// These allow compilation without MLX for testing purposes

void *mlx_init(void)
{
    printf("MLX stub: mlx_init() called\n");
    return (NULL);
}

void *mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title)
{
    (void)mlx_ptr;
    printf("MLX stub: mlx_new_window() called - size: %dx%d, title: %s\n", size_x, size_y, title);
    return (NULL);
}

void *mlx_new_image(void *mlx_ptr, int width, int height)
{
    (void)mlx_ptr;
    printf("MLX stub: mlx_new_image() called - size: %dx%d\n", width, height);
    return (NULL);
}

char *mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian)
{
    (void)img_ptr;
    printf("MLX stub: mlx_get_data_addr() called\n");
    if (bits_per_pixel) *bits_per_pixel = 32;
    if (size_line) *size_line = 1024 * 4;
    if (endian) *endian = 0;
    return (NULL);
}

int mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param)
{
    (void)win_ptr;
    (void)funct;
    (void)param;
    printf("MLX stub: mlx_hook() called - event: %d, mask: %d\n", x_event, x_mask);
    return (0);
}

int mlx_loop_hook(void *mlx_ptr, int (*f)(), void *param)
{
    (void)mlx_ptr;
    (void)f;
    (void)param;
    printf("MLX stub: mlx_loop_hook() called\n");
    return (0);
}

int mlx_loop(void *mlx_ptr)
{
    (void)mlx_ptr;
    printf("MLX stub: mlx_loop() called - entering infinite loop for testing\n");
    printf("Press Ctrl+C to exit\n");
    while (1)
    {
        // Infinite loop for testing
        usleep(100000); // Sleep for 100ms
    }
    return (0);
}

int mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y)
{
    (void)mlx_ptr;
    (void)win_ptr;
    (void)img_ptr;
    printf("MLX stub: mlx_put_image_to_window() called - pos: (%d, %d)\n", x, y);
    return (0);
}

int mlx_destroy_window(void *mlx_ptr, void *win_ptr)
{
    (void)mlx_ptr;
    (void)win_ptr;
    printf("MLX stub: mlx_destroy_window() called\n");
    return (0);
}

int mlx_destroy_image(void *mlx_ptr, void *img_ptr)
{
    (void)mlx_ptr;
    (void)img_ptr;
    printf("MLX stub: mlx_destroy_image() called\n");
    return (0);
}

int mlx_destroy_display(void *mlx_ptr)
{
    (void)mlx_ptr;
    printf("MLX stub: mlx_destroy_display() called\n");
    return (0);
}

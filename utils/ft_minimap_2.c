/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 06:00:22 by nico              #+#    #+#             */
/*   Updated: 2025/09/22 06:14:45 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_minimap_stride(t_img *img)
{
	if (!img)
		return (0);
	return (img->line / 4);
}

void	ft_draw_label(t_data *data, int y, int fg, char *msg)
{
	int	width;
	int	height;
	int	dx;
	int	dy;
	int	x;

	x = data->mini_off_x + 2;
	if (!data || !data->mlx || !data->wind || !msg)
		return ;
	width = (int)(ft_strlen(msg) * 7);
	if (width < 1)
		width = 1;
	height = 10;
	dy = -15;
	while (dy < height)
	{
		dx = -4;
		while (dx < width + 4)
		{
			mlx_pixel_put(data->mlx, data->wind, x + dx, y + dy, 0x000000);
			dx++;
		}
		dy++;
	}
	mlx_string_put(data->mlx, data->wind, x, y, fg, msg);
}

void	ft_draw_tile(t_data *data, int map_x, int map_y, int color)
{
	int	px;
	int	py;
	int	stride;
	int	base_x;
	int	base_y;

	stride = ft_minimap_stride(&data->mini);
	base_x = map_x * data->mini_tile;
	base_y = map_y * data->mini_tile;
	py = 0;
	while (py < data->mini_tile && base_y + py < data->mini_height)
	{
		px = 0;
		while (px < data->mini_tile && base_x + px < data->mini_width)
		{
			data->mini.addr[(base_y + py) * stride + (base_x + px)] = color;
			px++;
		}
		py++;
	}
}

void	ft_mm_fill_row(t_data *d, int y, int sx, int ex)
{
	int	stride;
	int	row;
	int	x;

	stride = ft_minimap_stride(&d->mini);
	row = y * stride;
	x = sx;
	while (x <= ex)
	{
		d->mini.addr[row + x] = 0xFFD700;
		x++;
	}
}

void	ft_mm_fill_square(t_data *d, int cx, int cy, int spread)
{
	int	sx;
	int	ex;
	int	sy;
	int	ey;
	int	y;

	sx = cx - spread;
	ex = cx + spread;
	sy = cy - spread;
	ey = cy + spread;
	if (sx < 0)
		sx = 0;
	if (sy < 0)
		sy = 0;
	if (ex >= d->mini_width)
		ex = d->mini_width - 1;
	if (ey >= d->mini_height)
		ey = d->mini_height - 1;
	y = sy;
	while (y <= ey)
	{
		ft_mm_fill_row(d, y, sx, ex);
		y++;
	}
}

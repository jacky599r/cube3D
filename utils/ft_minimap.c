/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 10:12:03 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/19 22:58:18 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_minimap_stride(t_img *img)
{
	if (!img)
		return (0);
	return (img->line / 4);
}

int	ft_apply_visibility(int color, double visibility)
{
	double	factor;
	int		r;
	int		g;
	int		b;

	if (visibility < 0.0)
		visibility = 0.0;
	if (visibility > 1.0)
		visibility = 1.0;
	factor = 0.05 + (1.0 - 0.05) * visibility;
	r = (int)(((color >> 16) & 0xFF) * factor);
	g = (int)(((color >> 8) & 0xFF) * factor);
	b = (int)((color & 0xFF) * factor);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

double	ft_tile_visibility(t_data *data, int map_x, int map_y, int update_fog)
{
	double	tile_cx;
	double	tile_cy;
	double	dist;
	double	temp_vis;
	double	stored;
	double	final;

	if (!data || map_x < 0 || map_y < 0
		|| map_y >= data->map.high || map_x >= data->map.wide)
		return (0.0);
	tile_cx = (double)map_x + 0.5;
	tile_cy = (double)map_y + 0.5;
	dist = hypot(tile_cx - data->play.pos.x, tile_cy - data->play.pos.y);
	temp_vis = 1.0 - (dist / MINIMAP_FOG_RADIUS);
	if (temp_vis < 0.0)
		temp_vis = 0.0;
	if (temp_vis > 1.0)
		temp_vis = 1.0;
	stored = 0.0;
	if (data->fog)
	{
		if (update_fog && temp_vis > data->fog[map_y][map_x])
			data->fog[map_y][map_x] = temp_vis;
		stored = data->fog[map_y][map_x];
		if (!update_fog && temp_vis > stored)
			stored = temp_vis;
	}
	else
		stored = temp_vis;
	final = temp_vis + stored * 0.25;
	if (final > 1.0)
		final = 1.0;
	if (final < 0.0)
		final = 0.0;
	return (final);
}

static void	ft_draw_tile(t_data *data, int map_x, int map_y,
		int color, double visibility)
{
	int	px;
	int	py;
	int	stride;
	int	base_x;
	int	base_y;
	int	shade;

	stride = ft_minimap_stride(&data->mini);
	base_x = map_x * data->mini_tile;
	base_y = map_y * data->mini_tile;
	shade = ft_apply_visibility(color, visibility);
	py = 0;
	while (py < data->mini_tile && base_y + py < data->mini_height)
	{
		px = 0;
		while (px < data->mini_tile && base_x + px < data->mini_width)
		{
			data->mini.addr[(base_y + py) * stride + (base_x + px)] = shade;
			px++;
		}
		py++;
	}
}

static void	ft_clear_minimap(t_data *data)
{
	int	stride;
	int	x;
	int	y;

	stride = ft_minimap_stride(&data->mini);
	y = 0;
	while (y < data->mini_height)
	{
		x = 0;
		while (x < data->mini_width)
		{
			data->mini.addr[y * stride + x] = 0x101010;
			x++;
		}
		y++;
	}
}

static void	ft_draw_player(t_data *data)
{
	int		stride;
	int		px;
	int		py;
	int		i;
	int		j;
	int		dir_x;
	int		dir_y;

	stride = ft_minimap_stride(&data->mini);
	px = (int)(data->play.pos.x * data->mini_tile);
	py = (int)(data->play.pos.y * data->mini_tile);
	i = -1;
	while (i <= 1)
	{
		j = -1;
		while (j <= 1)
		{
			if (px + i >= 0 && px + i < data->mini_width
				&& py + j >= 0 && py + j < data->mini_height)
				data->mini.addr[(py + j) * stride + (px + i)] = 0xFF4444;
			j++;
		}
		i++;
	}
	i = 1;
	while (i < data->mini_tile * 2)
	{
		dir_x = px + (int)(data->play.dir_x * i);
		dir_y = py + (int)(data->play.dir_y * i);
		if (dir_x < 0 || dir_x >= data->mini_width
			|| dir_y < 0 || dir_y >= data->mini_height)
			break ;
		data->mini.addr[dir_y * stride + dir_x] = 0xFFAA33;
		i++;
	}
}

static void	ft_legend(t_data *data)
{
	int	text_y;

	text_y = data->mini_off_y + data->mini_height + 18;
	mlx_string_put(data->mlx, data->wind, data->mini_off_x,
		text_y, 0xFFFFFF, "WASD: move");
	mlx_string_put(data->mlx, data->wind, data->mini_off_x,
		text_y + 16, 0xFFFFFF, "Arrow keys: rotate");
	mlx_string_put(data->mlx, data->wind, data->mini_off_x,
		text_y + 32, 0xFFFFFF, "E: toggle door");
	mlx_string_put(data->mlx, data->wind, data->mini_off_x,
		text_y + 48, 0xFFFFFF, "Esc: exit");
}

static int	ft_pick_color(char tile)
{
	if (tile == 'D')
		return (DOOR_COLOR);
	if (tile > '0')
		return (0x888888);
	return (0x303030);
}

void	ft_minimap_setup(t_data *data)
{
	int	tile;
	int	width;
	int	height;

	if (!data->mlx || data->map.wide <= 0 || data->map.high <= 0)
		return ;
	tile = 12;
	while ((data->map.wide * tile > data->mapx / 3
			|| data->map.high * tile > data->mapy / 3) && tile > 4)
		tile--;
	if (tile < 4)
		tile = 4;
	width = data->map.wide * tile;
	height = data->map.high * tile;
	data->mini.img = mlx_new_image(data->mlx, width, height);
	if (!data->mini.img)
	{
		ft_error_msg("Error", "Failed to allocate minimap", FAIL);
		ft_freedom(data);
	}
	data->mini.addr = (int *)mlx_get_data_addr(data->mini.img,
			&data->mini.bpp, &data->mini.line, &data->mini.endian);
	if (!data->mini.addr)
	{
		ft_error_msg("Error", "Failed to access minimap buffer", FAIL);
		ft_freedom(data);
	}
	data->mini_tile = tile;
	data->mini_width = width;
	data->mini_height = height;
	data->mini_off_x = 20;
	data->mini_off_y = data->mapy - height - 80;
	if (data->mini_off_y < 20)
		data->mini_off_y = 20;
}

void	ft_render_minimap(t_data *data)
{
	int		x;
	int		y;
	double	vis;

	if (!data->mini.img || !data->mini.addr || data->mini_tile <= 0)
		return ;
	ft_clear_minimap(data);
	y = 0;
	while (y < data->map.high)
	{
		x = 0;
		while (x < data->map.wide)
		{
			vis = ft_tile_visibility(data, x, y, 1);
			ft_draw_tile(data, x, y,
				ft_pick_color(data->map.fl_map[y][x]), vis);
			x++;
		}
		y++;
	}
	ft_draw_player(data);
	mlx_put_image_to_window(data->mlx, data->wind,
		data->mini.img, data->mini_off_x, data->mini_off_y);
	ft_legend(data);
}

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

static void	ft_draw_tile(t_data *data, int map_x, int map_y,
		int color)
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

static void	ft_draw_coin_marker(t_data *data, t_coin *coin)
{
	int	stride;
	int	center_x;
	int	center_y;
	int	spread;
	int	x;
	int	y;

	if (!coin || !coin->alive)
		return ;
	stride = ft_minimap_stride(&data->mini);
	center_x = (int)(coin->grid_x * data->mini_tile + data->mini_tile / 2);
	center_y = (int)(coin->grid_y * data->mini_tile + data->mini_tile / 2);
	spread = data->mini_tile / 10;
	if (spread < 1)
		spread = 1;
	y = -spread;
	while (y <= spread)
	{
		x = -spread;
		while (x <= spread)
		{
			int draw_x;
			int draw_y;

			draw_x = center_x + x;
			draw_y = center_y + y;
			if (draw_x >= 0 && draw_x < data->mini_width
				&& draw_y >= 0 && draw_y < data->mini_height)
				data->mini.addr[draw_y * stride + draw_x] = 0xFFD700;
			x++;
		}
		y++;
	}
}

static void	ft_draw_coin_markers(t_data *data)
{
	int	idx;

	if (!data->coins || data->coin_alive == 0)
		return ;
	idx = 0;
	while (idx < data->coin_count)
	{
		ft_draw_coin_marker(data, &data->coins[idx]);
		idx++;
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

	if (!data->mini.img || !data->mini.addr || data->mini_tile <= 0)
		return ;
	ft_clear_minimap(data);
	y = 0;
	while (y < data->map.high)
	{
		x = 0;
		while (x < data->map.wide)
		{
			ft_draw_tile(data, x, y,
				ft_pick_color(data->map.fl_map[y][x]));
			x++;
		}
		y++;
	}
	ft_draw_coin_markers(data);
	ft_draw_player(data);
	mlx_put_image_to_window(data->mlx, data->wind,
		data->mini.img, data->mini_off_x, data->mini_off_y);
	ft_legend(data);
}

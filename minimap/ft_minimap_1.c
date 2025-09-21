/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 10:12:03 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/22 06:41:37 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_mm_draw_player_dot(t_data *d, int px, int py, int stride)
{
	int	sx;
	int	sy;
	int	x;
	int	y;

	sx = px - 1;
	if (sx < 0)
		sx = 0;
	sy = py - 1;
	if (sy < 0)
		sy = 0;
	y = sy;
	while (y <= py + 1 && y < d->mini_height)
	{
		x = sx;
		while (x <= px + 1 && x < d->mini_width)
		{
			d->mini.addr[y * stride + x] = MM_PLAYER_COLOR;
			x++;
		}
		y++;
	}
}

void	ft_mm_draw_player_ray(t_data *d, int px, int py, int stride)
{
	int	i;
	int	max;
	int	x;
	int	y;

	i = 1;
	max = d->mini_tile * 2;
	while (i < max)
	{
		x = px + (int)(d->play.dir_x * i);
		y = py + (int)(d->play.dir_y * i);
		if (x < 0 || x >= d->mini_width || y < 0 || y >= d->mini_height)
			break ;
		d->mini.addr[y * stride + x] = MM_VIEW_COLOR;
		i++;
	}
}

void	ft_draw_player(t_data *d)
{
	int	stride;
	int	px;
	int	py;

	stride = ft_minimap_stride(&d->mini);
	px = (int)(d->play.pos.x * d->mini_tile);
	py = (int)(d->play.pos.y * d->mini_tile);
	ft_mm_draw_player_dot(d, px, py, stride);
	ft_mm_draw_player_ray(d, px, py, stride);
}

void	ft_legend(t_data *data)
{
	int		text_y;
	char	*remaining;
	char	*label;

	text_y = data->mini_off_y + data->mini_height + 18;
	ft_draw_label(data, text_y, 0xFFFFFF, "WASD: move");
	ft_draw_label(data, text_y + 18, 0xFFFFFF, "Arrow keys: rotate");
	ft_draw_label(data, text_y + 36, 0xFFFFFF, "E: toggle door");
	ft_draw_label(data, text_y + 54, 0xFFFFFF, "Esc: exit");
	remaining = ft_itoa(data->coin_alive);
	if (remaining)
	{
		label = ft_strjoin("Coins left: ", remaining);
		if (label)
		{
			ft_draw_label(data, text_y - 240, 0xFFD700, label);
			free(label);
		}
		free(remaining);
	}
}

void	ft_render_minimap(t_data *data)
{
	int	x;
	int	y;

	if (!data->mini.img || !data->mini.addr || data->mini_tile <= 0)
		return ;
	ft_clear_minimap(data);
	y = 0;
	while (y < data->map.high)
	{
		x = 0;
		while (x < data->map.wide)
		{
			ft_draw_tile(data, x, y, ft_pick_color(data->map.fl_map[y][x]));
			x++;
		}
		y++;
	}
	ft_draw_coin_markers(data);
	ft_draw_player(data);
	mlx_put_image_to_window(data->mlx, data->wind, data->mini.img,
		data->mini_off_x, data->mini_off_y);
	ft_legend(data);
}

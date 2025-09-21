/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 06:02:12 by nico              #+#    #+#             */
/*   Updated: 2025/09/22 06:17:01 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_mm_coin_center(const t_data *d, const t_coin *c, int *cx, int *cy)
{
	int	half;

	half = d->mini_tile / 2;
	*cx = (int)(c->grid_x * d->mini_tile + half);
	*cy = (int)(c->grid_y * d->mini_tile + half);
}

int	ft_mm_coin_spread(const t_data *d)
{
	int	s;

	s = d->mini_tile / 10;
	if (s < 1)
		s = 1;
	return (s);
}

void	ft_draw_coin_marker(t_data *d, t_coin *coin)
{
	int	cx;
	int	cy;
	int	spread;

	if (!d || !d->mini.addr || !coin || !coin->alive)
		return ;
	ft_mm_coin_center(d, coin, &cx, &cy);
	spread = ft_mm_coin_spread(d);
	ft_mm_fill_square(d, cx, cy, spread);
}

void	ft_draw_coin_markers(t_data *data)
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

void	ft_clear_minimap(t_data *data)
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

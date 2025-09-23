/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 06:04:04 by nico              #+#    #+#             */
/*   Updated: 2025/09/23 12:41:19 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_mm_setup_guard(const t_data *d)
{
	if (!d->mlx)
		return (0);
	if (d->map.wide <= 0)
		return (0);
	if (d->map.high <= 0)
		return (0);
	return (1);
}

int	ft_mm_choose_tile(const t_data *d)
{
	int	tile;

	tile = MM_BASE_TILE;
	while ((d->map.wide * tile > d->mapx / MM_DIV_X || d->map.high
			* tile > d->mapy / MM_DIV_Y) && tile > MM_MIN_TILE)
	{
		tile--;
	}
	if (tile < MM_MIN_TILE)
		tile = MM_MIN_TILE;
	return (tile);
}

void	ft_mm_alloc_image(t_data *d, int w, int h)
{
	d->mini.img = mlx_new_image(d->mlx, w, h);
	if (!d->mini.img)
	{
		ft_error_msg("Error", "Failed to allocate minimap", FAIL);
		ft_freedom(d);
	}
	d->mini.addr = (int *)mlx_get_data_addr(d->mini.img, &d->mini.bpp,
			&d->mini.line, &d->mini.endian);
	if (!d->mini.addr)
	{
		ft_error_msg("Error", "Failed to access minimap buffer", FAIL);
		ft_freedom(d);
	}
}

void	ft_mm_set_offsets(t_data *d, int w, int h)
{
	d->mini_off_x = MM_OFF_X;
	d->mini_off_y = d->mapy - h - MM_OFF_Y_MARGIN;
	if (d->mini_off_y < MM_OFF_Y_MIN)
		d->mini_off_y = MM_OFF_Y_MIN;
	(void)w;
}

void	ft_minimap_setup(t_data *d)
{
	int	tile;
	int	w;
	int	h;

	if (!ft_mm_setup_guard(d))
		return ;
	tile = ft_mm_choose_tile(d);
	w = d->map.wide * tile;
	h = d->map.high * tile;
	ft_mm_alloc_image(d, w, h);
	d->mini_tile = tile;
	d->mini_width = w;
	d->mini_height = h;
	ft_mm_set_offsets(d, w, h);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coin_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 11:24:33 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/21 11:24:33 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_coin_sample(t_coin_frame *frame, int x, int y)
{
	if (!frame || !frame->pixels)
		return (0);
	if (x < 0 || y < 0 || x >= frame->width || y >= frame->height)
		return (0);
	return (frame->pixels[y * frame->width + x]);
}

static int	ft_blend_colour(int base, int next, double alpha)
{
	int		br;
	int		bg;
	int		bb;
	int		nr;
	int		ng;
	int		nb;

	if ((base & 0x00FFFFFF) == 0 && (next & 0x00FFFFFF) == 0)
		return (0);
	if ((base & 0x00FFFFFF) == 0)
		return (next);
	if ((next & 0x00FFFFFF) == 0)
		return (base);
	br = (base >> 16) & 0xFF;
	bg = (base >> 8) & 0xFF;
	bb = base & 0xFF;
	nr = (next >> 16) & 0xFF;
	ng = (next >> 8) & 0xFF;
	nb = next & 0xFF;
	br = (int)(br * (1.0 - alpha) + nr * alpha);
	bg = (int)(bg * (1.0 - alpha) + ng * alpha);
	bb = (int)(bb * (1.0 - alpha) + nb * alpha);
	return ((br << 16) | (bg << 8) | bb);
}

static void	ft_sort_coins(int *order, double *dist, int count)
{
	int		i;
	int		j;
	int		temp_idx;
	double	temp_dist;

	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (dist[i] < dist[j])
			{
				temp_dist = dist[i];
				dist[i] = dist[j];
				dist[j] = temp_dist;
				temp_idx = order[i];
				order[i] = order[j];
				order[j] = temp_idx;
			}
			j++;
		}
		i++;
	}
}

static void	ft_draw_coin(t_data *d, t_img *img, t_coin *coin,
				 t_coin_anim anim)
{
	double	inv_det;
	double	coin_x;
	double	coin_y;
	double	transform_x;
	double	transform_y;
	int		screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
	int		stripe;
	int		tex_x;
	int		tex_y;
	int		color_a;
	int		color_b;
	int		stride;
	t_coin_frame	*frame_a;
	t_coin_frame	*frame_b;
	int			frame_indices[2];

	frame_indices[0] = anim.frame_a % COIN_FRAME_COUNT;
	if (frame_indices[0] < 0)
		frame_indices[0] = 0;
	frame_indices[1] = anim.frame_b % COIN_FRAME_COUNT;
	if (frame_indices[1] < 0)
		frame_indices[1] = frame_indices[0];
	frame_a = &d->coin_frames[frame_indices[0]];
	frame_b = &d->coin_frames[frame_indices[1]];
	if (!frame_a->pixels || !frame_b->pixels)
		return ;
	coin_x = coin->world_x - d->play.pos.x;
	coin_y = coin->world_y - d->play.pos.y;
	inv_det = 1.0 / (d->play.plane_x * d->play.dir_y
		- d->play.dir_x * d->play.plane_y);
	transform_x = inv_det * (d->play.dir_y * coin_x - d->play.dir_x * coin_y);
	transform_y = inv_det * (-d->play.plane_y * coin_x
		+ d->play.plane_x * coin_y);
	if (transform_y <= 0.0001)
		return ;
	screen_x = (int)((d->mapx / 2.0) * (1.0 + transform_x / transform_y));
	sprite_height = (int)(fabs(d->mapy / transform_y) * COIN_SPRITE_SCALE);
	if (sprite_height < 1)
		sprite_height = 1;
	sprite_width = sprite_height;
	if (sprite_height <= 0 || sprite_width <= 0)
		return ;
	draw_start_y = -sprite_height / 2 + d->mapy / 2;
	if (draw_start_y < 0)
		draw_start_y = 0;
	draw_end_y = sprite_height / 2 + d->mapy / 2;
	if (draw_end_y >= d->mapy)
		draw_end_y = d->mapy - 1;
	draw_start_x = -sprite_width / 2 + screen_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = sprite_width / 2 + screen_x;
	if (draw_end_x >= d->mapx)
		draw_end_x = d->mapx - 1;
	stride = img->line / 4;
	stripe = draw_start_x;
	while (stripe <= draw_end_x)
	{
		tex_x = (int)(256 * (stripe - (-sprite_width / 2 + screen_x))
			* frame_a->width / sprite_width) / 256;
		if (transform_y > 0 && stripe >= 0 && stripe < d->mapx
			&& d->zbuffer && transform_y < d->zbuffer[stripe]
			&& tex_x >= 0 && tex_x < frame_a->width)
		{
			int	y;

			y = draw_start_y;
			while (y <= draw_end_y)
			{
				tex_y = ((y - (-sprite_height / 2 + d->mapy / 2)) * 256
					* frame_a->height / sprite_height) / 256;
				if (tex_y >= 0 && tex_y < frame_a->height)
				{
					color_a = ft_coin_sample(frame_a, tex_x, tex_y);
					color_b = ft_coin_sample(frame_b, tex_x, tex_y);
					color_a = ft_blend_colour(color_a, color_b, anim.alpha);
					if ((color_a & 0x00FFFFFF) != 0)
						img->addr[y * stride + stripe] = color_a;
				}
				y++;
			}
		}
		stripe++;
	}
}

void	ft_render_coins(t_data *d, t_img *img)
{
	int		*order;
	double	*dist;
	int		alive;
	int		idx;
	t_coin_anim	anim;

	if (!d || !img || d->coin_alive == 0 || !d->coins)
		return ;
	if (!d->zbuffer)
		return ;
	order = malloc(sizeof(int) * d->coin_count);
	dist = malloc(sizeof(double) * d->coin_count);
	if (!order || !dist)
	{
		free(order);
		free(dist);
		return ;
	}
	alive = 0;
	idx = 0;
	while (idx < d->coin_count)
	{
		if (d->coins[idx].alive)
		{
			double	dx;
			double	dy;

			order[alive] = idx;
			dx = d->coins[idx].world_x - d->play.pos.x;
			dy = d->coins[idx].world_y - d->play.pos.y;
			dist[alive] = dx * dx + dy * dy;
			alive++;
		}
		idx++;
	}
	if (alive == 0)
	{
		free(order);
		free(dist);
		return ;
	}
	ft_sort_coins(order, dist, alive);
	free(dist);
	anim = d->coin_anim;
	if (anim.frame_a < 0 || anim.frame_a >= COIN_FRAME_COUNT)
		anim = ft_coin_anim_state();
	idx = 0;
	while (idx < alive)
	{
		ft_draw_coin(d, img, &d->coins[order[idx]], anim);
		idx++;
	}
	free(order);
}

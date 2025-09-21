/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coin_texture_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 07:16:44 by nico              #+#    #+#             */
/*   Updated: 2025/09/22 07:17:10 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_bilin_prepare(const t_img_view *v, double u, double vv,
				t_bilin *b)
{
	double	x;
	double	y;

	x = u * (v->w - 1);
	y = vv * (v->h - 1);
	b->x0 = ft_clamp((int)floor(x), 0, v->w - 1);
	b->y0 = ft_clamp((int)floor(y), 0, v->h - 1);
	b->x1 = ft_clamp(b->x0 + 1, 0, v->w - 1);
	b->y1 = ft_clamp(b->y0 + 1, 0, v->h - 1);
	b->dx = x - (double)b->x0;
	b->dy = y - (double)b->y0;
	b->c00 = v->pixels[b->y0 * v->stride + b->x0];
	b->c10 = v->pixels[b->y0 * v->stride + b->x1];
	b->c01 = v->pixels[b->y1 * v->stride + b->x0];
	b->c11 = v->pixels[b->y1 * v->stride + b->x1];
}

static int	ft_lerp_chan(const t_bilin *b, int sh)
{
	int	top;
	int	bot;

	top = ft_lerp_channel((b->c00 >> sh) & 0xFF,
			(b->c10 >> sh) & 0xFF, b->dx);
	bot = ft_lerp_channel((b->c01 >> sh) & 0xFF,
			(b->c11 >> sh) & 0xFF, b->dx);
	return (ft_lerp_channel(top, bot, b->dy));
}

int	ft_bilinear_sample_view(const t_img_view *v, double u, double vv)
{
	t_bilin	b;
	int		r;
	int		g;
	int		bl;

	if (!v || v->w <= 0 || v->h <= 0)
		return (0);
	ft_bilin_prepare(v, u, vv, &b);
	r = ft_lerp_chan(&b, 16);
	g = ft_lerp_chan(&b, 8);
	bl = ft_lerp_chan(&b, 0);
	return ((r << 16) | (g << 8) | bl);
}


int	ft_bilinear_sample(int *pixels, int stride, int src_w, int src_h,
		double u, double v)
{
	t_img_view	view;

	if (src_w <= 0 || src_h <= 0)
		return (0);
	view.pixels = pixels;
	view.stride = stride;
	view.w = src_w;
	view.h = src_h;
	return (ft_bilinear_sample_view(&view, u, v));
}
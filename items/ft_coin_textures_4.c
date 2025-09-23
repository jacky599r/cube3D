/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coin_textures_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:49:59 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/23 13:58:51 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_lerp_channel(int a, int b, double t)
{
	return ((int)(a * (1.0 - t) + b * t));
}

void	ft_bilin_prepare(const t_img_view *src, t_bilin *b, double u, double v)
{
	double	x;
	double	y;

	x = u * (src->w - 1);
	y = v * (src->h - 1);
	b->x0 = ft_clamp((int)floor(x), 0, src->w - 1);
	b->y0 = ft_clamp((int)floor(y), 0, src->h - 1);
	b->x1 = ft_clamp(b->x0 + 1, 0, src->w - 1);
	b->y1 = ft_clamp(b->y0 + 1, 0, src->h - 1);
	b->dx = x - (double)b->x0;
	b->dy = y - (double)b->y0;
	b->c00 = src->pixels[b->y0 * src->stride + b->x0];
	b->c10 = src->pixels[b->y0 * src->stride + b->x1];
	b->c01 = src->pixels[b->y1 * src->stride + b->x0];
	b->c11 = src->pixels[b->y1 * src->stride + b->x1];
}

int	ft_bilinear_colour(const t_bilin *b, int shift)
{
	int	top;
	int	bot;

	top = ft_lerp_channel((b->c00 >> shift) & 0xFF, (b->c10 >> shift) & 0xFF,
			b->dx);
	bot = ft_lerp_channel((b->c01 >> shift) & 0xFF, (b->c11 >> shift) & 0xFF,
			b->dx);
	return (ft_lerp_channel(top, bot, b->dy));
}

int	ft_sample_colour(const t_img_view *src, double u, double v)
{
	t_bilin	b;
	int		r;
	int		g;
	int		bgr;

	if (!src || src->w <= 0 || src->h <= 0)
		return (0);
	ft_bilin_prepare(src, &b, u, v);
	r = ft_bilinear_colour(&b, 16);
	g = ft_bilinear_colour(&b, 8);
	bgr = ft_bilinear_colour(&b, 0);
	return ((r << 16) | (g << 8) | bgr);
}

void	ft_copy_exact(const t_coin_copy_ctx *ctx)
{
	int	y;
	int	x;
	int	stride;
	int	width;

	stride = ctx->src.stride;
	width = ctx->dst->width;
	y = 0;
	while (y < ctx->dst->height)
	{
		x = 0;
		while (x < width)
		{
			ctx->dst->pixels[y * width + x] = ctx->src.pixels[y * stride + x];
			x++;
		}
		y++;
	}
}

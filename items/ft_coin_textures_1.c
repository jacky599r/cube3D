/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coin_textures_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 11:12:57 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/22 07:44:48 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

static int	ft_lerp_channel(int a, int b, double t)
{
	return ((int)(a * (1.0 - t) + b * t));
}

static void	ft_bilin_prepare(const t_img_view *src, t_bilin *b, double u,
		double v)
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

static int	ft_bilinear_colour(const t_bilin *b, int shift)
{
	int	top;
	int	bot;

	top = ft_lerp_channel((b->c00 >> shift) & 0xFF, (b->c10 >> shift) & 0xFF,
			b->dx);
	bot = ft_lerp_channel((b->c01 >> shift) & 0xFF, (b->c11 >> shift) & 0xFF,
			b->dx);
	return (ft_lerp_channel(top, bot, b->dy));
}

static int	ft_sample_colour(const t_img_view *src, double u, double v)
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

static void	ft_copy_exact(const t_coin_copy_ctx *ctx)
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

static void	ft_copy_scaled(const t_coin_copy_ctx *ctx)
{
	int		y;
	int		x;
	double	u;
	double	v;

	y = 0;
	while (y < ctx->dst->height)
	{
		v = (ctx->dst->height <= 1) ? 0.0 : (double)y
			/ (double)(ctx->dst->height - 1);
		x = 0;
		while (x < ctx->dst->width)
		{
			u = (ctx->dst->width <= 1) ? 0.0 : (double)x
				/ (double)(ctx->dst->width - 1);
			ctx->dst->pixels[y * ctx->dst->width
				+ x] = ft_sample_colour(&ctx->src, u, v);
			x++;
		}
		y++;
	}
}

static void	ft_copy_coin_pixels(const t_coin_copy_ctx *ctx)
{
	if (!ctx || !ctx->dst || !ctx->dst->pixels)
		return ;
	if (ctx->dst->width == ctx->src.w && ctx->dst->height == ctx->src.h)
		ft_copy_exact(ctx);
	else
		ft_copy_scaled(ctx);
}

static int	ft_alloc_coin_frame(t_data *data, int index, int width, int height)
{
	int	dst_w;
	int	dst_h;

	dst_w = width;
	dst_h = height;
	if (dst_w <= 0)
		dst_w = 1;
	if (dst_h <= 0)
		dst_h = 1;
	data->coin_frames[index].width = dst_w;
	data->coin_frames[index].height = dst_h;
	data->coin_frames[index].pixels = ft_calloc(dst_w * dst_h, sizeof(int));
	if (!data->coin_frames[index].pixels)
	{
		ft_error_msg("Error", "Coin frame allocation failed", FAIL);
		ft_freedom(data);
		return (FAIL);
	}
	return (PASS);
}

static void	ft_coin_texture_path(int idx, char *buffer, size_t size)
{
	snprintf(buffer, size, "textures/coins/Coin_%d.xpm", idx + 1);
}

static int	ft_coin_img_error(t_data *data, char *path, t_img *img)
{
	ft_error_msg("Error", path, FAIL);
	if (img && img->img)
		mlx_destroy_image(data->mlx, img->img);
	ft_freedom(data);
	return (FAIL);
}

static int	ft_coin_load_frame(t_data *data, int idx)
{
	t_coin_load_ctx	ctx;
	t_coin_copy_ctx	copy;

	ft_coin_texture_path(idx, ctx.path, sizeof(ctx.path));
	ft_img_init(&ctx.img);
	ctx.src.w = 0;
	ctx.src.h = 0;
	ctx.img.img = mlx_xpm_file_to_image(data->mlx, ctx.path, &ctx.src.w,
			&ctx.src.h);
	if (!ctx.img.img)
		return (ft_coin_img_error(data, ctx.path, &ctx.img));
	ctx.img.addr = (int *)mlx_get_data_addr(ctx.img.img, &ctx.img.bpp,
			&ctx.img.line, &ctx.img.endian);
	ctx.src.pixels = ctx.img.addr;
	ctx.src.stride = ctx.img.line / 4;
	ctx.dst = &data->coin_frames[idx];
	ctx.dst_w = (COIN_TEXTURE_SIZE > 0) ? COIN_TEXTURE_SIZE : ctx.src.w;
	ctx.dst_h = (COIN_TEXTURE_SIZE > 0) ? COIN_TEXTURE_SIZE : ctx.src.h;
	if (ft_alloc_coin_frame(data, idx, ctx.dst_w, ctx.dst_h) == FAIL)
	{
		mlx_destroy_image(data->mlx, ctx.img.img);
		return (FAIL);
	}
	copy.src = ctx.src;
	copy.dst = ctx.dst;
	ft_copy_coin_pixels(&copy);
	mlx_destroy_image(data->mlx, ctx.img.img);
	return (PASS);
}

void	ft_load_coin_textures(t_data *data)
{
	int	idx;

	if (!data || !data->mlx)
		return ;
	idx = 0;
	while (idx < COIN_FRAME_COUNT)
	{
		if (ft_coin_load_frame(data, idx) == FAIL)
			return ;
		idx++;
	}
}

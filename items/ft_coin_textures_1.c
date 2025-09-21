/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coin_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 11:12:57 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/22 07:18:49 by nico             ###   ########.fr       */
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

// static int	ft_bilinear_sample(int *pixels, int stride, int src_w, int src_h,
// 		double u, double v)
// {
// 	double	x;
// 	double	y;
// 	int		x0;
// 	int		y0;
// 	int		x1;
// 	int		y1;
// 	double	dx;
// 	double	dy;
// 	int		c00;
// 	int		c10;
// 	int		c01;
// 	int		c11;
// 	int		r_top;
// 	int		r_bot;
// 	int		r;
// 	int		g_top;
// 	int		g_bot;
// 	int		g;
// 	int		b_top;
// 	int		b_bot;
// 	int		b;

// 	if (src_w <= 0 || src_h <= 0)
// 		return (0);
// 	x = u * (src_w - 1);
// 	y = v * (src_h - 1);
// 	x0 = ft_clamp((int)floor(x), 0, src_w - 1);
// 	y0 = ft_clamp((int)floor(y), 0, src_h - 1);
// 	x1 = ft_clamp(x0 + 1, 0, src_w - 1);
// 	y1 = ft_clamp(y0 + 1, 0, src_h - 1);
// 	dx = x - x0;
// 	dy = y - y0;
// 	c00 = pixels[y0 * stride + x0];
// 	c10 = pixels[y0 * stride + x1];
// 	c01 = pixels[y1 * stride + x0];
// 	c11 = pixels[y1 * stride + x1];
// 	r_top = ft_lerp_channel((c00 >> 16) & 0xFF, (c10 >> 16) & 0xFF, dx);
// 	r_bot = ft_lerp_channel((c01 >> 16) & 0xFF, (c11 >> 16) & 0xFF, dx);
// 	r = ft_lerp_channel(r_top, r_bot, dy);
// 	g_top = ft_lerp_channel((c00 >> 8) & 0xFF, (c10 >> 8) & 0xFF, dx);
// 	g_bot = ft_lerp_channel((c01 >> 8) & 0xFF, (c11 >> 8) & 0xFF, dx);
// 	g = ft_lerp_channel(g_top, g_bot, dy);
// 	b_top = ft_lerp_channel(c00 & 0xFF, c10 & 0xFF, dx);
// 	b_bot = ft_lerp_channel(c01 & 0xFF, c11 & 0xFF, dx);
// 	b = ft_lerp_channel(b_top, b_bot, dy);
// 	return ((r << 16) | (g << 8) | b);
// }

static void	ft_copy_coin_pixels(t_data *data, t_img *img, int index,
		int stride, int src_w, int src_h)
{
	int		x;
	int		y;
	int		dst_w;
	int		dst_h;
	double	u;
	double	v;

	dst_w = data->coin_frames[index].width;
	dst_h = data->coin_frames[index].height;
	if (dst_w <= 0 || dst_h <= 0)
		return ;
	if (dst_w == src_w && dst_h == src_h)
	{
		y = 0;
		while (y < dst_h)
		{
			x = 0;
			while (x < dst_w)
			{
				data->coin_frames[index].pixels[y * dst_w + x]
					= img->addr[y * stride + x];
				x++;
			}
			y++;
		}
		return ;
	}
	y = 0;
	while (y < dst_h)
	{
		v = (dst_h == 1) ? 0.0 : (double)y / (double)(dst_h - 1);
		x = 0;
		while (x < dst_w)
		{
			u = (dst_w == 1) ? 0.0 : (double)x / (double)(dst_w - 1);
			data->coin_frames[index].pixels[y * dst_w + x]
				= ft_bilinear_sample(img->addr, stride, src_w, src_h, u, v);
			x++;
		}
		y++;
	}
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

void	ft_load_coin_textures(t_data *data)
{
	t_img	img;
	int		width;
	int		height;
	int		dst_w;
	int		dst_h;
	char	path[128];
	int		stride;
	int		idx;

	if (!data || !data->mlx)
		return ;
	idx = 0;
	while (idx < COIN_FRAME_COUNT)
	{
		ft_coin_texture_path(idx, path, sizeof(path));
		width = 0;
		height = 0;
		ft_img_init(&img);
		img.img = mlx_xpm_file_to_image(data->mlx, path, &width, &height);
		if (!img.img)
		{
			ft_error_msg("Error", path, FAIL);
			ft_freedom(data);
			return ;
		}
		img.addr = (int *)mlx_get_data_addr(img.img, &img.bpp, &img.line,
				&img.endian);
		stride = img.line / 4;
		dst_w = (COIN_TEXTURE_SIZE > 0) ? COIN_TEXTURE_SIZE : width;
		dst_h = (COIN_TEXTURE_SIZE > 0) ? COIN_TEXTURE_SIZE : height;
		if (ft_alloc_coin_frame(data, idx, dst_w, dst_h) == FAIL)
		{
			mlx_destroy_image(data->mlx, img.img);
			return ;
		}
		ft_copy_coin_pixels(data, &img, idx, stride, width, height);
		mlx_destroy_image(data->mlx, img.img);
		idx++;
	}
}

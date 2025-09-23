/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coin_textures_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 11:12:57 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/23 14:01:30 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_copy_scaled(const t_coin_copy_ctx *ctx)
{
	int		y;
	int		x;
	double	u;
	double	v;

	y = 0;
	while (y < ctx->dst->height)
	{
		v = 0.0;
		if (ctx->dst->height > 1)
			v = (double)y / (double)(ctx->dst->height - 1);
		x = 0;
		while (x < ctx->dst->width)
		{
			u = 0.0;
			if (ctx->dst->width > 1)
				u = (double)x / (double)(ctx->dst->width - 1);
			ctx->dst->pixels[y * ctx->dst->width + x]
				= ft_sample_colour(&ctx->src, u, v);
			x++;
		}
		y++;
	}
}

void	ft_copy_coin_pixels(const t_coin_copy_ctx *ctx)
{
	if (!ctx || !ctx->dst || !ctx->dst->pixels)
		return ;
	if (ctx->dst->width == ctx->src.w && ctx->dst->height == ctx->src.h)
		ft_copy_exact(ctx);
	else
		ft_copy_scaled(ctx);
}

int	ft_alloc_coin_frame(t_data *data, int index, int width, int height)
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

void	ft_coin_texture_path(int idx, char *buffer, size_t size)
{
	char	num[12];

	if (!buffer || size == 0)
		return ;
	buffer[0] = '\0';
	if (idx < 0)
		idx = 0;
	if (!ft_uint_to_str((unsigned int)(idx + 1), num, sizeof(num)))
		return ;
	if (ft_strlcpy(buffer, COIN_PATH_PREFIX, size) >= size)
		return ;
	if (ft_strlcat(buffer, num, size) >= size)
		return ;
	(void)ft_strlcat(buffer, COIN_PATH_SUFFIX, size);
}

int	ft_coin_img_error(t_data *data, char *path, t_img *img)
{
	ft_error_msg("Error", path, FAIL);
	if (img && img->img)
		mlx_destroy_image(data->mlx, img->img);
	ft_freedom(data);
	return (FAIL);
}

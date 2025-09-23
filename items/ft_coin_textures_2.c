/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coin_textures_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:27:29 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/23 13:57:52 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_coin_open_img(t_data *d, int idx, t_coin_load_ctx *c)
{
	ft_coin_texture_path(idx, c->path, sizeof(c->path));
	ft_img_init(&c->img);
	c->src.w = 0;
	c->src.h = 0;
	c->img.img = mlx_xpm_file_to_image(d->mlx, c->path, &c->src.w, &c->src.h);
	if (!c->img.img)
		return (ft_coin_img_error(d, c->path, &c->img));
	c->img.addr = (int *)mlx_get_data_addr(c->img.img, &c->img.bpp,
			&c->img.line, &c->img.endian);
	c->src.pixels = c->img.addr;
	c->src.stride = c->img.line / 4;
	return (PASS);
}

static void	ft_coin_choose_dst(t_coin_load_ctx *c)
{
	if (COIN_TEXTURE_SIZE > 0)
	{
		c->dst_w = COIN_TEXTURE_SIZE;
		c->dst_h = COIN_TEXTURE_SIZE;
	}
	else
	{
		c->dst_w = c->src.w;
		c->dst_h = c->src.h;
	}
}

static int	ft_coin_alloc_dst(t_data *d, t_coin_load_ctx *c, int idx)
{
	c->dst = &d->coin_frames[idx];
	if (ft_alloc_coin_frame(d, idx, c->dst_w, c->dst_h) == FAIL)
		return (FAIL);
	return (PASS);
}

static int	ft_coin_load_frame(t_data *d, int idx)
{
	t_coin_load_ctx	ctx;
	t_coin_copy_ctx	copy;

	if (ft_coin_open_img(d, idx, &ctx) == FAIL)
		return (FAIL);
	ft_coin_choose_dst(&ctx);
	if (ft_coin_alloc_dst(d, &ctx, idx) == FAIL)
	{
		mlx_destroy_image(d->mlx, ctx.img.img);
		return (FAIL);
	}
	copy.src = ctx.src;
	copy.dst = ctx.dst;
	ft_copy_coin_pixels(&copy);
	mlx_destroy_image(d->mlx, ctx.img.img);
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

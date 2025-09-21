/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coin_render_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 05:07:34 by nico              #+#    #+#             */
/*   Updated: 2025/09/22 05:22:14 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_coin_bounds(const t_data *d, t_img *img, t_coin_spr *s)
{
	s->sy = -s->h / 2 + d->mapy / 2;
	if (s->sy < 0)
		s->sy = 0;
	s->ey = s->h / 2 + d->mapy / 2;
	if (s->ey >= d->mapy)
		s->ey = d->mapy - 1;
	s->sx = -s->w / 2 + s->screen_x;
	if (s->sx < 0)
		s->sx = 0;
	s->ex = s->w / 2 + s->screen_x;
	if (s->ex >= d->mapx)
		s->ex = d->mapx - 1;
	s->left_x = -s->w / 2 + s->screen_x;
	s->base_y = -s->h / 2 + d->mapy / 2;
	s->inv_w = 1.0 / (double)s->w;
	s->inv_h = 1.0 / (double)s->h;
	s->stride = img->line / 4;
}

void	ft_coin_draw_column(t_img *img, const t_coin_spr *s,
		const t_coin_tex *t, int stripe)
{
	int	y;
	int	tx;
	int	ty;
	int	color;

	tx = (int)(((stripe - s->left_x) * t->tw) * s->inv_w);
	if (tx < 0 || tx >= t->tw)
		return ;
	y = s->sy;
	while (y <= s->ey)
	{
		ty = (int)(((y - s->base_y) * t->th) * s->inv_h);
		if (ty >= 0 && ty < t->th)
		{
			color = ft_blend_colour(ft_coin_sample(t->a, tx, ty),
					ft_coin_sample(t->b, tx, ty), t->alpha);
			if ((color & 0x00FFFFFF) != 0)
				img->addr[y * s->stride + stripe] = color;
		}
		y++;
	}
}

void	ft_coin_render(t_data *d, t_img *img, const t_coin_spr *s,
		const t_coin_tex *t)
{
	int	stripe;

	stripe = s->sx;
	while (stripe <= s->ex)
	{
		if (s->ty > 0 && stripe >= 0 && stripe < d->mapx && d->zbuffer
			&& s->ty < d->zbuffer[stripe])
			ft_coin_draw_column(img, s, t, stripe);
		stripe++;
	}
}

void	ft_draw_coin(t_data *d, t_img *img, t_coin *coin, t_coin_anim anim)
{
	t_coin_tex	tex;
	t_coin_spr	spr;

	if (!ft_coin_pick_frames(d, anim, &tex))
		return ;
	if (!ft_coin_transform(d, coin, &spr))
		return ;
	ft_coin_bounds(d, img, &spr);
	ft_coin_render(d, img, &spr, &tex);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coin_render_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 05:07:12 by nico              #+#    #+#             */
/*   Updated: 2025/09/22 05:13:43 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_coin_sample(const t_coin_frame *frame, int x, int y)
{
	if (!frame || !frame->pixels)
		return (0);
	if (x < 0 || y < 0 || x >= frame->width || y >= frame->height)
		return (0);
	return (frame->pixels[y * frame->width + x]);
}

int	ft_blend_colour(int base, int next, double alpha)
{
	int	br;
	int	bg;
	int	bb;

	if ((base & 0x00FFFFFF) == 0 && (next & 0x00FFFFFF) == 0)
		return (0);
	if ((base & 0x00FFFFFF) == 0)
		return (next);
	if ((next & 0x00FFFFFF) == 0)
		return (base);
	br = (base >> 16) & 0xFF;
	bg = (base >> 8) & 0xFF;
	bb = base & 0xFF;
	br = (int)(br * (1.0 - alpha) + ((next >> 16) & 0xFF) * alpha);
	bg = (int)(bg * (1.0 - alpha) + ((next >> 8) & 0xFF) * alpha);
	bb = (int)(bb * (1.0 - alpha) + (next & 0xFF) * alpha);
	return ((br << 16) | (bg << 8) | bb);
}

void	ft_sort_coins(int *order, double *dist, int count)
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

int	ft_coin_pick_frames(const t_data *d, t_coin_anim anim, t_coin_tex *t)
{
	int	i0;
	int	i1;

	i0 = anim.frame_a % COIN_FRAME_COUNT;
	i1 = anim.frame_b % COIN_FRAME_COUNT;
	if (i0 < 0)
		i0 = 0;
	if (i1 < 0)
		i1 = i0;
	t->a = &d->coin_frames[i0];
	t->b = &d->coin_frames[i1];
	if (!t->a->pixels || !t->b->pixels)
		return (0);
	t->tw = t->a->width;
	t->th = t->a->height;
	t->alpha = anim.alpha;
	return (1);
}

int	ft_coin_transform(const t_data *d, const t_coin *c, t_coin_spr *s)
{
	double	cx;
	double	cy;
	double	inv;

	cx = c->world_x - d->play.pos.x;
	cy = c->world_y - d->play.pos.y;
	inv = 1.0 / (d->play.plane_x * d->play.dir_y - d->play.dir_x
			* d->play.plane_y);
	s->tx = inv * (d->play.dir_y * cx - d->play.dir_x * cy);
	s->ty = inv * (-d->play.plane_y * cx + d->play.plane_x * cy);
	if (s->ty <= 0.0001)
		return (0);
	s->screen_x = (int)((d->mapx / 2.0) * (1.0 + s->tx / s->ty));
	s->h = (int)(fabs(d->mapy / s->ty) * COIN_SPRITE_SCALE);
	if (s->h < 1)
		s->h = 1;
	s->w = s->h;
	return (s->w > 0 && s->h > 0);
}

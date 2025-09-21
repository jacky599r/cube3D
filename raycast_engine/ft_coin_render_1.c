/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coin_render_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 11:24:33 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/22 05:22:30 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_coins_tmp_alloc(const t_data *d, int **order, double **dist)
{
	*order = malloc(sizeof(int) * d->coin_count);
	*dist = malloc(sizeof(double) * d->coin_count);
	if (!*order || !*dist)
	{
		free(*order);
		free(*dist);
		*order = NULL;
		*dist = NULL;
		return (0);
	}
	return (1);
}

int	ft_coins_gather(const t_data *d, int *order, double *dist)
{
	int		i;
	int		alive;
	double	dx;
	double	dy;

	i = 0;
	alive = 0;
	while (i < d->coin_count)
	{
		if (d->coins[i].alive)
		{
			order[alive] = i;
			dx = d->coins[i].world_x - d->play.pos.x;
			dy = d->coins[i].world_y - d->play.pos.y;
			dist[alive] = dx * dx + dy * dy;
			alive++;
		}
		i++;
	}
	return (alive);
}

t_coin_anim	ft_coins_anim(const t_data *d)
{
	t_coin_anim	a;

	a = d->coin_anim;
	if (a.frame_a < 0 || a.frame_a >= COIN_FRAME_COUNT)
		a = ft_coin_anim_state();
	return (a);
}

void	ft_coins_draw(const t_data *d, t_img *img, t_coin_batch b,
		t_coin_anim anim)
{
	int	i;

	i = 0;
	while (i < b.alive)
	{
		ft_draw_coin((t_data *)d, img, &d->coins[b.order[i]], anim);
		i++;
	}
}

void	ft_render_coins(t_data *d, t_img *img)
{
	int				*order;
	double			*dist;
	t_coin_batch	b;
	t_coin_anim		anim;

	if (!d || !img || !d->zbuffer || !d->coins || d->coin_alive == 0)
		return ;
	if (!ft_coins_tmp_alloc(d, &order, &dist))
		return ;
	b.alive = ft_coins_gather(d, order, dist);
	if (b.alive == 0)
	{
		free(order);
		free(dist);
		return ;
	}
	ft_sort_coins(order, dist, b.alive);
	free(dist);
	b.order = order;
	anim = ft_coins_anim(d);
	ft_coins_draw(d, img, b, anim);
	free(order);
}

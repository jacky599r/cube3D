/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:13:59 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/19 13:14:08 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_dda_prep(t_track *t, t_play *p)
{
	if (t->dir.x < 0)
	{
		t->stp.x = -1;
		t->sid.x = (p->pos.x - t->map.x) * t->dlt.x;
	}
	else
	{
		t->stp.x = 1;
		t->sid.x = (t->map.x + 1.0 - p->pos.x) * t->dlt.x;
	}
	if (t->dir.y < 0)
	{
		t->stp.y = -1;
		t->sid.y = (p->pos.y - t->map.y) * t->dlt.y;
	}
	else
	{
		t->stp.y = 1;
		t->sid.y = (t->map.y + 1.0 - p->pos.y) * t->dlt.y;
	}
	return (0);
}

int	ft_ray_check(t_data *d, t_track *t)
{
	if (t->map.y < 0.25 || t->map.x < 0.25 || t->map.y > d->map.high - 0.25
		|| t->map.x > d->map.wide - 1.25)
		return (1);
	if (d->map.fl_map[t->map.y][t->map.x] > '0')
		return (2);
	return (0);
}

void	ft_line_len(t_data *d, t_track *t, t_play *p)
{
    if (t->side == 0)
        t->wall = ((double)t->map.x - p->pos.x + (1 - t->stp.x) * 0.5) / t->dir.x;
    else
        t->wall = ((double)t->map.y - p->pos.y + (1 - t->stp.y) * 0.5) / t->dir.y;

    t->high = (int)(d->mapy / t->wall);
    t->strt = -t->high / 2 + d->mapy / 2;
    if (t->strt < 0) t->strt = 0;
    t->end  =  t->high / 2 + d->mapy / 2;
    if (t->end >= d->mapy) t->end = d->mapy - 1;

    if (t->side == 0) t->walx = p->pos.y + t->wall * t->dir.y;
    else              t->walx = p->pos.x + t->wall * t->dir.x;
    t->walx -= floor(t->walx);
}

void	ft_dda_algo(t_data *d, t_track *t, t_play *p)
{
    int cross;
	int check;
	
	cross = ft_dda_prep(t, p);
    while (cross == 0)
    {
        if (t->sid.x < t->sid.y)
		{ 
			t->sid.x += t->dlt.x;
			t->map.x += t->stp.x;
			t->side = 0;
		}
        else
		{
			t->sid.y += t->dlt.y;
			t->map.y += t->stp.y;
			t->side = 1;
		}
        check = ft_ray_check(d, t);
        if (check == 1) 
			break;
        else if (check == 2)
			cross = 1;
    }
	ft_line_len(d, t, p);
}
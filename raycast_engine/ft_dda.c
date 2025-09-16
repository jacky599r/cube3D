/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:47:04 by nico              #+#    #+#             */
/*   Updated: 2025/09/16 17:19:15 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_dda_prep(t_track *t, t_play *p)
{
	if (t->ray_dir_x < 0)
	{
		t->step_x = -1;
		t->side_dist_x = (p->pos.x - t->map_x) * t->delta_dist_x;
	}
	else
	{
		t->step_x = 1;
		t->side_dist_x = (t->map_x + 1.0 - p->pos.x) * t->delta_dist_x;
	}
	if (t->ray_dir_y < 0)
	{
		t->step_y = -1;
		t->side_dist_y = (p->pos.y - t->map_y) * t->delta_dist_y;
	}
	else
	{
		t->step_y = 1;
		t->side_dist_y = (t->map_y + 1.0 - p->pos.y) * t->delta_dist_y;
	}
	return (0);
}

int	ft_ray_check(t_data *d, t_track *t)
{
	if (t->map_y < 0.25 || t->map_x < 0.25 || t->map_y > d->map.high - 0.25
		|| t->map_x > d->map.wide - 1.25)
		return (1);
        if (d->map.og_map[t->map_y][t->map_x] > '0')
		return (2);
	return (0);
}

void	ft_line_len(t_data *d, t_track *t, t_play *p)
{
	if (t->side == 0)
                t->perp_wall_dist = (t->side_dist_x - t->delta_dist_x);
	else
		t->perp_wall_dist = (t->side_dist_y - t->delta_dist_y);
	t->line_height = (int)(d->mapy / t->perp_wall_dist);
	t->draw_start = -(t->line_height) / 2 + d->mapy / 2;
	if (t->draw_start < 0)
		t->draw_start = 0;
	t->draw_end = t->line_height / 2 + d->mapy / 2;
	if (t->draw_end >= d->mapy)
		t->draw_end = d->mapy - 1;
	if (t->side == 0)
                t->wall_x = p->pos.y + t->perp_wall_dist * t->ray_dir_y;
	else
		t->wall_x = p->pos.x + t->perp_wall_dist * t->ray_dir_x;
	t->wall_x -= floor(t->wall_x);
}

void	ft_dda_algo(t_data *d, t_track *t, t_play *p)
{
	int cross;
	int check;

        cross = ft_dda_prep(t, p);
	while (cross == 0)
	{
		if (t->side_dist_x < t->side_dist_y)
		{
			t->side_dist_x += t->delta_dist_x;
			t->map_x += t->step_x;
			t->side = 0;
		}
		else
		{
			t->side_dist_y += t->delta_dist_y;
			t->map_y += t->step_y;
			t->side = 1;
		}
		check = ft_ray_check(d, t);
		if (check == 1)
			break ;
		else if (check == 2)
			cross = 1;
	}
        ft_line_len(d, t, p);
}
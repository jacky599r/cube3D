/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 06:30:23 by nico              #+#    #+#             */
/*   Updated: 2025/09/23 13:52:26 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_coins_alloc(t_data *d)
{
	size_t	cap;

	if (!d || !d->map.fl_map)
		return (FAIL);
	ft_reset_coin_list(d);
	cap = (size_t)d->map.high * (size_t)d->map.wide;
	d->coin_capacity = (int)cap;
	d->coins = ft_calloc(d->coin_capacity, sizeof(t_coin));
	if (!d->coins)
	{
		ft_error_msg("Error", "Coin allocation failed", FAIL);
		ft_freedom(d);
		return (FAIL);
	}
	return (PASS);
}

static void	ft_try_spawn_coin(t_data *d, int x, int y, const t_int *p)
{
	if (!ft_is_coin_candidate(d->map.fl_map[y][x]))
		return ;
	if (x == p->x && y == p->y)
		return ;
	d->coins[d->coin_count].grid_x = x;
	d->coins[d->coin_count].grid_y = y;
	d->coins[d->coin_count].world_x = (double)x + 0.5;
	d->coins[d->coin_count].world_y = (double)y + 0.5;
	d->coins[d->coin_count].alive = true;
	d->coin_count++;
}

static void	ft_scan_map_spawn(t_data *d, const t_int *p)
{
	int	y;
	int	x;

	y = 0;
	while (y < d->map.high)
	{
		x = 0;
		while (x < d->map.wide)
		{
			ft_try_spawn_coin(d, x, y, p);
			x++;
		}
		y++;
	}
}

int	ft_spawn_coins(t_data *d)
{
	t_int	p;

	if (!d || !d->map.fl_map)
		return (FAIL);
	if (ft_coins_alloc(d) != PASS)
		return (FAIL);
	p.x = (int)d->play.pos.x;
	p.y = (int)d->play.pos.y;
	ft_scan_map_spawn(d, &p);
	d->coin_alive = d->coin_count;
	return (PASS);
}

int	ft_clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

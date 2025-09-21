/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhook_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 06:45:24 by nico              #+#    #+#             */
/*   Updated: 2025/09/22 07:05:47 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_handle_move_keys(t_data *d)
{
	int	changed;

	changed = 0;
	if (d->key.up == 1)
		changed |= ft_move_player(d, UP, 0.0, 0.0);
	if (d->key.down == 1)
		changed |= ft_move_player(d, DOWN, 0.0, 0.0);
	if (d->key.left == 1)
		changed |= ft_move_player(d, LEFT, 0.0, 0.0);
	if (d->key.right == 1)
		changed |= ft_move_player(d, RIGHT, 0.0, 0.0);
	return (changed);
}

static int	ft_handle_rotation(t_data *d)
{
	int	changed;

	changed = 0;
	if (d->key.l_arw == 1)
		changed |= ft_rotate_player(d, ROT_L);
	if (d->key.r_arw == 1)
		changed |= ft_rotate_player(d, ROT_R);
	changed |= ft_rotate_player_mouse(d);
	return (changed);
}

static int	ft_handle_use(t_data *d)
{
	int	changed;

	changed = 0;
	if (d->key.use == 1)
	{
		changed |= ft_interact_door(d);
		d->key.use = 0;
	}
	return (changed);
}

static int	ft_update_coin_state(t_data *d, int changed)
{
	t_coin_anim	next_anim;

	next_anim = ft_coin_anim_state();
	if (ft_coin_update_anim(d, next_anim))
		changed = 1;
	if (changed != 0)
		changed |= ft_collect_coin(d, 0);
	return (changed);
}

void	ft_player_action(t_data *d)
{
	int	changed;

	changed = 0;
	changed |= ft_handle_move_keys(d);
	changed |= ft_handle_rotation(d);
	changed |= ft_handle_use(d);
	changed = ft_update_coin_state(d, changed);
	d->play.check = changed;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:09:31 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/19 15:26:43 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_raycast_check(t_data *d)
{
	ft_player_action(d);
	if (d->play.check == 0)
		return (0);
	ft_raycasting(d);
	return (0);
}

int	ft_terminate_game(t_data *d)
{
	ft_freedom(d);
	ft_print_exit();
	exit(EXIT_FAILURE);
}

int	ft_key_press(int keycode, t_data *d)
{
	if (keycode == ESC_KEY)
		ft_terminate_game(d);
	if (keycode == LEFT_KEY)
		d->key.l_arw = 1;
	if (keycode == RIGHT_KEY)
		d->key.r_arw = 1;
	if (keycode == W_KEY)
		d->key.up = 1;
	if (keycode == S_KEY)
		d->key.down = 1;
	if (keycode == A_KEY)
		d->key.left = 1;
	if (keycode == D_KEY)
		d->key.right = 1;
	if (keycode == E_KEY)
		d->key.use = 1;
	return (0);
}

int	ft_key_release(int keycode, t_data *d)
{
	if (keycode == LEFT_KEY)
		d->key.l_arw = 0;
	if (keycode == RIGHT_KEY)
		d->key.r_arw = 0;
	if (keycode == W_KEY)
		d->key.up = 0;
	if (keycode == S_KEY)
		d->key.down = 0;
	if (keycode == A_KEY)
		d->key.left = 0;
	if (keycode == D_KEY)
		d->key.right = 0;
	if (keycode == E_KEY)
		d->key.use = 0;
	return (0);
}

void	ft_player_action(t_data *d)
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
	if (d->key.l_arw == 1)
		changed |= ft_rotate_player(d, ROT_L);
	if (d->key.r_arw == 1)
		changed |= ft_rotate_player(d, ROT_R);
	if (d->key.use == 1)
	{
		changed |= ft_interact_door(d);
		d->key.use = 0;
	}
	d->play.check = changed;
}

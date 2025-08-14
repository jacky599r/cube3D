/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:39:52 by nico              #+#    #+#             */
/*   Updated: 2025/08/14 19:42:57 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_terminate_game(t_data *d)
{
	if (d->wind)
		mlx_destroy_window(d->mlx, d->wind);
	if (d->mlx)
	{
		mlx_destroy_display(d->mlx);
		free(d->mlx);
	}
	ft_freedom(d);
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
	return (0);
}

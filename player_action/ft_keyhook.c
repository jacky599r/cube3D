/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:39:52 by nico              #+#    #+#             */
/*   Updated: 2025/09/18 13:25:32 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_terminate_game(t_data *d)
{
	ft_freedom(d);
	exit(EXIT_FAILURE);
}

int	ft_key_press(int keycode, t_data *d)
{
	printf("Map coordinates:(%f - %f)\n", d->play.pos.x, d->play.pos.y);
	printf("Player cell: (x = %d, y = %d)\n", (int)d->play.pos.x,
		(int)d->play.pos.y);
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

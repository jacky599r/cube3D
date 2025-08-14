/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:39:59 by nico              #+#    #+#             */
/*   Updated: 2025/08/14 20:57:04 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_position_check(t_data *d, double mve_x, double mve_y)
{
	(void)d; // Suppress unused parameter warning
	// Simple boundary check - can be enhanced with wall collision detection
	if (mve_x < 0 || mve_y < 0)
		return (FAIL);
	// Add more sophisticated collision detection here if needed
	return (PASS);
}

int	ft_move_check(t_data *d, double mve_x, double mve_y)
{
	int	check;

	check = 0;
	if (ft_position_check(d, mve_x, d->play.pos.y) == PASS)
	{
		d->play.pos.x = mve_x;
		check += 1;
	}
	if (ft_position_check(d, d->play.pos.x, mve_y) == PASS)
	{
		d->play.pos.y = mve_y;
		check += 1;
	}
	if (check > 0)
		return (1);
	return (0);
}

int	ft_move_player(t_data *d, int key)
{
	double	mve_x;
	double	mve_y;

	mve_x = d->play.pos.x;  // Initialize with current position
	mve_y = d->play.pos.y;  // Initialize with current position

	if (key == UP)
	{
		mve_x = d->play.pos.x + d->play.dir_x * MOVE_SPEED;
		mve_y = d->play.pos.y + d->play.dir_y * MOVE_SPEED;
	}
	else if (key == DOWN)
	{
		mve_x = d->play.pos.x - d->play.dir_x * MOVE_SPEED;
		mve_y = d->play.pos.y - d->play.dir_y * MOVE_SPEED;
	}
	else if (key == LEFT)
	{
		mve_x = d->play.pos.x + d->play.dir_y * MOVE_SPEED;
		mve_y = d->play.pos.y - d->play.dir_x * MOVE_SPEED;
	}
	else if (key == RIGHT)
	{
		mve_x = d->play.pos.x - d->play.dir_y * MOVE_SPEED;
		mve_y = d->play.pos.y + d->play.dir_x * MOVE_SPEED;
	}
	return (ft_move_check(d, mve_x, mve_y));
}

int	ft_rotdir(int key)
{
	if (key == ROT_L)
		return (-1);
	return (1);
}

int	ft_rotate_player(t_data *d, int key)
{
	double	ang;
	double	c;
	double	s;
	double	tmp;

	ang = ROT_SPEED * ft_rotdir(key);
	c = cos(ang);
	s = sin(ang);
	if (ang == 0.0)
		return (0);
	tmp = d->play.dir_x;
	d->play.dir_x = d->play.dir_x * c - d->play.dir_y * s;
	d->play.dir_y = tmp * s + d->play.dir_y * c;
	tmp = d->play.plane_x;
	d->play.plane_x = d->play.plane_x * c - d->play.plane_y * s;
	d->play.plane_y = tmp * s + d->play.plane_y * c;
	return (1);
}

void	ft_player_action(t_data *d)
{
	int a;

	a = 0;
	if (d->key.up == 1)
		a = ft_move_player(d, UP);
	if (d->key.down == 1)
		a = ft_move_player(d, DOWN);
	if (d->key.left == 1)
		a = ft_move_player(d, LEFT);
	if (d->key.right == 1)
		a = ft_move_player(d, RIGHT);
	if (d->key.l_arw == 1)
		a = ft_rotate_player(d, ROT_L);
	if (d->key.r_arw == 1)
		a = ft_rotate_player(d, ROT_R);
	d->play.check += a;
}
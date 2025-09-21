/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movment_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:11:50 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/22 07:04:15 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_is_solid_tile(t_data *d, double x, double y)
{
	int		grid_x;
	int		grid_y;
	char	tile;

	if (x < 0.0 || y < 0.0)
		return (FAIL);
	grid_x = (int)x;
	grid_y = (int)y;
	if (grid_y < 0 || grid_y >= d->map.high || grid_x < 0
		|| grid_x >= d->map.wide)
		return (FAIL);
	tile = d->map.fl_map[grid_y][grid_x];
	if (tile == '0' || tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
		return (PASS);
	return (FAIL);
}

static int	ft_collision(t_data *d, double x, double y)
{
	double	r;

	r = PLAYER_RADIUS;
	if (ft_is_solid_tile(d, x - r, y - r) == FAIL)
		return (FAIL);
	if (ft_is_solid_tile(d, x + r, y - r) == FAIL)
		return (FAIL);
	if (ft_is_solid_tile(d, x - r, y + r) == FAIL)
		return (FAIL);
	if (ft_is_solid_tile(d, x + r, y + r) == FAIL)
		return (FAIL);
	return (PASS);
}

int	ft_position_check(t_data *d, double mve_x, double mve_y)
{
	if (mve_x < PLAYER_RADIUS || mve_y < PLAYER_RADIUS)
		return (FAIL);
	if (mve_x > (double)d->map.wide - PLAYER_RADIUS
		|| mve_y > (double)d->map.high - PLAYER_RADIUS)
		return (FAIL);
	return (PASS);
}

int	ft_move_check(t_data *d, double mve_x, double mve_y, int check)
{
	if (ft_position_check(d, mve_x, d->play.pos.y) == PASS && ft_collision(d,
			mve_x, d->play.pos.y) == PASS)
	{
		if (mve_x < 0.0)
			mve_x = 0.0;
		else if (mve_x > d->map.wide - 0.001)
			mve_x = d->map.wide - 0.001;
		d->play.pos.x = mve_x;
		check += 1;
	}
	if (ft_position_check(d, d->play.pos.x, mve_y) == PASS && ft_collision(d,
			d->play.pos.x, mve_y) == PASS)
	{
		if (mve_y < 0.0)
			mve_y = 0.0;
		else if (mve_y > d->map.high - 0.001)
			mve_y = d->map.high - 0.001;
		d->play.pos.y = mve_y;
		check += 1;
	}
	if (check > 0)
		return (1);
	return (0);
}

int	ft_move_player(t_data *d, int key, double mve_x, double mve_y)
{
	mve_x = d->play.pos.x;
	mve_y = d->play.pos.y;
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
	return (ft_move_check(d, mve_x, mve_y, 0));
}

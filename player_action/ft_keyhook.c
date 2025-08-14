/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:39:52 by nico              #+#    #+#             */
/*   Updated: 2025/08/14 17:28:50 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"



int ft_terminate_game(t_data *d)
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

int ft_key_press(int keycode, t_data *d)
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

int ft_key_release(int keycode, t_data *d)
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

int ft_move_check(t_data *d, double mve_x, double mve_y)
{
    int check;

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

int ft_move_player(t_data *d, int key)
{
    double mve_x;
    double mve_y;

    if ( key == UP)
    {
        mve_x = d->play.pos.x + d->play.dir.x * move_speed;
        mve_y = d->play.pos.y + d->play.dir.y * move_speed;
    }
    else if ( key == DOWN)
    {
        mve_x = d->play.pos.x - d->play.dir.x * move_speed;
        mve_y = d->play.pos.y - d->play.dir.y * move_speed;
    }
    else if ( key == LEFT)
    {
        mve_x = d->play.pos.x + d->play.dir.y * move_speed;
        mve_y = d->play.pos.y - d->play.dir.x * move_speed;
    }
    else if ( key == RIGHT)
    {
        mve_x = d->play.pos.x - d->play.dir.y * move_speed;
        mve_y = d->play.pos.y + d->play.dir.x * move_speed;
    }
    return (ft_move_check(d, mve_x, mve_y));
}

int ft_rotdir(int key)
{
    if (key == ROT_L)
        return (-1);
    return (1);
}

int ft_rotate_player(t_data *d, int key)
{
    double ang;
    double c;
    double s;
    double tmp;

    ang = rot_speed * ft_rotdir(key);
    c = cos(ang);
    s = sin(ang);
    if (ang == 0.0)
        return (0);
    tmp = d->play.dir.x;
    d->play.dir.x = d->play.dir.x * c - d->play.dir.y * s;
    d->play.dir.y = d->play.dir.x * s + d->play.dir.y * c;
    tmp = d->play.pln.x;
    d->play.pln.x = d->play.pln.x * c - d->play.pln.y * s;
    d->play.pln.y = d->play.pln.x * s + d->play.pln.y * c;
    return (1);
}

void ft_player_action(t_data *d)
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

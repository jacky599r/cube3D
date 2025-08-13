/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycaster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:03:26 by nico              #+#    #+#             */
/*   Updated: 2025/08/13 14:44:01 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int ft_dda_prep(t_track *t, t_play *p)
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
	if (t->map.y < 0.25 || t->map.x < 0.25
		|| t->map.y > d->map.high - 0.25 
        || t->map.x > d->map.wide - 1.25)
		return (1);
	if (d->og_map[t->map.y][t->map.x] > '0')
		return (2);
	return (0);
}

void ft_line_len(t_data *d, t_track *t, t_play *p)
{
    if (t->side == 0)
        t->wall = (t->sid.x - t->dlt.x);
    else
        t->wall = (t->sid.y - t->dlt.y);
    t->high = (int)(d->mapy / t->wall);
    t->strt = -(t->high) / 2 + d->mapy / 2;
    if (t->strt < 0)
        t->strt = 0;
    t->end = t->high / 2 + d->mapy / 2;
    if (t->end >= d->mapy)
        t->end = d->mapy - 1;
    if (t->side == 0)
        t->walx = p->pos.y + t->wall * t->dir.y;
    else
        t->walx = p->pos.x + t->wall * t->dir.x;
    t->walx -= floor(t->walx);
}

void ft_dda_algo(t_data *d, t_track *t, t_play *p)
{
    int cross;
    int check;

    cross = ft_dda_prep(p, &t);
    while (cross == 0)
    {
        if(t->sid.x < t->sid.y)
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
    ft_line_len(d, &t, p);
}

int ft_direction_check(t_track *t)
{
    int dir;

    if (t->side == 0)
    {
        if (t->dir.x < 0)
            dir = 3;
        else
            dir = 2;
    }
    else
    {
        if (t->dir.y > 0)
            dir = 1;
        else
            dir = 0;
    }
    return (dir);
}

void ft_compute_refx(t_track *t, t_text *x)
{
    x->ref.x = (int)(t->walx * x->size);
    if ((t->side == 0 && t->dir.x < 0) || (t->side == 1 && t->dir.y > 0))
        x->ref.x = x->size - x->ref.x - 1;
    //valid range check in case
    if (x->ref.x < 0)
        x->ref.x = 0;
    if (x->ref.x >= x->size)
        x->ref.x = x->size - 1;
}

void ft_step_calculate(t_text *x, t_track *t, t_data *d)
{
    x->step = 1.0 * x->size / t->high;
	x->pos = (t->strt - d->mapy / 2 + t->high / 2) * x->step;
}

void ft_update_pxl(t_data *d, t_text *x, t_track *t, int a)
{
    int     y;
    int     y_end;
    int     color;

    y_end = t->end;
    x->indx = ft_direction_check(t);
    ft_compute_refx(t, x);
    ft_step_calculate(x, t, d);
    y = t->strt;
    if (t->strt < 0)
        y = 0;
	if (y_end >= d->mapy) 
        y_end = d->mapy - 1;
    while (y <= y_end)
    {
        x->ref.y = (int)x->pos & (x->size - 1);
        x->pos += x->step;
        color = d->txt[x->indx][x->size * x->ref.y + x->ref.x];
        if (x->indx == 0 || x->indx == 3)
            color = (color >> 1) & 0x7F7F7F;
        if (color > 0)
            d->pxl[y][a] = color;
        y ++;
    }
}

void ft_ray_cast(t_play *p, t_data *d)
{
    t_track     t;
    int         a;

    a = 0;
    t = d->track;
    while (a < d->mapx)
    {
        ft_track_init(t);
        t.cam_x = 2 * a / 640 - 1;
        t.dir.x = p->dir.x + p->pln.x * t.cam_x;
        t.dir.y = p->dir.y + p->pln.y * t.cam_x;
        t.map.x = (int)p->pos.x;
        t.map.y = (int)p->pos.y;
        t.dlt.x = fabs(1 / t.dir.x);
        t.dlt.y = fabs(1 / t.dir.y);
        ft_dda_algo(d, &t, p);
        ft_update_pxl(d, &d->text, &t, a);
        a ++;
    }
}

void	*ft_pxl_init(size_t count, size_t size)
{
	void	*pxl;
    int     a;

	pxl = malloc(count * size);
	if (!pxl)
		return (NULL);
    a = size * count;
    while (a--)
		*(unsigned char *)pxl ++ = 0;
	return (pxl);
}

void ft_pxl_fill(t_data *d)
{
    int a;

    a = 0;
    if (d->pxl)
        ft_safe_array((void ***)&d->pxl);
    d->pxl = ft_pxl_init(d->mapy + 1, sizeof * d->pxl);
    if (!d->pxl)
    {
        ft_error_msg("Malloc error", NULL, NULL, FAIL);
        ft_freedom(d, 1);
    }
    while(a < d->mapy)
    {
        d->pxl[a] = ft_pxl_init(d->mapx + 1 , sizeof * d->pxl);
        if (!d->pxl[a])
        {
            ft_error_msg("Malloc error", NULL, NULL, FAIL);
            ft_freedom(d, 1);
        }
        a ++;
    }
}

void ft_display_wind(t_data *d, t_img *p, int x, int y)
{
    int dot;

    if (d->pxl[y][x] > 0)
    {    
        dot = y * (p->line / 4) + x;
        p->addr[dot] = d->pxl[y][x];
    }
    else if (y < d->mapy / 2)
     {    
        dot = y * (p->line / 4) + x;
        p->addr[dot] = d->text.rgb_c;
    }
    else if (y < d->mapy - 1)
    {    
        dot = y * (p->line / 4) + x;
        p->addr[dot] = d->text.rgb_g;
    }
}

void ft_display(t_data *d)
{
    t_img pic;
    int x;
    int y;

    y = 0;
    ft_img_init(pic);
    pic.img = mlx_new_image(d->mlx, d->mapx, d->mapy);
    if (pic.img == NULL)
    {    
        ft_error_msg("Mlx error", NULL, NULL, 0);
        ft_freedom(d);
    }
    pic.addr = (int *)mlx_get_data_addr(pic.img, &pic.bpp, &pic.line, &pic.endian);
    while (y < d->mapy)
    {
        x = 0;
        while (x < d->mapx)
        {
            ft_display_wind(d, &pic, x, y);
            x ++;
        }
        y ++;
    }
    mlx_put_image_to_window(d->mlx, d->wind, pic.img, 0, 0);
    mlx_destroy_image(d->mlx, pic.img);
}

void ft_raycasting(t_data *data)
{
    ft_pxl_fill(data);
    ft_track_init(&data->track);
    ft_ray_cast(&data->play, data);
    ft_display(data);
}
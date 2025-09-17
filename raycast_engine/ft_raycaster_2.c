/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycaster_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:45:10 by nico              #+#    #+#             */
/*   Updated: 2025/09/17 15:36:42 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_update_pxl(t_data *d, t_text *x, t_track *t, int a)
{
	int	y;
	int	y_end;
	int	color;

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
		y++;
	}
}

void *ft_pxl_init(size_t count, size_t size)
{
    void			*px;
    unsigned char	*p;
    size_t 			a;

    px = malloc(count * size);
    if (!px)
        return NULL;

    p = (unsigned char *)px;
    a = count * size;
    while (a--)
        *p++ = 0;

    return (px);
}

void	ft_pxl_fill(t_data *d)
{
	int	a;

	a = 0;
	//printf("pxl_fill 1\n");
	if (d->pxl)
		ft_safe_array((void ***)&d->pxl);
	//printf("pxl_fill 2\n");
	d->pxl = ft_pxl_init(d->mapy + 1, sizeof *d->pxl);
	//printf("pxl_fill 3\n");
	if (!d->pxl)
	{
		ft_error_msg("Malloc error", NULL, NULL, FAIL);
		ft_freedom(d);
	}
	while (a < d->mapy)
	{
		d->pxl[a] = ft_pxl_init(d->mapx + 1, sizeof *d->pxl);
		if (!d->pxl[a])
		{
			ft_error_msg("Malloc error", NULL, NULL, FAIL);
			ft_freedom(d);
		}
		a++;
	}
}

void	ft_display_wind(t_data *d, t_img *p, int x, int y)
{
	int	dot;

	if (d->pxl[y][x] > 0)
	{
		dot = y * (p->line / 4) + x;
		p->addr[dot] = d->pxl[y][x];
	}
	else if (y < d->mapy / 2)
	{
		dot = y * (p->line / 4) + x;
		p->addr[dot] = *(d->text.rgb_c);
	}
	else if (y < d->mapy - 1)
	{
		dot = y * (p->line / 4) + x;
		p->addr[dot] = *(d->text.rgb_g);
	}
}

void	ft_display(t_data *d)
{
	t_img p;
	int x;
	int y;

	y = 0;
	ft_img_init(&p);
	p.img = mlx_new_image(d->mlx, d->mapx, d->mapy);
	if (p.img == NULL)
	{
		ft_error_msg("Mlx error", NULL, NULL, 0);
		ft_freedom(d);
	}
	p.addr = (int *)mlx_get_data_addr(p.img, &p.bpp, &p.line, &p.endian);
	while (y < d->mapy)
	{
		x = 0;
		while (x < d->mapx)
		{
			ft_display_wind(d, &p, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(d->mlx, d->wind, p.img, 0, 0);
	mlx_destroy_image(d->mlx, p.img);
}
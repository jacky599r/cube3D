/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:00:28 by nico              #+#    #+#             */
/*   Updated: 2025/08/14 15:17:03 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void ft_free_data(t_data *d)
{
    int i;

    if (!d) 
        return;
    ft_free_int_arr(&d->pxl, d->map.high);
    d->pxl = NULL;
    ft_free_int_arr(&d->txt, d->map.high);
    d->txt = NULL;
    ft_free_text(&d->text);
    ft_free_map(&d->map);
    //ft_free_mini(&d->mini);
    ft_safe_array((void ***)&d->og_map);
    ft_safe_array((void ***)&d->fl_map);
    /* 5) if you malloc’d d itself, you can now do:
         ft_safe_ptr(d);
         d = NULL;
       —but only if d wasn’t on the stack! */
}

void ft_freedom(t_data *d)
{
    if (!d)
        exit(FAIL);
    if (d->wind && d->mlx)
        mlx_destroy_window(d->mlx, d->wind);
    if (d->mlx)
    {
        mlx_destroy_display(d->mlx);
        mlx_loop_end(d->mlx);
        free(d->mlx);
    }
    ft_free_data(d);
    exit(FAIL);
}

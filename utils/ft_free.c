/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:09:21 by nico              #+#    #+#             */
/*   Updated: 2025/09/16 15:14:46 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_safe_ptr(void *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
}

void ft_free_int_arr(int ***mat_ptr, int rows)
{
    int i;

    i = 0;
    if (!mat_ptr || !*mat_ptr)
        return;
    while (i < rows)
    {
        ft_safe_ptr((*mat_ptr)[i]);
        (*mat_ptr)[i] = NULL;
        i++;
    }
    ft_safe_ptr(*mat_ptr);
    *mat_ptr = NULL;
}

void ft_free_text(t_text *t)
{
	if (!t) 
		return;
	ft_safe_ptr(t->txt_n);
	t->txt_n = NULL;
	ft_safe_ptr(t->txt_s);
	t->txt_s = NULL;
	ft_safe_ptr(t->txt_w);
	t->txt_w = NULL;
	ft_safe_ptr(t->txt_e);
	t->txt_e = NULL;
	ft_safe_ptr(t->rgb_g);
	t->rgb_g = NULL;
	ft_safe_ptr(t->rgb_c);
	t->rgb_c = NULL;
	// Image data cleanup
	ft_safe_ptr(t->addr);
	t->addr = NULL;
	ft_safe_ptr(t->img);
	t->img = NULL;
}

void ft_free_img(t_img *i)
{
    if (!i)
        return;
    ft_safe_ptr(i->addr);
    i->addr = NULL;
    ft_safe_ptr(i->img);
    i->img = NULL;
}

void ft_free_map(t_map *m)
{
	if (!m)
		return;
	ft_safe_array((void ***)&m->og_map);
	m->og_map = NULL;
	ft_safe_array((void ***)&m->fl_map);
	m->fl_map = NULL;
}

void ft_free_mini(t_mini *m)
{
    if (!m)
        return;
    ft_safe_array((void ***)&m->og_mini);
    m->og_mini = NULL;
    ft_free_img(m->mini_m);
    m->mini_m = NULL;
}

void ft_free_all(t_data *data)
{
    if (!data) 
        return;
    if (data->pxl && data->map.high > 0)
    {
        ft_free_int_arr(&data->pxl, data->map.high);
        data->pxl = NULL;
    }
    if (data->txt && data->map.high > 0)
    {
        ft_free_int_arr(&data->txt, data->map.high);
        data->txt = NULL;
    }
    ft_free_text(&data->text);
    ft_free_map(&data->map);
    ft_free_img(&data->mini);
    // Map arrays are freed through ft_free_map()
}
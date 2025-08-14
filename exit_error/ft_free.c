/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:09:21 by nico              #+#    #+#             */
/*   Updated: 2025/08/14 15:17:56 by nico             ###   ########.fr       */
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

void	ft_safe_array(void ***array)
{
	int	a;

	a = 0;
	if (!array || !(*array))
		return ;
	while ((*array)[a])
	{
		ft_safe_ptr((*array)[a]);
		(*array)[a] = NULL;
		a++;
	}
	free(*array);
	*array = NULL;
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
    ft_safe_ptr(t->txt_g);
    t->txt_g = NULL;
    ft_safe_ptr(t->txt_c);
    t->txt_c = NULL;
    ft_safe_ptr(t->rgb_g);
    t->rgb_g = NULL;
    ft_safe_ptr(t->rgb_c);
    t->rgb_c = NULL;
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
    ft_safe_ptr(m->m_ref);
    m->m_ref = NULL;
    ft_safe_array((void ***)&m->og_map);
    m->og_map = NULL;
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


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:06:56 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/19 13:06:59 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_free_text(t_text *t)
{
	if (!t)
		return ;
	ft_safe_ptr(t->txt_n);
	t->txt_n = NULL;
	ft_safe_ptr(t->txt_s);
	t->txt_s = NULL;
	ft_safe_ptr(t->txt_w);
	t->txt_w = NULL;
	ft_safe_ptr(t->txt_e);
	t->txt_e = NULL;
	ft_safe_ptr(t->txt_d);
	t->txt_d = NULL;
	ft_safe_ptr(t->rgb_g);
	t->rgb_g = NULL;
	ft_safe_ptr(t->rgb_c);
	t->rgb_c = NULL;
}

void	ft_free_img(t_img *i)
{
	if (!i)
		return ;
	ft_safe_ptr(i->addr);
	i->addr = NULL;
	ft_safe_ptr(i->img);
	i->img = NULL;
}

void	ft_free_map(t_map *m)
{
	if (!m)
		return ;
	ft_safe_array((void ***)&m->og_map);
	m->og_map = NULL;
	ft_safe_array((void ***)&m->fl_map);
	m->fl_map = NULL;
}

void	ft_free_fog(t_data *data)
{
	if (!data || !data->fog)
		return ;
	ft_safe_array((void ***)&data->fog);
	data->fog = NULL;
}

// void	ft_free_mini(t_mini *m)
// {
// 	if (!m)
// 		return ;
// 	ft_safe_array((void ***)&m->og_mini);
// 	m->og_mini = NULL;
// 	ft_free_img(m->mini_m);
// 	m->mini_m = NULL;
// }

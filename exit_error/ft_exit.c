/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:06:34 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/19 13:06:36 by nsamarin         ###   ########.fr       */
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

void	ft_free_int_arr(int ***mat_ptr, int rows)
{
	int	i;

	i = 0;
	if (!mat_ptr || !*mat_ptr)
		return ;
	while (i < rows)
	{
		ft_safe_ptr((*mat_ptr)[i]);
		(*mat_ptr)[i] = NULL;
		i++;
	}
	ft_safe_ptr(*mat_ptr);
	*mat_ptr = NULL;
}

void	ft_free_data(t_data *d)
{
	if (!d)
		return;
    if (d->pxl && d->map.high > 0)
    {
        ft_free_int_arr(&d->pxl, d->mapy);
        d->pxl = NULL;
    }
    if (d->txt)
    {
        ft_free_int_arr(&d->txt, 5);
        d->txt = NULL;
    }
    ft_free_text(&d->text);
    ft_free_map(&d->map);
}

void	ft_freedom(t_data *d)
{
	if (!d)
		return;
	
	printf("Cleaning up resources...\n");
	if (d->wind && d->mlx)
		mlx_destroy_window(d->mlx, d->wind);
	if (d->mlx)
	{
		mlx_destroy_display(d->mlx);
		mlx_loop_end(d->mlx);
		free(d->mlx);
		d->mlx = NULL;
	}
	ft_free_data(d);
	free(d);
}

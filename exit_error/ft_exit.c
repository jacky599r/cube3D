/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:00:28 by nico              #+#    #+#             */
/*   Updated: 2025/09/17 21:45:32 by jacky599r        ###   ########.fr       */
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
		return ;
	ft_free_int_arr(&d->pxl, d->map.high);
	d->pxl = NULL;
	ft_free_int_arr(&d->txt, d->map.high);
	d->txt = NULL;
	ft_free_text(&d->text);
	ft_free_map(&d->map);
	// ft_free_mini(&d->mini);
	// Map arrays are freed through ft_free_map()
	/* 5) if you malloc'd d itself, you can now do:
			ft_safe_ptr(d);
			d = NULL;
		—but only if d wasn't on the stack! */
}

void	ft_freedom(t_data *d)
{
	if (!d)
		return;
	
	// Temporarily disabled MLX functionality for testing
	printf("Cleaning up resources...\n");
	
	// Original MLX code commented out:
	/*
	if (d->wind && d->mlx)
		mlx_destroy_window(d->mlx, d->wind);
	printf("freedom 2\n");
	if (d->mlx)
	{
		mlx_destroy_display(d->mlx);
		mlx_loop_end(d->mlx);
		free(d->mlx);
	}
	printf("freedom 3\n");
	ft_free_data(d);
	// Don't call exit() here for testing - let the main program control exit
}

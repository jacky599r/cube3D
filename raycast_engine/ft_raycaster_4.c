/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycaster_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 04:36:08 by nico              #+#    #+#             */
/*   Updated: 2025/09/22 04:37:27 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_die_alloc(t_data *d, const char *msg)
{
	ft_error_msg("Error", (char *)msg, FAIL);
	ft_freedom(d);
}

void	*ft_xinit(t_data *d, size_t count, size_t size)
{
	void	*p;

	p = ft_pxl_init(count, size);
	if (!p)
		ft_die_alloc(d, "Malloc Failure");
	return (p);
}

void	ft_free_framebuffers(t_data *d)
{
	if (d->pxl)
	{
		ft_safe_array((void ***)&d->pxl);
		d->pxl = NULL;
	}
	if (d->zbuffer)
	{
		free(d->zbuffer);
		d->zbuffer = NULL;
	}
}

void	ft_alloc_pxl_rows(t_data *d)
{
	int	a;

	d->pxl = ft_xinit(d, d->mapy + 1, sizeof(*d->pxl));
	a = 0;
	while (a < d->mapy)
	{
		d->pxl[a] = ft_xinit(d, d->mapx + 1, sizeof(**d->pxl));
		a++;
	}
}

void	ft_alloc_zbuffer(t_data *d)
{
	d->zbuffer = ft_xinit(d, d->mapx, sizeof(double));
}

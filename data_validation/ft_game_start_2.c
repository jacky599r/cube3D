/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_start_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 07:08:05 by nico              #+#    #+#             */
/*   Updated: 2025/09/22 07:11:10 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_texture_err(t_data *d, t_img *p, char *path, char *msg)
{
	mlx_destroy_image(d->mlx, p->img);
	free(path);
	ft_error_msg("Error", msg, FAIL);
	ft_freedom(d);
}

static void	ft_load_wall_texture(t_data *d, int dir, int size)
{
	t_img	p;
	char	*path;

	path = ft_direction_id(d, dir);
	if (!path)
	{
		ft_error_msg("Error", "Missing wall texture", FAIL);
		ft_freedom(d);
		exit(EXIT_FAILURE);
	}
	ft_img_start(d, &p, path, size);
	d->txt[dir] = ft_fill_texture(d, &p, size);
	if (!d->txt[dir])
	{
		ft_texture_err(d, &p, path, "Malloc Failure");
		return ;
	}
	mlx_destroy_image(d->mlx, p.img);
	free(path);
}

static void	ft_load_door_texture(t_data *d, int size)
{
	t_img	p;
	char	*path;

	if (!d->text.txt_d)
	{
		ft_error_msg("Error", "Missing door texture", FAIL);
		ft_freedom(d);
		exit(EXIT_FAILURE);
	}
	path = ft_direction_id(d, DOOR_IDX);
	if (!path)
	{
		ft_error_msg("Error", "Missing door texture", FAIL);
		ft_freedom(d);
		exit(EXIT_FAILURE);
	}
	ft_img_start(d, &p, path, size);
	d->txt[DOOR_IDX] = ft_fill_texture(d, &p, size);
	if (!d->txt[DOOR_IDX])
	{
		ft_texture_err(d, &p, path, "Door texture alloc failed");
		return ;
	}
	mlx_destroy_image(d->mlx, p.img);
	free(path);
}

void	ft_direction_text(t_data *d, int dir, int size)
{
	while (dir < 4)
	{
		ft_load_wall_texture(d, dir, size);
		dir++;
	}
	ft_load_door_texture(d, size);
}

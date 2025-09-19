/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:23:59 by nico              #+#    #+#             */
/*   Updated: 2025/09/19 16:08:58 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_direction_id(t_data *d, int dir)
{
	if (dir == 0)
		return (ft_strdup(d->text.txt_n));
	else if (dir == 1)
		return (ft_strdup(d->text.txt_s));
	else if (dir == 2)
		return (ft_strdup(d->text.txt_e));
	else if (dir == 3)
		return (ft_strdup(d->text.txt_w));
	return (NULL);
}

int	*ft_fill_texture(t_data *d, t_img *pic, int size)
{
	int	x;
	int	y;
	int	*buf;

	y = 0;
	buf = ft_calloc(1, sizeof(int) * size * size);
	if (!buf)
	{
		ft_error_msg("Malloc Error", NULL, FAIL);
		ft_freedom(d);
		return (NULL);
	}
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			buf[y * size + x] = pic->addr[y * size + x];
			x++;
		}
		y++;
	}
	return (buf);
}

void	ft_img_start(t_data *d, t_img *p, char *path, int size)
{
	int	width;
	int	height;

	ft_img_init(p);
	width = size;
	height = size;
	p->img = mlx_xpm_file_to_image(d->mlx, path, &width, &height);
	if (p->img == NULL)
	{
		ft_error_msg("MLX Image Error", NULL, FAIL);
		ft_freedom(d);
	}
	p->addr = (int *)mlx_get_data_addr(p->img, &p->bpp, &p->line, &p->endian);
}

void	ft_direction_text(t_data *d, int dir, int size)
{
	t_img	p;
	char	*path;

	while (dir < 4)
	{
		path = ft_direction_id(d, dir);
		ft_img_start(d, &p, path, size);
		d->txt[dir] = ft_fill_texture(d, &p, size);
		if (!d->txt[dir])
		{
			mlx_destroy_image(d->mlx, p.img);
			free(path);
			ft_error_msg("Error", "Malloc Failure", FAIL);
			ft_freedom(d);
		}
		mlx_destroy_image(d->mlx, p.img);
		free(path);
		dir++;
	}
}

void	ft_game_start(t_data *d)
{
	d->mlx = mlx_init();
	if (!d->mlx)
	{
		ft_error_msg("Error", "MLX Start Failure", FAIL);
		ft_freedom(d);
	}
	d->wind = mlx_new_window(d->mlx, d->mapx, d->mapy, "Cub3D");
	if (!d->wind)
	{
		ft_error_msg("Error", "MLX Window Failure", FAIL);
		ft_freedom(d);
	}
	d->txt = ft_calloc(5, sizeof (*d->txt));
	if (!d->txt)
	{
		ft_error_msg("Error", "Malloc Failure", FAIL);
		ft_freedom(d);
	}
	ft_direction_text(d, 0, d->text.size);
	ft_print_welcome();
}

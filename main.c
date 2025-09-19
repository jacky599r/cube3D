/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:43:43 by nico              #+#    #+#             */
/*   Updated: 2025/09/19 13:16:59 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void print_text(t_text *t)
{
    if (!t) return;
    printf("=== Texture Info ===\n");
    printf("txt_n: %s\n", t->txt_n ? t->txt_n : "(null)");
    printf("txt_s: %s\n", t->txt_s ? t->txt_s : "(null)");
    printf("txt_w: %s\n", t->txt_w ? t->txt_w : "(null)");
    printf("txt_e: %s\n", t->txt_e ? t->txt_e : "(null)");

    printf("rgb_g (floor): %p\n", (void *)t->rgb_g);
    printf("rgb_c (ceiling): %p\n", (void *)t->rgb_c);
    printf("size: %d, indx: %d\n", t->size, t->indx);
    printf("step: %f, pos: %f\n", t->step, t->pos);
    printf("ref: (%d, %d)\n", t->ref.x, t->ref.y);
    printf("\n");
}

void print_map(t_map *m)
{
    if (!m) return;
    printf("=== Map Info ===\n");
    printf("high: %d, wide: %d, eom: %d\n", 
           m->high, m->wide, m->eom);
    if (m->fl_map)
    {
        printf("fl_map:\n");
        for (int i = 0; m->fl_map[i]; i++)
            printf("  %s\n", m->fl_map[i]);
    }
    printf("\n");
}

void print_map_special(t_map *m)
{
    if (m->fl_map)
    {
        printf("fl_map:\n");
        for (int i = 0; m->fl_map[i]; i++)
            printf("  %s\n", m->fl_map[i]);
    }
    printf("-end-\n");
}

void print_track(t_track *t)
{
    if (!t) return;
    printf("=== Track Info ===\n");

    printf("cam_x: %f\n", t->cam_x);
    printf("wall: %f, walx: %f\n", t->wall, t->walx);
    printf("side: %d\n", t->side);
    printf("high: %d, strt: %d, end: %d\n", t->high, t->strt, t->end);

    printf("map: (%d, %d)\n", t->map.x, t->map.y);
    printf("stp: (%d, %d)\n", t->stp.x, t->stp.y);

    printf("dir: (%f, %f)\n", t->dir.x, t->dir.y);
    printf("sid: (%f, %f)\n", t->sid.x, t->sid.y);
    printf("dlt: (%f, %f)\n", t->dlt.x, t->dlt.y);

    printf("\n");
}

void print_play(t_play *p)
{
    if (!p) return;
    printf("=== Player Info ===\n");
    printf("dir: (%f, %f), plane: (%f, %f)\n", p->dir_x, p->dir_y, p->plane_x, p->plane_y);
    printf("move_speed: %f, rot_speed: %f\n", p->move_speed, p->rot_speed);
    printf("s_dir: %c\n", p->s_dir);
    printf("pos: (%f, %f)\n", p->pos.x, p->pos.y);
    printf("check: %d, rot: %d\n", p->check, p->rot);
    printf("\n");
}

void print_data(t_data *d)
{
    if (!d) return;
    printf("=== Data Struct ===\n");
    printf("mapx: %d, mapy: %d\n", d->mapx, d->mapy);
    printf("mlx: %p, wind: %p\n", d->mlx, d->wind);
    print_text(&d->text);
    print_map(&d->map);
    print_play(&d->play);
    print_track(&d->track);

    printf("(Other members like pxl/txt/mini/key omitted for brevity)\n");
    printf("\n");
}

int ft_raycast_check(t_data *d)
{
	ft_player_action(d);
	if (d->play.check == 0)
		return (0);
	ft_raycasting(d);
	return (0);
}


int	main(int argc, char **argv)
{
	t_data	*data;
	int		err_code;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	err_code = ft_data_validation(data, argc, argv);
	if (err_code != PASS)
		return (ft_freedom(data), err_code);
	ft_game_start(data);
	ft_raycasting(data);
    mlx_hook(data->wind, 17, 0, ft_terminate_game, data);
	mlx_hook(data->wind, 2, 1L << 0, ft_key_press, data);
	mlx_hook(data->wind, 3, 1L << 1, ft_key_release, data);
	mlx_loop_hook(data->mlx, ft_raycast_check, data);
	print_map_special(&data->map);
    mlx_loop(data->mlx);
	return (0);
}

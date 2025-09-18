/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeong <zyeong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:43:43 by nico              #+#    #+#             */
/*   Updated: 2025/09/18 15:44:56 by zyeong           ###   ########.fr       */
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
    //printf("max_x: %d, max_y: %d\n", m->max_x, m->max_y);
    //printf("player_x: %d, player_y: %d, dir: %c\n", 
    //       m->player_x, m->player_y, m->player_dir);
    printf("high: %d, wide: %d, eom: %d\n", 
           m->high, m->wide, m->eom);

    // if (m->og_map)
    // {
    //     printf("og_map:\n");
    //     for (int i = 0; m->og_map[i]; i++)
    //         printf("  %s\n", m->og_map[i]);
    // }
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

    // Nested structs
    print_text(&d->text);
    print_map(&d->map);
    print_play(&d->play);
    print_track(&d->track);

    printf("(Other members like pxl/txt/mini/key omitted for brevity)\n");
    printf("\n");
}


// Function declarations
int ft_process_map(t_data *data, char **argv);
void ft_game_start(t_data *data);
void ft_raycasting(t_data *data);
int ft_key_press(int keycode, t_data *data);
int ft_key_release(int keycode, t_data *data);
int ft_raycast_check(t_data *data);

// Simple implementation of ft_process_map for now
int ft_process_map(t_data *data, char **argv)
{
	(void)data; // Suppress unused parameter warning
	(void)argv; // Suppress unused parameter warning
	// For now, just return PASS - this can be enhanced later
	// This function would typically process the map data for rendering
	return (PASS);
}

// Raycast check function - handles player movement and raycasting updates
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
	err_code = ft_process_map(data, argv);
	if (err_code != PASS)
		return (ft_freedom(data), err_code);
	ft_game_start(data);
	ft_raycasting(data);
    printf("Map coordinates:(%f - %f)\n", data->play.pos.x, data->play.pos.y);
    printf("Player cell: (x = %d, y = %d)\n", (int)data->play.pos.x, (int)data->play.pos.y);
	mlx_hook(data->wind, 2, 1L << 0, ft_key_press, data);
    //printf("phase 3 done\n");
	mlx_hook(data->wind, 3, 1L << 1, ft_key_release, data);
    //printf("phase 4 done\n");
    
	mlx_loop_hook(data->mlx, ft_raycast_check, data);
    //printf("phase 5 done\n");
    //print_data(data);
	print_map_special(&data->map);
    mlx_loop(data->mlx);
	
	return (0);
}

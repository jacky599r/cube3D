/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:43:43 by nico              #+#    #+#             */
/*   Updated: 2025/09/16 18:03:34 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void print_ptr(const char *name, const void *p) { printf("%s: %p\n", name, p); }
static void print_cstr(const char *name, const char *s) { printf("%s: %s\n", name, s ? s : "(null)"); }

static void print_str_matrix(const char *label, char **rows, int max_rows) {
    printf("%s:\n", label);
    if (!rows) { printf("  (null)\n"); return; }
    for (int i = 0; rows[i] && (max_rows <= 0 || i < max_rows); ++i)
        printf("  [%d] %s\n", i, rows[i]);
}


static int get_texel(const int *tex, int size, int x, int y) {
    if (!tex || size <= 0) return 0;
    if (x < 0) x = 0; if (y < 0) y = 0;
    if (x >= size) x = size-1; if (y >= size) y = size-1;
    return tex[y * size + x];
}

// ===== printers =====
void dbg_print_keys(const t_keys *k) {
    printf("=== t_keys ===\n");
    if (!k) { printf("(null)\n"); return; }
    printf("up:%d down:%d left:%d right:%d l_arw:%d r_arw:%d\n",
           k->up,k->down,k->left,k->right,k->l_arw,k->r_arw);
}

void dbg_print_int2(const t_int *v, const char *name) {
    printf("=== t_int %s ===\n", name ? name : "");
    if (!v) { printf("(null)\n"); return; }
    printf("x:%d y:%d\n", v->x, v->y);
}

void dbg_print_dbl2(const t_dbl *v, const char *name) {
    printf("=== t_dbl %s ===\n", name ? name : "");
    if (!v) { printf("(null)\n"); return; }
    printf("x:%f y:%f\n", v->x, v->y);
}

void dbg_print_img(const t_img *img, const char *name) {
    printf("=== t_img %s ===\n", name ? name : "");
    if (!img) { printf("(null)\n"); return; }
    print_ptr("img", img->img);
    print_ptr("addr", img->addr);
    printf("bpp:%d line(bytes):%d endian:%d\n", img->bpp, img->line, img->endian);
}

void dbg_print_text(const t_text *t) {
    printf("=== t_text ===\n");
    if (!t) { printf("(null)\n"); return; }
    print_cstr("txt_n", t->txt_n);
    print_cstr("txt_s", t->txt_s);
    print_cstr("txt_w", t->txt_w);
    print_cstr("txt_e", t->txt_e);

    printf("rgb_g: "); if (t->rgb_g) printf("0x%08lX @%p\n", *t->rgb_g, (void*)t->rgb_g); else printf("(null)\n");
    printf("rgb_c: "); if (t->rgb_c) printf("0x%08lX @%p\n", *t->rgb_c, (void*)t->rgb_c); else printf("(null)\n");

    printf("size:%d indx:%d step:%f pos:%f ref:(%d,%d)\n",
           t->size, t->indx, t->step, t->pos, t->ref.x, t->ref.y);
}

void dbg_print_map(const t_map *m) {
    printf("=== t_map ===\n");
    if (!m) { printf("(null)\n"); return; }
    printf("max_x:%d max_y:%d high:%d wide:%d eom:%d start_index:%d\n",
           m->max_x,m->max_y,m->high,m->wide,m->eom,m->start_index);
    printf("player:(%d,%d) dir:%c\n", m->player_x, m->player_y, m->player_dir ? m->player_dir : '?');
    print_str_matrix("og_map (first 32 rows)", m->og_map, 32);
    print_str_matrix("fl_map (first 32 rows)", m->fl_map, 32);
}

void dbg_print_track(const t_track *t) {
    printf("=== t_track ===\n");
    if (!t) { printf("(null)\n"); return; }
    printf("pos:(%.6f,%.6f) dir:(%.6f,%.6f) plane:(%.6f,%.6f) cam_x:%.6f\n",
           t->pos_x,t->pos_y,t->dir_x,t->dir_y,t->plane_x,t->plane_y,t->cam_x);
    printf("ray_dir:(%.6f,%.6f) map:(%d,%d) step:(%d,%d) side:%d hit:%d\n",
           t->ray_dir_x,t->ray_dir_y,t->map_x,t->map_y,t->step_x,t->step_y,t->side,t->hit);
    printf("side_dist:(%.6f,%.6f) delta_dist:(%.6f,%.6f) perp:%.6f wall_x:%.6f\n",
           t->side_dist_x,t->side_dist_y,t->delta_dist_x,t->delta_dist_y,t->perp_wall_dist,t->wall_x);
    printf("line_height:%d draw:[%d..%d] tex:(%d,%d) step:%.6f tex_pos:%.6f\n",
           t->line_height,t->draw_start,t->draw_end,t->tex_x,t->tex_y,t->step,t->tex_pos);
}

void dbg_print_play(const t_play *p) {
    printf("=== t_play ===\n");
    if (!p) { printf("(null)\n"); return; }
    printf("s_dir:%c pos:(%d,%d) dir:(%.6f,%.6f) plane:(%.6f,%.6f)\n",
           p->s_dir ? p->s_dir : '?', p->pos.x, p->pos.y, p->dir_x, p->dir_y, p->plane_x, p->plane_y);
    printf("move_speed:%.6f rot_speed:%.6f check:%d rot:%d\n",
           p->move_speed, p->rot_speed, p->check, p->rot);
}

static void dbg_print_textures(const int **txt, int tex_size, int cap_probe) {
    printf("=== textures (ptrs) ===\n");
    if (!txt) { printf("(null)\n"); return; }
    for (int i = 0; i < cap_probe; ++i) {
        if (!txt[i]) { printf("  [%d] (null)\n", i); break; }
        printf("  [%d] %p\n", i, (const void*)txt[i]);
    }
    if (tex_size > 0 && txt && txt[0]) {
        int corners[4][2] = {{0,0},{tex_size-1,0},{0,tex_size-1},{tex_size-1,tex_size-1}};
        for (int i = 0; i < 4 && txt[i]; ++i) {
            printf("  samples tex[%d] size=%d: ", i, tex_size);
            for (int c = 0; c < 4; ++c) {
                int x = corners[c][0], y = corners[c][1];
                int val = get_texel(txt[i], tex_size, x, y);
                printf("(%d,%d)=0x%08X ", x, y, (unsigned)val);
            }
            printf("\n");
        }
    }
}

static void dbg_print_pxl_samples(int **pxl, int w, int h) {
    printf("=== pxl buffer samples ===\n");
    if (!pxl || w <= 0 || h <= 0) { printf("(null or empty)\n"); return; }
    int sx[4] = {0, w/2, w-1, w/3};
    int sy[4] = {0, h/2, h-1, (2*h)/3};
    for (int i = 0; i < 4; ++i) {
        int x = sx[i]; int y = sy[i];
        if (x < 0) x = 0; if (y < 0) y = 0;
        if (x >= w) x = w-1; if (y >= h) y = h-1;
        printf("  pxl[%d,%d] = 0x%08X\n", y, x, pxl[y] ? (unsigned)pxl[y][x] : 0);
    }
}

void dbg_print_data(const t_data *d) {
    printf("========== t_data ==========\n");
    if (!d) { printf("(null)\n"); return; }
    printf("mapx:%d mapy:%d\n", d->mapx, d->mapy);
    print_ptr("mlx", d->mlx);
    print_ptr("wind", d->wind);

    dbg_print_keys(&d->key);
    dbg_print_play(&d->play);
    dbg_print_track(&d->track);
    dbg_print_text(&d->text);
    dbg_print_map(&d->map);
    dbg_print_img(&d->mini, "mini");

    // Show a few samples to avoid flooding output
    dbg_print_pxl_samples(d->pxl, d->mapx, d->mapy);

    // textures: try to infer/limit
    dbg_print_textures((const int**)d->txt, d->text.size, 8);

    printf("======== end t_data ========\n");
}



// Function declarations
int ft_extension_check(char *file);
int ft_open_file(char *path);
int ft_process_map(t_data *data, char **argv);
void ft_game_start(t_data *data);
void ft_raycasting(t_data *data);
int ft_key_press(int keycode, t_data *data);
int ft_key_release(int keycode, t_data *data);
int ft_raycast_check(t_data *data);

int ft_extension_check(char *file)
{
    int len;

    if (!file)
        return (ft_error_msg("Error", "No file specified", NULL, FAIL));
    
    len = ft_strlen(file);
    if (len < 5)
        return (ft_error_msg("Error", "File name too short", file, FAIL));
    
    if (ft_strncmp(file + len - 4, ".cub", 4) != 0)
        return (ft_error_msg("Error", "Invalid file extension", file, FAIL));
    
    return (PASS);
}

int ft_open_file(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_error_msg("Error", "Cannot open file", path, FAIL));
	close(fd);
	return (PASS);
}

int ft_data_validation(t_data *data, int argc, char **argv)
{
    ft_data_init(data);
    
    // Validate argument count
    if (argc != 2)
        return (ft_error_msg("Error", "Invalid number of arguments", NULL, FAIL));
    
    // Validate file path is not NULL
    if (!argv[1])
        return (ft_error_msg("Error", "No file specified", NULL, FAIL));
    
    // Validate file extension
    if (ft_extension_check(argv[1]) != PASS)
        return (FAIL);
    
    // Validate file accessibility
    if (ft_open_file(argv[1]) != PASS)
        return (FAIL);
    
    // Read and validate file content
    data->map.og_map = ft_get_raw_map_data(argv[1]);
    if (!data->map.og_map)
        return (FAIL);
    
    // Validate map configuration
    if (ft_check_map_config(data) == FAIL)
    {
        ft_safe_array((void ***)&data->map.og_map);
        return (FAIL);
    }
    
    // Prepare map for flood-fill validation
    if (ft_prepare_map_for_flood_fill(data) == FAIL)
    {
        ft_safe_array((void ***)&data->map.og_map);
        return (FAIL);
    }
    
    // Set initial player view
    ft_set_initial_player_view(data);
    
    // Validate map enclosure
    if (ft_validate_map_enclosure(data) == FAIL)
    {
        ft_safe_array((void ***)&data->map.og_map);
        ft_safe_array((void ***)&data->map.fl_map);
        return (FAIL);
    }
    return (PASS);
}

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
	// Initialize MLX and start the game
    dbg_print_data(data);
	ft_game_start(data);
    printf("phase 1 done\n");
	ft_raycasting(data);
    printf("phase 2 done\n");
	mlx_hook(data->wind, 2, 1L << 0, ft_key_press, data);
    printf("phase 3 done\n");
	mlx_hook(data->wind, 3, 1L << 1, ft_key_release, data);
    printf("phase 4 done\n");
	mlx_loop_hook(data->mlx, ft_raycast_check, data);
    printf("phase 5 done\n");
	mlx_loop(data->mlx);
	
	return (0);
}

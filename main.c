/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:43:43 by nico              #+#    #+#             */
/*   Updated: 2025/08/13 16:24:43 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int ft_extension_check(char *file, char *ext)
{
	int len;

    len = ft_strlen(file);
    if (len < 5)
    	return (ft_error_msg("Error File Name", file, NULL, 3));
	if (ft_strncmp(file + len - 4, ext, 4) != 0)
		return (ft_error_msg("Error File Name", file, NULL, 3));
    return(0);
}
int ft_open_file(char *path)
{
    int dfd;
    int fd;
    
    dfd = open(path, O_RDONLY | __O_DIRECTORY);
    if (dfd >= 0) 
    {
        close(dfd);
        return (ft_error_msg("File is Directory", path, NULL, 3));
    }
    if (errno != ENOTDIR) 
        return (ft_error_msg("File Error", path, NULL, FAIL));
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (ft_error_msg("File Error", path, NULL, FAIL));
    close (fd);
    return (PASS);
}

int ft_data_validation(t_data *data, int argc,  char **argv)
{
    if (argc != 2)
        return(FAIL);
    ft_data_init(&data);
    if (ft_extension_check(argv[1], ".cud") != PASS)
        return (FAIL);
    if (ft_open_file(argv[1]) != PASS)
        return (FAIL);
    return(PASS);
}

int ft_process_map(t_data *data, char **argv)
{
    
}

int ft_raycast_check(t_data *d)
{
    d->play.check += ft_;
    if (d->play.check == 0)
        return (0);
    ft_raycasting(d);
    return (0);
}
char *ft_direction_id(t_data *d, int dir)
{
    char *str;

    str = NULL;
    if (dir == 0) // North
        str = ft_strdup(d->text.txt_n);
    else if (dir == 1) // South
        str = ft_strdup(d->text.txt_s);
    else if (dir == 2) // East
        str = ft_strdup(d->text.txt_e);
    else if (dir == 3) // West
        str = ft_strdup(d->text.txt_w);
    return (str);
}

int *ft_fill_texture(t_data *d, t_img *pic, int size)
{
    int x;
    int y;
    int *buf;

    y = 0;
    buf = ft_calloc(1, sizeof * buf * size * size);
    if (!buf)
    {
        ft_error_msg("Malloc Error", NULL, NULL, FAIL);
        ft_freedom(d);
        return (0);
    }
    while (y < size)
    {
        x = 0;
        while (x < size)
        {
            d->txt[y * size + x] = pic->addr[y * size + x];
            x ++;
        }
        y ++;
    }
    return (buf); 
}

void ft_direction_text(t_data *d, int dir, int size)
{
    t_img p;
    int *path;
    
    while (dir < 4)
    {
        path = ft_direction_id(d, dir);
        ft_img_init(p);
        p.img = mlx_xpm_file_to_image(d->mlx, path, size, size);
        if (p.img == NULL)
        {
            ft_error_msg("MLX Image Error", NULL, NULL, FAIL);
            ft_freedom(d);
        }
        p.addr = (int *)mlx_get_data_addr(p.img, &p.bpp, &p.line, &p.endian);
        d->txt[dir] = ft_calloc(1, sizeof * d->txt[dir] * size * size);
        if (!d->txt[dir])
        {
            ft_error_msg("Malloc Error", NULL, NULL, FAIL);
            ft_freedom(d);
        }
        d->txt[dir] = ft_fill_texture(d, &p, size);
        mlx_destroy_image(d->mlx, p.img);
        free(path);
        dir ++;
    } 
}

void ft_game_start(t_data *d)
{
    d->mlx = mlx_init();
    if(!d->mlx)
    {
        ft_error_msg("MLX Start Error", NULL, NULL, FAIL);
        ft_freedom(d);
    }
    d->wind = mlx_new_window(d->mlx, d->mapx, d->mapy, "Cub3D");
    if (!d->wind)
    {
        ft_error_msg("MLX Window Error", NULL, NULL, FAIL);
        ft_freedom(d);
    }
    d->txt = ft_calloc(5, sizeof * d->txt);
    if (!d->txt)
    {
        ft_error_msg("Malloc Error", NULL, NULL, FAIL);
        ft_freedom(d);
    }
    ft_direction_text(d, 0, d->text.size);
}

int main(int argc, char **argv)
{
    t_data *data;
    int     err_code;

    err_code = ft_data_validation(&data, argc, argv);
    if (err_code != PASS)
        return(ft_freedom(data), err_code);
    err_code = ft_process_map(&data, argv);
    if (err_code != PASS)
        return(ft_freedom(data), err_code);
    ft_game_start(&data);
    ft_raycasting(&data);
    ft_key_bind(&data);
    mlx_loop_hook(data->mlx, ft_raycast_check, &data);
    mlx_loop(data->mlx);
    return(0);
}

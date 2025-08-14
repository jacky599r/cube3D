/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:43:43 by nico              #+#    #+#             */
/*   Updated: 2025/08/14 20:30:25 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// int ft_extension_check(char *file, char *ext)
// {
// 	int len;

    len = ft_strlen(file);
    if (len < 5)
    	return (ft_error_msg("Error File Name", file, NULL, 3));
	if (ft_strncmp(file + len - 4, ext, 4) != 0)
		return (ft_error_msg("Error File Name", file, NULL, 3));
    return(0);
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
int ft_read_map(t_data *data, char *path); //can we char *file_name instead?
int ft_parse_map(t_data *data);

int ft_data_validation(t_data *data, int argc, char **argv)
{
    ft_data_init(data);
    if (argc != 2)
        return (ft_error_msg("Error", "Invalid number of arguments", NULL, FAIL));
    if (ft_strncmp(argv[0], "./cub3D", 7) != 0)
        return (ft_error_msg("Error", "Incorrect executable name", NULL, FAIL));
    if (ft_extension_check(argv[1], ".cub") != PASS)
        return (FAIL);
    if (ft_open_file(argv[1]) != PASS)
        return (FAIL);
    data->map.og_map = ft_get_raw_map_data(argv[1]);
    if (!data->map.og_map)
        return (FAIL);
    if (ft_check_map_config(data) == FAIL)
        return (FAIL);
    if (ft_prepare_map_for_flood_fill(data) == FAIL)
        return (FAIL);
    ft_set_initial_player_view(data);
    if (ft_validate_map_enclosure(data) == FAIL)
        return (FAIL);
    return (PASS);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		err_code;

	err_code = ft_data_validation(&data, argc, argv);
	if (err_code != PASS)
		return (ft_freedom(data), err_code);
	err_code = ft_process_map(&data, argv);
	if (err_code != PASS)
		return (ft_freedom(data), err_code);
	ft_game_start(&data);
	ft_raycasting(&data);
	mlx_hook(data->wind, 2, 1L << 0, ft_key_press, data);
	mlx_hook(data->wind, 3, 1L << 1, ft_key_release, data);
	mlx_loop_hook(data->mlx, ft_raycast_check, &data);
	mlx_loop(data->mlx);
	return (0);
}

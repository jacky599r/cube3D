/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:43:43 by nico              #+#    #+#             */
/*   Updated: 2025/08/14 19:57:34 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// int ft_extension_check(char *file, char *ext)
// {
// 	int len;

//     len = ft_strlen(file);
//     if (len < 5)
//     	return (ft_error_msg("Error File Name", file, NULL, 3));
// 	if (ft_strncmp(file + len - 4, ext, 4) != 0)
// 		return (ft_error_msg("Error File Name", file, NULL, 3));
//     return(0);
// }

// int ft_open_file(char *path)
// {
//     int dfd;
//     int fd;

//     dfd = open(path, O_RDONLY | __O_DIRECTORY);
//     if (dfd >= 0)
//     {
//         close(dfd);
//         return (ft_error_msg("File is Directory", path, NULL, 3));
//     }
//     if (errno != ENOTDIR)
//         return (ft_error_msg("File Error", path, NULL, FAIL));
//     fd = open(path, O_RDONLY);
//     if (fd < 0)
//         return (ft_error_msg("File Error", path, NULL, FAIL));
//     close (fd);
//     return (PASS);
// }

// int ft_data_validation(t_data *data, int argc,  char **argv)
// {
//     if (argc != 2)
//         return(FAIL);
//     ft_data_init(&data);
//     if (ft_extension_check(argv[1], ".cud") != PASS)
//         return (FAIL);
//     if (ft_open_file(argv[1]) != PASS)
//         return (FAIL);
//     return(PASS);
// }

// int ft_process_map(t_data *data, char **argv)
// {

// }

int	ft_raycast_check(t_data *d)
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

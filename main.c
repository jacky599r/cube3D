/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:38:53 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/19 15:07:48 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	mlx_hook(data->wind, 6, 1L << 6, ft_mouse_move, data);
	mlx_hook(data->wind, 8, 1L << 5, ft_mouse_leave, data);
	mlx_loop_hook(data->mlx, ft_raycast_check, data);
	mlx_loop(data->mlx);
	return (0);
}

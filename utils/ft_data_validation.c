/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:00:00 by jacky599r         #+#    #+#             */
/*   Updated: 2025/09/19 14:47:42 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_cleanup_validation_error(t_data *data)
{
	if (data->map.og_map)
		ft_safe_array((void ***)&data->map.og_map);
	if (data->map.fl_map)
		ft_safe_array((void ***)&data->map.fl_map);
	if (data->doors)
		ft_free_doors(data);
	if (data->coins)
		ft_free_coins(data);
}

int	ft_load_and_validate_file(t_data *data, char *filepath)
{
	data->map.og_map = ft_get_raw_map_data(filepath);
	if (!data->map.og_map)
		return (FAIL);
	if (ft_check_map_config(data) == FAIL)
	{
		ft_cleanup_validation_error(data);
		return (FAIL);
	}
	return (PASS);
}

int	ft_validate_map_structure(t_data *data)
{
	if (ft_prepare_map_for_flood_fill(data) == FAIL)
	{
		ft_cleanup_validation_error(data);
		return (FAIL);
	}
	ft_set_initial_player_view(data);
	if (ft_spawn_coins(data) == FAIL)
		return (FAIL);
	if (ft_validate_map_enclosure(data) == FAIL)
	{
		ft_cleanup_validation_error(data);
		return (FAIL);
	}
	return (PASS);
}

int	ft_data_validation(t_data *data, int argc, char **argv)
{
	int	err_code;

	ft_data_init(data);
	err_code = ft_validate_arguments(argc, argv);
	if (err_code != PASS)
		return (err_code);
	err_code = ft_load_and_validate_file(data, argv[1]);
	if (err_code != PASS)
		return (err_code);
	err_code = ft_validate_map_structure(data);
	if (err_code != PASS)
		return (err_code);
	return (PASS);
}

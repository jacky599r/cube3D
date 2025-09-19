/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:02:46 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/19 16:25:01 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_identify_map_properties(t_data *data, int start_index)
{
	int		curr_line_index;
	int		error_code;
	char	*trimmed_check;

	curr_line_index = start_index;
	data->map.high = 0;
	data->map.wide = 0;
	while (data->map.og_map[curr_line_index])
	{
		trimmed_check = ft_whitetrim(data->map.og_map[curr_line_index]);
		if (ft_is_empty_line(trimmed_check))
		{
			free(trimmed_check);
			break ;
		}
		free(trimmed_check);
		error_code = ft_parse_map_content(data, curr_line_index, start_index);
		if (error_code != PASS)
			return (error_code);
		curr_line_index++;
	}
	if (data->play.s_dir == '\0')
		return (ft_error_msg("Error", "No player found in map", 5));
	return (PASS);
}

static int	ft_handle_empty_line(t_data *data, char *trimmed_line)
{
	if (data->map_start_index != -1 && !data->map.eom)
		data->map.eom = 1;
	free(trimmed_line);
	return (PASS);
}

static int	ft_process_single_line(t_data *data, int i)
{
	char	*trimmed_line;
	int		error_code;

	trimmed_line = ft_whitetrim(data->map.og_map[i]);
	if (ft_is_empty_line(trimmed_line))
	{
		ft_handle_empty_line(data, trimmed_line);
		return (PASS);
	}
	error_code = ft_process_file_line(data, trimmed_line);
	free(trimmed_line);
	return (error_code);
}

int	ft_parse_file_structure(t_data *data, int *map_start_index)
{
	int	i;
	int	error_code;

	i = 0;
	error_code = PASS;
	data->param_count = 0;
	data->map_start_index = -1;
	while (data->map.og_map[i] && error_code == PASS)
	{
		data->curr_line_index = i;
		error_code = ft_process_single_line(data, i);
		i++;
	}
	if (data->param_count != 6 && error_code == PASS)
		error_code = ft_error_msg("Error", "Incorrect texture/colours params",
				4);
	*map_start_index = data->map_start_index;
	return (error_code);
}

int	ft_check_map_config(t_data *data)
{
	int	error_code;
	int	map_start_index;

	error_code = ft_parse_file_structure(data, &map_start_index);
	if (error_code != PASS)
		return (error_code);
	if (map_start_index == -1)
		return (ft_error_msg("Error", "No map found in file", 5));
	data->map.start_index = map_start_index;
	return (ft_identify_map_properties(data, map_start_index));
}

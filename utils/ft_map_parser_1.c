/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parser_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:30:00 by jacky599r         #+#    #+#             */
/*   Updated: 2025/09/22 06:19:51 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != 'D'
			&& line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	ft_validate_map_characters(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_is_valid_map_char(line[i]))
			return (ft_error_msg("Error: Invalid character in map", line,
					5));
		i++;
	}
	return (PASS);
}

int	ft_process_player_info(t_data *data, char player_char, int x_pos,
		int y_idx)
{
	if (data->play.s_dir != '\0')
		return (ft_error_msg("Error", "Only 1 player allowed", 5));
	data->play.s_dir = player_char;
	data->play.pos.x = (double)x_pos + 0.5;
	data->play.pos.y = (double)y_idx + 0.5;
	return (PASS);
}

int	ft_parse_map_content(t_data *data, int line_index, int start_index)
{
	char	*line;

	line = data->map.og_map[line_index];
	if (ft_validate_map_characters(line) != PASS)
		return (FAIL);
	if (ft_scan_map_line(data, line, line_index - start_index) != PASS)
		return (FAIL);
	ft_update_map_dims(data, line);
	return (PASS);
}

int	ft_process_file_line(t_data *data, char *trimmed_line)
{
	if (data->map_start_index == -1 && ft_is_valid_param(trimmed_line))
	{
		if (ft_process_param_line(data, trimmed_line) != PASS)
			return (FAIL);
		data->param_count++;
	}
	else if (data->map_start_index == -1 && ft_is_map_line(trimmed_line))
		data->map_start_index = data->curr_line_index;
	else if (data->map_start_index != -1 && data->map.eom)
		return (ft_error_msg("Error", "Data after map data", FAIL));
	else if (data->map_start_index == -1 && !ft_is_valid_param(trimmed_line))
		return (ft_error_msg("Error: Invalid line in file", trimmed_line,
				FAIL));
	return (PASS);
}

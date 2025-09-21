/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parser_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 05:25:48 by nico              #+#    #+#             */
/*   Updated: 2025/09/22 05:40:28 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_handle_tile(t_data *data, char c, int x, int y)
{
	if (ft_strchr("NSEW", c))
		return (ft_process_player_info(data, c, x, y));
	if (c == 'D')
		return (ft_register_door(data, x, y));
	return (PASS);
}

int	ft_scan_map_line(t_data *data, const char *line, int map_y)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_handle_tile(data, line[i], i, map_y) != PASS)
			return (FAIL);
		i++;
	}
	return (PASS);
}

void	ft_update_map_dims(t_data *data, char *line)
{
	int	current_width;

	ft_strip_line_endings(line);
	current_width = ft_strlen(line);
	if (current_width > data->map.wide)
		data->map.wide = current_width;
	data->map.high++;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_to_fill.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:50:00 by jacky599r         #+#    #+#             */
/*   Updated: 2025/09/17 20:01:08 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	convert_map_char(char c)
{
	if (c == '0' || c == '1' || ft_strchr("NSEW", c))
		return (c);
	else if (c == ' ')
		return ('0');
	else if (c == 'D')
		return ('D');
	else
		return ('X');
}

static void	fill_map_row(char *fl_row, char *temp_line, int width)
{
	int	x;
	int	line_len;

	line_len = ft_strlen(temp_line);
	x = 0;
	while (x < width)
	{
		if (x < line_len)
			fl_row[x] = convert_map_char(temp_line[x]);
		else
			fl_row[x] = '0';
		x++;
	}
	fl_row[x] = '\0';
}

static int	process_map_line(t_data *data, int y)
{
	char	*temp_line;

	temp_line = ft_strdup(data->map.og_map[y + data->map.start_index]);
	if (!temp_line)
		return (FAIL);
	ft_strip_line_endings(temp_line);
	fill_map_row(data->map.fl_map[y], temp_line, data->map.wide);
	free(temp_line);
	return (PASS);
}

int	convert_to_flood_map(t_data *data)
{
	int	y;

	y = 0;
	while (y < data->map.high)
	{
		if (process_map_line(data, y) == FAIL)
			return (FAIL);
		y++;
	}
	return (PASS);
}

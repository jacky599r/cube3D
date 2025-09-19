/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:49:31 by jacky599r         #+#    #+#             */
/*   Updated: 2025/09/19 16:15:30 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	**ft_add_line_to_array(char **cur_map, char *new_line, int cur_size)
{
	char	**new_map;
	int		j;

	new_map = ft_calloc(cur_size + 2, sizeof(char *));
	if (!new_map)
		return (ft_safe_array((void ***)&cur_map), free(new_line), NULL);
	j = 0;
	while (j < cur_size)
	{
		new_map[j] = cur_map[j];
		cur_map[j] = NULL;
		j++;
	}
	new_map[cur_size] = ft_strdup(new_line);
	free(new_line);
	if (!new_map[cur_size])
	{
		ft_safe_array((void ***)&new_map);
		ft_safe_array((void ***)&cur_map);
		return (NULL);
	}
	return (ft_safe_array((void ***)&cur_map), new_map);
}

char	**ft_read_lines_into_array(int fd)
{
	char	*line;
	char	**temp_map;
	char	**new_map;
	int		i;

	temp_map = NULL;
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		new_map = ft_add_line_to_array(temp_map, line, i);
		if (!new_map)
		{
			close(fd);
			return (NULL);
		}
		temp_map = new_map;
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (temp_map);
}

int	ft_check_for_empty_file(char **map_array, char *path)
{
	if (map_array == NULL)
	{
		return (ft_error_msg("Error: Empty map file", path, FAIL));
	}
	return (PASS);
}

char	**ft_get_raw_map_data(char *path)
{
	int		fd;
	char	**raw_map;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_error_msg("Error: Unable to open map file", path, FAIL),
			NULL);
	raw_map = ft_read_lines_into_array(fd);
	if (ft_check_for_empty_file(raw_map, path) == FAIL)
		return (NULL);
	return (raw_map);
}

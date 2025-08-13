/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:49:31 by jacky599r         #+#    #+#             */
/*   Updated: 2025/08/12 17:57:12 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int ft_open_map_file(char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (ft_error_msg("Error", "Unable to open map file", path, FAIL));
    return (fd);
}

static char **ft_add_line_to_array(char **current_map, char *new_line, int current_size)
{
    char **new_map;
    int j;

    new_map = ft_calloc(sizeof(char *) * (current_size + 2));
    if (!new_map)
    {
        ft_safe_array((void ***)&current_map);
        free(new_line);
        return (NULL);
    }
    j = 0;
    while (j < current_size)
    {
        new_map[j] = current_map[j];
        j++;
    }
    new_map[current_size] = ft_strdup(new_line);
    free(new_line);
    if (!new_map[current_size])
    {
        ft_safe_array((void ***)&new_map);
        ft_safe_array((void ***)&current_map);
        return (NULL);
    }
    return (ft_safe_array((void ***)&current_map), new_map);
}

char **ft_read_lines_into_array(int fd)
{
    char *line;
    char **temp_map;
    int i;

    temp_map = NULL;
    i = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        temp_map = ft_add_line_to_array(temp_map, line, i);
        if (!temp_map)
            return (NULL);
        i++;
    }
    close(fd);
    return (temp_map);
}

int ft_check_for_empty_file(char **map_array, char *path)
{
    if (map_array == NULL)
    {
        ft_safe_array((void ***)&map_array);
        return (ft_error_msg("Error", "Empty map file", path, FAIL));
    }
    return (PASS);
}

char **ft_get_raw_map_data(char *path)
{
    int fd;
    char **raw_map;

    fd = ft_open_map_file(path);
    if (fd == FAIL)
        return (NULL);
    raw_map = ft_read_lines_into_array(fd);
    if (ft_check_for_empty_file(raw_map, path) == FAIL)
        return (NULL);
    return (raw_map);
}

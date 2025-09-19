/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_param_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:51:29 by jacky599r         #+#    #+#             */
/*   Updated: 2025/09/17 21:50:26 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int ft_parse_texture_line(t_data *data, char *line)
{
    char *type_id;
    int result;

    type_id = ft_strndup(line, 2);
    if (!type_id)
        return (ft_error_msg("Error", "Memory allocation failed", NULL, FAIL));
    result = ft_parse_texture_path(data, line, type_id);
    free(type_id);
    return (result);
}

static int ft_parse_color_line(t_data *data, char *line)
{
    char *type_id;
    int result;

    type_id = ft_strndup(line, 1);
    if (!type_id)
        return (ft_error_msg("Error", "Memory allocation failed", NULL, FAIL));
    result = ft_parse_color_values(data, line, type_id);
    free(type_id);
    return (result);
}

static int ft_handle_texture_param(t_data *data, char *line)
{
    if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 || 
        ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
        return (ft_parse_texture_line(data, line));
    return (PASS);
}

static int ft_handle_color_param(t_data *data, char *line)
{
    if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
        return (ft_parse_color_line(data, line));
    return (PASS);
}

int ft_process_param_line(t_data *data, char *line)
{
    if (!ft_is_valid_param(line))
        return (PASS);
    if (ft_handle_texture_param(data, line) != PASS)
        return (FAIL);
    if (ft_handle_color_param(data, line) != PASS)
        return (FAIL);
    return (PASS);
}
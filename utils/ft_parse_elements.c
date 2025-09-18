/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:03:16 by jacky599r         #+#    #+#             */
/*   Updated: 2025/09/17 21:45:32 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int ft_process_param_line(t_data *data, char *line)
{
    if (ft_strncmp(line, "NO ", 3) == 0)
        return (ft_parse_texture_path(data, line, "NO"));
    else if (ft_strncmp(line, "SO ", 3) == 0)
        return (ft_parse_texture_path(data, line, "SO"));
    else if (ft_strncmp(line, "WE ", 3) == 0)
        return (ft_parse_texture_path(data, line, "WE"));
    else if (ft_strncmp(line, "EA ", 3) == 0)
        return (ft_parse_texture_path(data, line, "EA"));
    else if (ft_strncmp(line, "F ", 2) == 0)
        return (ft_parse_color_values(data, line, "F"));
    else if (ft_strncmp(line, "C ", 2) == 0)
        return (ft_parse_color_values(data, line, "C"));
    return (ft_error_msg("Error", "Unknown param", line, FAIL));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_param_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:51:29 by jacky599r         #+#    #+#             */
/*   Updated: 2025/08/15 18:27:20 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int ft_is_valid_param_identifier(char *line)
{
    if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
        return (1);
    return (0);
}

int ft_check_duplicate_param(t_data *data, char *type_id)
{
    if (ft_strncmp(type_id, "NO", 2) == 0 && data->text.txt_n)
        return (ft_error_msg("Error", "Duplicate texture 'NO'", NULL, FAIL));
    if (ft_strncmp(type_id, "SO", 2) == 0 && data->text.txt_s)
        return (ft_error_msg("Error", "Duplicate texture 'SO'", NULL, FAIL));
    if (ft_strncmp(type_id, "WE", 2) == 0 && data->text.txt_w)
        return (ft_error_msg("Error", "Duplicate texture 'WE'", NULL, FAIL));
    if (ft_strncmp(type_id, "EA", 2) == 0 && data->text.txt_e)
        return (ft_error_msg("Error", "Duplicate texture 'EA'", NULL, FAIL));
    if (ft_strncmp(type_id, "F", 1) == 0 && data->text.rgb_g) 
        return (ft_error_msg("Error", "Duplicate color 'F'", NULL, FAIL));
    if (ft_strncmp(type_id, "C", 1) == 0 && data->text.rgb_c)
        return (ft_error_msg("Error", "Duplicate color 'C'", NULL, FAIL));
    return (PASS);
}

static int ft_validate_rgb_and_convert(char *rgb_str, int *r, int *g, int *b)
{
    char **rgb_components;
    int checker;

    rgb_components = ft_split(rgb_str, ',');
    if (!rgb_components || !rgb_components[0] || !rgb_components[1] || !rgb_components[2] || rgb_components[3] != NULL)
    {
        ft_safe_array((void ***)&rgb_components);
        return (ft_error_msg("Error", "Invalid colour format", NULL, FAIL));
    }
    if (!ft_is_num(rgb_components[0]) || !ft_is_num(rgb_components[1]) || !ft_is_num(rgb_components[2]))
    {
        ft_safe_array((void ***)&rgb_components);
        return (ft_error_msg("Error", "RGB must be in numerics", NULL, FAIL));
    }
    *r = ft_atoi(rgb_components[0]);
    *g = ft_atoi(rgb_components[1]);
    *b = ft_atoi(rgb_components[2]);
    checker = PASS;
    if (ft_is_rgb_within_range(*r, *g, *b) != PASS)
        checker = ft_error_msg("Error", "RGB must be [0 to 255]", NULL, FAIL);
    ft_safe_array((void ***)&rgb_components);
    return (checker);
}

int ft_is_rgb_within_range(int r, int g, int b)
{
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (FAIL);
    return (PASS);
}

unsigned long ft_convert_rgb_to_int(int r, int g, int b)
{
    return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

int ft_parse_texture_path(t_data *data, char *line, char *type_id)
{
    char *path;
    int fd;

    path = ft_strtrim(line + ft_strlen(type_id) + 1, " \t\n\r\v\f");
    if (!path || *path == '\0')
        return (ft_error_msg("Error", "Missing texture path", type_id, FAIL));
    if (ft_check_duplicate_param(data, type_id) != PASS)
        return (free(path), FAIL);
    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        free(path);
        return (ft_error_msg("Error","Texture file not found or unreadable", NULL, FAIL));
    }
    close (fd);
    if (ft_strncmp(type_id, "NO", 2) == 0)
        data->text.txt_n = path;
    else if (ft_strncmp(type_id, "SO", 2) == 0)
        data->text.txt_s = path;
    else if (ft_strncmp(type_id, "WE", 2) == 0)
        data->text.txt_w = path;
    else if (ft_strncmp(type_id, "EA", 2) == 0)
        data->text.txt_e = path;
    return (PASS);
}

int ft_parse_color_values(t_data *data, char *line, char *type_id)
{
    int r;
    int g;
    int b;
    unsigned long colour;
    char *rgb_string;

    rgb_string = ft_strtrim(line + ft_strlen(type_id) + 1, " \n\t\r\v\f");
    if (!rgb_string || *rgb_string == '\0')
        return (ft_error_msg("Error", "Missing colour values", type_id, FAIL));
    if (ft_check_duplicate_param(data, type_id) != PASS)
        return (free(rgb_string), FAIL);
    if (ft_validate_rgb_and_convert(rgb_string, &r, &g, &b) != PASS)
        return (free(rgb_string), FAIL);
    free(rgb_string);
    colour = ft_convert_rgb_to_int(r, g, b);
    if (ft_strncmp(type_id, "F", 1) == 0)
    {
        data->text.rgb_g = malloc(sizeof(unsigned long));
        if (!data->text.rgb_g)
            return (ft_error_msg("Error", "Memory allocation failed", NULL, FAIL));
        *(data->text.rgb_g) = colour;
    }
    else if (ft_strncmp(type_id, "C", 1) == 0)
    {
        data->text.rgb_c = malloc(sizeof(unsigned long));
        if (!data->text.rgb_c)
            return (ft_error_msg("Error", "Memory allocation failed", NULL, FAIL));
        *(data->text.rgb_c) = colour;
    }
    return (PASS);
}

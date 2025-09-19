/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jacky599r         #+#    #+#             */
/*   Updated: 2025/09/19 16:13:07 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_is_rgb_within_range(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (FAIL);
	return (PASS);
}

unsigned long	ft_convert_rgb_to_int(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

static int	ft_validate_rgb_and_convert(char *rgb_str, int *r, int *g, int *b)
{
	char	**rgb_components;
	int		checker;

	rgb_components = ft_split(rgb_str, ',');
	if (!rgb_components || !rgb_components[0] || !rgb_components[1]
		|| !rgb_components[2] || rgb_components[3] != NULL)
	{
		ft_safe_array((void ***)&rgb_components);
		return (ft_error_msg("Error", "Invalid colour format", 4));
	}
	if (!ft_is_num(rgb_components[0]) || !ft_is_num(rgb_components[1])
		|| !ft_is_num(rgb_components[2]))
	{
		ft_safe_array((void ***)&rgb_components);
		return (ft_error_msg("Error", "RGB must be in numerics", 4));
	}
	*r = ft_atoi(rgb_components[0]);
	*g = ft_atoi(rgb_components[1]);
	*b = ft_atoi(rgb_components[2]);
	checker = PASS;
	if (ft_is_rgb_within_range(*r, *g, *b) != PASS)
		checker = ft_error_msg("Error", "Invalid colour format", 4);
	ft_safe_array((void ***)&rgb_components);
	return (checker);
}

static int	ft_assign_color_to_data(t_data *data, char *type_id,
		unsigned long colour)
{
	if (ft_strncmp(type_id, "F", 1) == 0)
	{
		data->text.rgb_g = malloc(sizeof(unsigned long));
		if (!data->text.rgb_g)
			return (ft_error_msg("Error", "Malloc Failure", FAIL));
		*(data->text.rgb_g) = colour;
	}
	else if (ft_strncmp(type_id, "C", 1) == 0)
	{
		data->text.rgb_c = malloc(sizeof(unsigned long));
		if (!data->text.rgb_c)
			return (ft_error_msg("Error", "Malloc Failure", FAIL));
		*(data->text.rgb_c) = colour;
	}
	return (PASS);
}

int	ft_parse_color_values(t_data *data, char *line, char *type_id,
		unsigned long colour)
{
	char	*rgb_string;
	int		r;
	int		g;
	int		b;

	rgb_string = ft_whitetrim(line + ft_strlen(type_id) + 1);
	if (!rgb_string || *rgb_string == '\0')
		return (ft_error_msg("Error: Missing Colour Values", type_id, 4));
	if (ft_check_duplicate_param(data, type_id) != PASS)
		return (free(rgb_string), FAIL);
	if (ft_validate_rgb_and_convert(rgb_string, &r, &g, &b) != PASS)
		return (free(rgb_string), FAIL);
	free(rgb_string);
	colour = ft_convert_rgb_to_int(r, g, b);
	return (ft_assign_color_to_data(data, type_id, colour));
}

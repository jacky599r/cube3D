/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jacky599r         #+#    #+#             */
/*   Updated: 2025/09/19 16:11:47 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_is_valid_param(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "DD ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

int	ft_check_duplicate_param(t_data *data, char *type_id)
{
	if (ft_strncmp(type_id, "NO", 2) == 0 && data->text.txt_n)
		return (ft_error_msg("Error", "Duplicate texture 'NO'", 4));
	if (ft_strncmp(type_id, "SO", 2) == 0 && data->text.txt_s)
		return (ft_error_msg("Error", "Duplicate texture 'SO'", 4));
	if (ft_strncmp(type_id, "WE", 2) == 0 && data->text.txt_w)
		return (ft_error_msg("Error", "Duplicate texture 'WE'", 4));
	if (ft_strncmp(type_id, "EA", 2) == 0 && data->text.txt_e)
		return (ft_error_msg("Error", "Duplicate texture 'EA'", 4));
	if (ft_strncmp(type_id, "DD", 2) == 0 && data->text.txt_d)
		return (ft_error_msg("Error", "Duplicate texture 'DD'", 4));
	if (ft_strncmp(type_id, "F", 1) == 0 && data->text.rgb_g)
		return (ft_error_msg("Error", "Duplicate color 'F'", 4));
	if (ft_strncmp(type_id, "C", 1) == 0 && data->text.rgb_c)
		return (ft_error_msg("Error", "Duplicate color 'C'", 4));
	return (PASS);
}

static int	ft_assign_texture_to_data(t_data *data, char *type_id, char *path)
{
	if (ft_strncmp(type_id, "NO", 2) == 0)
		data->text.txt_n = path;
	else if (ft_strncmp(type_id, "SO", 2) == 0)
		data->text.txt_s = path;
	else if (ft_strncmp(type_id, "WE", 2) == 0)
		data->text.txt_w = path;
	else if (ft_strncmp(type_id, "EA", 2) == 0)
		data->text.txt_e = path;
	else if (ft_strncmp(type_id, "DD", 2) == 0)
		data->text.txt_d = path;
	return (PASS);
}

int	ft_parse_texture_path(t_data *data, char *line, char *type_id)
{
	char	*path;
	int		fd;
	char	*error_path;

	path = ft_whitetrim(line + ft_strlen(type_id) + 1);
	if (!path || *path == '\0')
		return (free(path), ft_error_msg("Error: Missing texture path",
				type_id, 3));
	if (ft_check_duplicate_param(data, type_id) != PASS)
		return (free(path), FAIL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		error_path = ft_strdup(path);
		free(path);
		ft_error_msg("Error: Texture file not found or unreadable",
			error_path, 3);
		free(error_path);
		return (FAIL);
	}
	close(fd);
	return (ft_assign_texture_to_data(data, type_id, path));
}

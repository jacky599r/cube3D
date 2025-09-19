/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:00:00 by jacky599r         #+#    #+#             */
/*   Updated: 2025/09/19 15:53:44 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_extension_check(char *file)
{
	int	len;

	if (!file)
		return (ft_error_msg("Error", "No file specified", 2));
	len = ft_strlen(file);
	if (len < 5)
		return (ft_error_msg("Error", "File name too short", 2));
	if (ft_strncmp(file + len - 4, ".cub", 4) != 0)
		return (ft_error_msg("Error", "Invalid file extension", 2));
	return (PASS);
}

int	ft_validate_arguments(int argc, char **argv)
{
	if (argc != 2)
		return (ft_error_msg("Error", "Invalid number of arguments", 2));
	if (!argv[1])
		return (ft_error_msg("Error", "No file specified", 2));
	if (ft_extension_check(argv[1]) != PASS)
		return (FAIL);
	return (PASS);
}

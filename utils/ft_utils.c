/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:51:49 by jacky599r         #+#    #+#             */
/*   Updated: 2025/09/16 14:22:04 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Placeholder for ft_is_num (will be moved from ft_parse_elements.c)
int ft_is_num(char *str)
{
    int i = 0;
    if (!str || *str == '\0')
        return (0);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

// Placeholder for ft_is_empty_line (will be moved from ft_map_validation.c)
int ft_is_empty_line(char *line)
{
    int i;

    i = 0;
    while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\n' || line[i] == '\t' || line[i] == '\r' || line[i] == '\v' || line[i] == '\f'))
        i++;
    return (line[i] == '\0');
}

// ft_error_msg implementation moved to exit_error/ft_messaging.c

// ft_safe_array implementation moved to exit_error/ft_exit.c

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validation_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/XX XX:XX:XX by jacky599r         #+#    #+#             */
/*   Updated: 2025/01/XX XX:XX:XX by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


int ft_is_empty_line(char *line)
{
    int i;

    i = 0;
    while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\n' || 
           line[i] == '\t' || line[i] == '\r' || line[i] == '\v' || 
           line[i] == '\f'))
        i++;
    return (line[i] == '\0');
}

int ft_is_valid_map_char(char c)
{
    if (c == '0' || c == '1')
        return (1);
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
        return (1);
    if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || 
        c == '\f' || c == '\r')
        return (1);
    return (0);
}


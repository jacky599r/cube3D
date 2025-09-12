/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:51:49 by jacky599r         #+#    #+#             */
/*   Updated: 2025/08/14 17:21:37 by jacky599r        ###   ########.fr       */
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

// Placeholder for ft_error_msg (will be moved from ft_messaging.c)
int ft_error_msg(char *err_type, char *msg, char *context, int ret_code)
{
    ft_putstr_fd(err_type, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(msg, 2);
    if (context)
    {
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(context, 2);
    }
    ft_putstr_fd("\n", 2);
    return (ret_code);
}

// Placeholder for ft_safe_array (will be moved from ft_free.c if it exists)
void ft_safe_array(void ***arr)
{
    int i;
    void **array_ptr;

    if (!arr || !*arr)
        return;
    array_ptr = *arr;
    i = 0;
    while (array_ptr[i])
    {
        free(array_ptr[i]);
        i++;
    }
    free(array_ptr);
    *arr = NULL;
}

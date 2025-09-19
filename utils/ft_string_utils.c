/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/XX XX:XX:XX by jacky599r         #+#    #+#             */
/*   Updated: 2025/01/XX XX:XX:XX by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char *ft_whitetrim(char *str)
{
    return (ft_strtrim(str, " \n\t\v\f\r"));
}

char *ft_strip_line_endings(char *str)
{
    int len;
    
    if (!str)
        return (str);
    len = ft_strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r'))
    {
        str[len - 1] = '\0';
        len--;
    }
    return (str);
}

char *ft_strndup(const char *str, size_t n)
{
    char *dup;
    size_t len;
    size_t i;

    if (!str)
        return (NULL);
    len = ft_strlen(str);
    if (n < len)
        len = n;
    dup = malloc(sizeof(char) * (len + 1));
    if (!dup)
        return (NULL);
    i = 0;
    while (i < len)
    {
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

static int ft_is_digit_char(char c)
{
    return (c >= '0' && c <= '9');
}

int ft_is_num(char *str)
{
    int i;

    i = 0;
    if (!str || *str == '\0')
        return (0);
    while (str[i])
    {
        if (!ft_is_digit_char(str[i]))
            return (0);
        i++;
    }
    return (1);
}

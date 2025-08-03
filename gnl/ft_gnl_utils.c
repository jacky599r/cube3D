/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:30:28 by nsamarin          #+#    #+#             */
/*   Updated: 2025/03/26 16:05:58 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_mem_alloc_fill(int nb, int size)
{
	char	*str;
	int		len;
	int		a;

	a = 0;
	len = nb * size;
	str = malloc(nb * size);
	if (!str)
		return (NULL);
	while (a < len - 1)
	{
		str[a] = 0;
		a++;
	}
	str[a] = '\0';
	return (str);
}

int	ft_str_len(char *str)
{
	int	a;

	a = 0;
	if (!str)
		return (0);
	while (str[a])
		a++;
	return (a);
}

int	ft_new_line(char *temporary)
{
	int	a;

	a = 0;
	while (temporary[a] != '\0')
	{
		if (temporary[a] == '\n')
		{
			return (1);
		}
		a++;
	}
	return (0);
}

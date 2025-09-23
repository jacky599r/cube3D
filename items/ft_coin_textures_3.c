/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coin_textures_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:37:39 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/23 13:59:09 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_uint_len(unsigned int n)
{
	int	len;

	len = 1;
	while (n >= 10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	ft_uint_write(unsigned int n, char *dst, size_t len)
{
	dst[len] = '\0';
	while (len > 0)
	{
		len--;
		dst[len] = (char)('0' + (n % 10));
		n = n / 10;
	}
}

int	ft_uint_to_str(unsigned int n, char *dst, size_t cap)
{
	size_t	len;

	if (!dst || cap == 0)
		return (0);
	if (n == 0)
	{
		if (cap < 2)
			return (0);
		dst[0] = '0';
		dst[1] = '\0';
		return (1);
	}
	len = (size_t)ft_uint_len(n);
	if (len + 1 > cap)
		return (0);
	ft_uint_write(n, dst, len);
	return (1);
}

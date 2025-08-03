/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:12:03 by nsamarin          #+#    #+#             */
/*   Updated: 2024/06/19 16:29:28 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	unsigned char	*e;
	unsigned char	*f;
	size_t			d;

	d = 0;
	e = (unsigned char *)dest;
	f = (unsigned char *)src;
	if (!e && !f)
		return (0);
	while (d < size)
	{
		*(unsigned char *)(dest + d) = *(unsigned char *)(src + d);
		d++;
	}
	return (dest);
}

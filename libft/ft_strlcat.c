/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:56:08 by nsamarin          #+#    #+#             */
/*   Updated: 2024/06/19 13:06:47 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	d;
	size_t	e;
	size_t	f;

	d = 0;
	e = 0;
	f = 0;
	if ((!dest || !src) && !size)
		return (0);
	while (dest[d])
		d++;
	while (src[e])
		e++;
	if (size <= d)
		return (size + e);
	while (d + f < (size - 1) && src[f])
	{
		dest[d + f] = src[f];
		f++;
	}
	dest[d + f] = 0;
	return (d + e);
}

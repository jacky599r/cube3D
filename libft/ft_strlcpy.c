/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:06:46 by nsamarin          #+#    #+#             */
/*   Updated: 2024/06/18 16:10:07 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	d;

	d = 0;
	if (size > 0)
	{
		while (d < (size - 1) && src[d])
		{
			dest[d] = src[d];
			d ++;
		}
		dest[d] = '\0';
	}
	while (src[d])
		d ++;
	return (d);
}

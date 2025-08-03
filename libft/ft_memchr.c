/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:28:24 by nsamarin          #+#    #+#             */
/*   Updated: 2024/06/20 13:05:40 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int a, size_t size)
{
	size_t	b;

	b = 0;
	while (b < size)
	{
		if (*(unsigned char *)(str + b) == (unsigned char)a)
			return ((void *)(str + b));
		b++;
	}
	return (NULL);
}

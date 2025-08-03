/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:10:03 by nsamarin          #+#    #+#             */
/*   Updated: 2024/06/20 11:18:09 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t a)
{
	size_t	b;

	b = 0;
	while (b < a)
	{
		if (*(unsigned char *)(str1 + b) != *(unsigned char *)(str2 + b))
			return (*(unsigned char *)(str1 + b) - *(unsigned char *)(str2
					+ b));
		b++;
	}
	return (0);
}

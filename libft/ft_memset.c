/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:20:13 by nsamarin          #+#    #+#             */
/*   Updated: 2024/06/14 16:38:04 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int b, size_t c)
{
	size_t	d;

	d = 0;
	while (d < c)
	{
		*(unsigned char *)(str + d) = (unsigned char)b;
		d++;
	}
	return (str);
}

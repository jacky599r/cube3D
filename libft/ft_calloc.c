/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:31:28 by nsamarin          #+#    #+#             */
/*   Updated: 2025/03/27 12:15:03 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nb, size_t size)
{
	void	*a;

	if (nb * size > 2147483647)
		return (NULL);
	if (nb == 0 || size == 0)
	{
		nb = 0;
		size = 1;
	}
	a = (void *)malloc(nb * size);
	if (!a)
		return (NULL);
	ft_bzero(a, nb * size);
	return (a);
}

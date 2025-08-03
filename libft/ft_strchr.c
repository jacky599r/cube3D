/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:41:34 by nsamarin          #+#    #+#             */
/*   Updated: 2024/06/19 11:19:28 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int a)
{
	unsigned char	c;
	int				b;

	b = 0;
	c = (unsigned char)a;
	while (str[b])
	{
		if (str[b] == c)
			return ((char *)(str + b));
		b++;
	}
	if (str[b] == c)
		return ((char *)(str + b));
	return (NULL);
}

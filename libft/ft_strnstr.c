/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:29:23 by nsamarin          #+#    #+#             */
/*   Updated: 2024/06/19 09:55:36 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *ndl, size_t a)
{
	size_t	b;
	size_t	c;

	b = 0;
	c = 0;
	while (ndl[c])
		c++;
	if (c == 0 || hay == ndl)
		return ((char *)hay);
	while (hay[b] && b < a)
	{
		c = 0;
		while (hay[b + c] == ndl[c] && (b + c) < a)
		{
			if (ndl[c + 1] == '\0')
				return ((char *)hay + b);
			c++;
		}
		b++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:01:17 by nsamarin          #+#    #+#             */
/*   Updated: 2024/06/20 10:50:56 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int a)
{
	char			*b;
	int				c;
	unsigned char	d;

	b = NULL;
	c = 0;
	d = (unsigned char)a;
	while (str[c])
	{
		if (str[c] == d)
			b = (char *)(str + c);
		c++;
	}
	if (str[c] == d)
		return ((char *)(str + c));
	return (b);
}

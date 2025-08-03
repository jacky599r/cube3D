/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:16:43 by nsamarin          #+#    #+#             */
/*   Updated: 2024/06/18 11:32:52 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t		a;
	size_t		b;
	char		*c;

	a = 0;
	b = 0;
	while (s[b])
		b++;
	c = (char *)malloc(sizeof(char) * (b + 1));
	if (!c)
		return (NULL);
	while (s[a])
	{
		c[a] = f(a, s[a]);
		a++;
	}
	c[a] = '\0';
	return (c);
}

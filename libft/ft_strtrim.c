/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:08:59 by nsamarin          #+#    #+#             */
/*   Updated: 2024/06/18 15:30:16 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	validity(char const *str, char const c)
{
	size_t	e;

	e = 0;
	while (str[e])
	{
		if (str[e] == c)
			return (1);
		e++;
	}
	return (0);
}

static size_t	newstrlen(const char *str)
{
	size_t	d;

	d = 0;
	while (str[d])
		d++;
	return (d);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		a;
	size_t		b;
	size_t		c;
	char		*nstrm;

	a = 0;
	b = newstrlen(s1);
	c = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[a] && (validity(set, s1[a])) == 1)
		a++;
	while (b > a && (validity(set, s1[b - 1])) == 1)
		b--;
	nstrm = (char *)malloc(sizeof(char) * ((b - a) + 1));
	if (!nstrm)
		return (NULL);
	while ((a + c) < b)
	{
		nstrm[c] = s1[a + c];
		c++;
	}
	nstrm[c] = '\0';
	return (nstrm);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:15:57 by nsamarin          #+#    #+#             */
/*   Updated: 2024/06/18 15:29:39 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	count_substr(char const *str, char c)
{
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
	while (str[a])
	{
		if (str[a] != c)
		{
			b++;
			while (str[a] && str[a] != c)
				a++;
		}
		else if (str[a] == c)
			a++;
	}
	return (b);
}

static void	ft_free(char **nstr, size_t d)
{
	while (d > 0)
	{
		d--;
		free(*(nstr + d));
	}
	free (nstr);
}

static size_t	word_len(char const *str, char c)
{
	size_t	h;

	h = 0;
	while (str[h] && str[h] != c)
		h++;
	return (h);
}

static char	**fill_newstr(char **nstr, size_t e, char const *str, char c)
{
	size_t	f;
	size_t	g;

	f = 0;
	g = 0;
	while (f < e)
	{
		while (str[g] && str[g] == c)
			g++;
		*(nstr + f) = ft_substr(str, g, word_len(&str[g], c));
		if (!*(nstr + f))
		{
			ft_free(nstr, f);
			return (0);
		}
		while (str[g] && str[g] != c)
			g++;
		f++;
	}
	*(nstr + f) = NULL;
	return (nstr);
}

char	**ft_split(char const *s, char c)
{
	char		**newstr;
	size_t		h;

	if (!s)
		return (NULL);
	h = count_substr(s, c);
	newstr = (char **)malloc(sizeof(char *) * (h + 1));
	if (!newstr)
		return (NULL);
	newstr = fill_newstr(newstr, h, s, c);
	return (newstr);
}

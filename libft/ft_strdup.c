/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:59:06 by nsamarin          #+#    #+#             */
/*   Updated: 2024/06/20 13:05:27 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		a;
	char	*dup;

	a = 0;
	while (str[a])
		a++;
	dup = (char *)malloc(sizeof(*str) * (a + 1));
	if (!dup)
		return (NULL);
	a = 0;
	while (str[a])
	{
		dup[a] = str[a];
		a++;
	}
	dup[a] = '\0';
	return (dup);
}

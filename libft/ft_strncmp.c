/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:15:20 by nsamarin          #+#    #+#             */
/*   Updated: 2024/06/19 09:58:44 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t a)
{
	size_t	b;

	b = 0;
	if (a == 0)
		return (0);
	while (str1[b] == str2[b] && b < (a - 1) && str1[b] && str2[b])
		b++;
	return ((unsigned char)str1[b] - (unsigned char)str2[b]);
}

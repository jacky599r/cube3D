/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:14:57 by nsamarin          #+#    #+#             */
/*   Updated: 2025/03/27 12:19:47 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int nb)
{
	if (nb < 0)
		nb = -nb;
	return (nb);
}

static int	ft_sign(int nb)
{
	int	a;

	a = 0;
	if (nb <= 0)
		a = 1;
	return (a);
}

static int	ft_length(int nb)
{
	int	len;
	int	sig;

	len = 0;
	sig = 0;
	if (nb <= 0)
		sig = 1;
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len + sig);
}

char	*ft_itoa(int n)
{
	unsigned int	num;
	int				sign;
	int				length;
	char			*nstr;

	sign = ft_sign(n);
	length = ft_length(n);
	num = ft_abs(n);
	nstr = malloc(sizeof(char) * (length + 1));
	if (!nstr)
		return (NULL);
	nstr[length--] = '\0';
	if (num == 0)
		nstr[0] = '0';
	while (length >= 0)
	{
		nstr[length] = num % 10 + '0';
		num /= 10;
		length--;
	}
	if (sign == 1 && n != 0)
		nstr[0] = '-';
	return (nstr);
}

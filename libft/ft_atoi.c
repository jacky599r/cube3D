/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:57:39 by nsamarin          #+#    #+#             */
/*   Updated: 2024/06/20 13:07:44 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	a;
	int	sign;
	int	new;

	a = 0;
	sign = 1;
	new = 0;
	while (str[a] == 32 || (str[a] >= 9 && str[a] <= 13))
		a++;
	if (str[a] == '-' || str[a] == '+')
	{
		if (str[a] == '-')
			sign *= -1;
		a ++;
	}
	while (str[a] >= '0' && str[a] <= '9')
	{
		new = (new * 10) + (str[a] - '0');
		a ++;
	}
	return (new * sign);
}

/*
int main(void)
{
	char *test = "   +01";
	printf("mine: %i, atoi: %i\n", ft_atoi(test), atoi(test));
}
*/

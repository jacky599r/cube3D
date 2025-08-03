/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:20:22 by nsamarin          #+#    #+#             */
/*   Updated: 2024/06/19 14:44:41 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long int	a;

	a = n;
	if (a < 0)
	{
		ft_putchar_fd('-', fd);
		a *= -1;
	}
	if (a > 9)
	{
		ft_putnbr_fd((a / 10), fd);
		ft_putchar_fd(((a % 10) + '0'), fd);
	}
	else
		ft_putchar_fd((a + '0'), fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:36:46 by nsamarin          #+#    #+#             */
/*   Updated: 2024/06/20 14:36:02 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list		*location;
	t_list		*to_clear;

	location = *lst;
	to_clear = 0;
	while (location)
	{
		if (location->next)
			to_clear = location->next;
		else
			to_clear = 0;
		del(location->content);
		free(location);
		location = to_clear;
	}
	*lst = NULL;
}

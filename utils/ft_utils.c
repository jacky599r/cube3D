/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 21:45:32 by jacky599r         #+#    #+#             */
/*   Updated: 2025/09/19 15:01:20 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_img_init(t_img *img)
{
	if (!img)
		return ;
	img->img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line = 0;
	img->endian = 0;
}

void	ft_key_init(t_keys *key)
{
	key->down = 0;
	key->up = 0;
	key->right = 0;
	key->left = 0;
	key->l_arw = 0;
	key->r_arw = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 11:02:17 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/22 07:06:04 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_is_coin_candidate(char tile)
{
	if (tile == '1' || tile == 'D')
		return (0);
	if (tile == 'X')
		return (0);
	return (1);
}

void	ft_reset_coin_list(t_data *data)
{
	if (!data)
		return ;
	if (data->coins)
		free(data->coins);
	data->coins = NULL;
	data->coin_count = 0;
	data->coin_capacity = 0;
	data->coin_alive = 0;
}

int	ft_collect_coin(t_data *data, int i)
{
	int	grid_x;
	int	grid_y;

	if (!data || !data->coins || data->coin_alive == 0)
		return (0);
	grid_x = (int)data->play.pos.x;
	grid_y = (int)data->play.pos.y;
	i = 0;
	while (i < data->coin_count)
	{
		if (data->coins[i].alive && data->coins[i].grid_x == grid_x
			&& data->coins[i].grid_y == grid_y)
		{
			data->coins[i].alive = false;
			if (data->coin_alive > 0)
			{
				data->coin_alive--;
				if (data->coin_alive == 0)
					ft_terminate_game(data);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_free_coins(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->coins)
		free(data->coins);
	data->coins = NULL;
	data->coin_count = 0;
	data->coin_capacity = 0;
	data->coin_alive = 0;
	i = 0;
	while (i < COIN_FRAME_COUNT)
	{
		if (data->coin_frames[i].pixels)
		{
			free(data->coin_frames[i].pixels);
			data->coin_frames[i].pixels = NULL;
		}
		data->coin_frames[i].width = 0;
		data->coin_frames[i].height = 0;
		i++;
	}
}

int	ft_coin_update_anim(t_data *data, t_coin_anim next)
{
	int	changed;

	if (!data)
		return (0);
	changed = 0;
	if (data->coin_anim.frame_a != next.frame_a
		|| data->coin_anim.frame_b != next.frame_b)
		changed = 1;
	else if (fabs(data->coin_anim.alpha - next.alpha) > 0.0001)
		changed = 1;
	data->coin_anim = next;
	return (changed);
}

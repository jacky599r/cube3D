/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 11:02:17 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/22 06:23:30 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_is_coin_candidate(char tile)
{
	if (tile == '1' || tile == 'D')
		return (0);
	if (tile == 'X')
		return (0);
	return (1);
}

static void	ft_reset_coin_list(t_data *data)
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

int	ft_spawn_coins(t_data *data)
{
	int	player_x;
	int	player_y;
	int	y;
	int	x;

	if (!data || !data->map.fl_map)
		return (FAIL);
	ft_reset_coin_list(data);
	data->coin_capacity = data->map.high * data->map.wide;
	data->coins = ft_calloc(data->coin_capacity, sizeof(t_coin));
	if (!data->coins)
	{
		ft_error_msg("Error", "Coin allocation failed", FAIL);
		ft_freedom(data);
		return (FAIL);
	}
	player_x = (int)data->play.pos.x;
	player_y = (int)data->play.pos.y;
	y = 0;
	while (y < data->map.high)
	{
		x = 0;
		while (x < data->map.wide)
		{
			if (ft_is_coin_candidate(data->map.fl_map[y][x])
				&& !(x == player_x && y == player_y))
			{
				data->coins[data->coin_count].grid_x = x;
				data->coins[data->coin_count].grid_y = y;
				data->coins[data->coin_count].world_x = (double)x + 0.5;
				data->coins[data->coin_count].world_y = (double)y + 0.5;
				data->coins[data->coin_count].alive = true;
				data->coin_count++;
			}
			x++;
		}
		y++;
	}
	data->coin_alive = data->coin_count;
	return (PASS);
}

int	ft_collect_coin(t_data *data)
{
	int	grid_x;
	int	grid_y;
	int	i;

	if (!data || !data->coins || data->coin_alive == 0)
		return (0);
	grid_x = (int)data->play.pos.x;
	grid_y = (int)data->play.pos.y;
	i = 0;
	while (i < data->coin_count)
	{
		if (data->coins[i].alive
			&& data->coins[i].grid_x == grid_x
			&& data->coins[i].grid_y == grid_y)
		{
			data->coins[i].alive = false;
			if (data->coin_alive > 0)
				data->coin_alive--;
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

t_coin_anim	ft_coin_anim_state(void)
{
	struct timeval	tv;
	time_t			ticks;
	struct tm		*info;
	double			seconds;
	double			position;
	t_coin_anim	anim;

	anim.frame_a = 0;
	anim.frame_b = (COIN_FRAME_COUNT > 1) ? 1 : 0;
	anim.alpha = 0.0;
	if (gettimeofday(&tv, NULL) != 0)
		return (anim);
	ticks = tv.tv_sec;
	info = localtime(&ticks);
	if (!info)
		return (anim);
	seconds = info->tm_hour * 3600.0 + info->tm_min * 60.0
		+ info->tm_sec + tv.tv_usec / 1000000.0;
	position = fmod(seconds * COIN_ANIM_SPEED, COIN_FRAME_COUNT);
	anim.frame_a = (int)position;
	anim.alpha = position - anim.frame_a;
	if (anim.frame_a >= COIN_FRAME_COUNT)
		anim.frame_a = 0;
	if (COIN_FRAME_COUNT > 1)
		anim.frame_b = (anim.frame_a + 1) % COIN_FRAME_COUNT;
	else
		anim.frame_b = anim.frame_a;
	return (anim);
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

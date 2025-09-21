/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coins_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 06:31:56 by nico              #+#    #+#             */
/*   Updated: 2025/09/22 06:44:31 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_seconds_of_day(double *out_sec)
{
	struct timeval	tv;
	time_t			ticks;
	struct tm		*info;
	double			sec;

	if (gettimeofday(&tv, NULL) != 0)
		return (FAIL);
	ticks = tv.tv_sec;
	info = localtime(&ticks);
	if (!info)
		return (FAIL);
	sec = info->tm_hour * 3600.0 + info->tm_min * 60.0 + info->tm_sec;
	sec = sec + (tv.tv_usec / 1000000.0);
	*out_sec = sec;
	return (PASS);
}

static void	ft_coin_anim_default(t_coin_anim *a)
{
	a->frame_a = 0;
	a->frame_b = 0;
	a->alpha = 0.0;
	if (COIN_FRAME_COUNT > 1)
		a->frame_b = 1;
}

t_coin_anim	ft_coin_anim_state(void)
{
	t_coin_anim	anim;
	double		sec;
	double		pos;

	ft_coin_anim_default(&anim);
	if (ft_seconds_of_day(&sec) != PASS)
		return (anim);
	pos = fmod(sec * COIN_ANIM_SPEED, COIN_FRAME_COUNT);
	anim.frame_a = (int)pos;
	anim.alpha = pos - (double)anim.frame_a;
	if (anim.frame_a >= COIN_FRAME_COUNT)
		anim.frame_a = 0;
	if (COIN_FRAME_COUNT > 1)
	{
		anim.frame_b = anim.frame_a + 1;
		if (anim.frame_b >= COIN_FRAME_COUNT)
			anim.frame_b = 0;
	}
	else
		anim.frame_b = anim.frame_a;
	return (anim);
}

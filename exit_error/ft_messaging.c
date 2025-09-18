/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_messaging.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:40:56 by nico              #+#    #+#             */
/*   Updated: 2025/09/17 21:45:32 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_dup_or_join(char *s1, char *s2)
{
	if (!s2)
		return (ft_strdup(s1));
	if (!s1)
		return (ft_strdup(s2));
	else
		return (ft_strjoin(s1, s2));
}

char	*ft_add_quotes(char *final, char *cmd, char *dtl)
{
	char	*temp;

	(void)cmd; // Suppress unused parameter warning
	temp = ft_dup_or_join(final, "'");
	ft_safe_ptr(final);
	final = temp;
	temp = ft_dup_or_join(final, dtl);
	ft_safe_ptr(final);
	final = temp;
	temp = ft_dup_or_join(final, "'");
	ft_safe_ptr(final);
	final = temp;
	return (final);
}

void	ft_correct_form(int err_code, char *dtl)
{
	if (err_code == 2)
		printf("Correct Usage: \"./cub3D maps.cub\"\n");
	if (err_code == 3)
		printf("Correct Usage: \"%s ./path_to_texture.xpm\"\n", dtl);
	if (err_code == 4)
		printf("Correct Usage: \"%s R,G,B\" colors in range [0-255]\n", dtl);
	if (err_code == 5)
	{
		printf("Map Correct Usage\n");
		printf("Map must be surrounded by walls\n");
		printf("The map can have only 6 characters:\n");
		printf("  - 0 for an empty space\n");
		printf("  - 1 for a wall\n");
		printf("  - N,S,E or W player start position/orientation\n");
	}
	return ;
}
// explored idea to have a trim function that removes empty spaces, before,
//	during and after useful info
// eg: "     F                          1,7,9" -> "F 1,7,9"
int	ft_error_msg(char *cmd, char *msg, char *dtl, int err_code)
{
	char	*final;

	if (msg)
	{
		final = ft_dup_or_join(cmd, ": ");
		final = ft_add_quotes(final, cmd, msg);
	}
	else
		final = ft_strdup(cmd);
	printf("Cub3D: %s\n", final);
	ft_safe_ptr(final);
	ft_correct_form(err_code, dtl);
	return (err_code);
}

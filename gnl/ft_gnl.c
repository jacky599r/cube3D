/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:30:41 by nsamarin          #+#    #+#             */
/*   Updated: 2025/03/26 16:09:25 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_read_to_temp(char *temporary, int fd)
{
	char	*read_result;
	int		str_len;

	str_len = 1;
	if (!temporary)
		temporary = ft_mem_alloc_fill(1, sizeof(char));
	read_result = ft_mem_alloc_fill(BUFFER_SIZE + 1, sizeof(char));
	while (ft_new_line(temporary) == 0 && str_len != 0)
	{
		str_len = read(fd, read_result, BUFFER_SIZE);
		if (str_len == -1)
		{
			free(temporary);
			free(read_result);
			return (NULL);
		}
		read_result[str_len] = '\0';
		temporary = ft_join_to_temp(temporary, read_result);
	}
	free(read_result);
	return (temporary);
}

char	*ft_join_to_temp(char *temporary, char *read_result)
{
	int		a;
	int		b;
	char	*str;

	a = ft_str_len(temporary);
	b = ft_str_len(read_result);
	str = ft_mem_alloc_fill((a + b + 1), sizeof(char));
	if (!str)
		return (temporary);
	b = 0;
	while (temporary[b])
	{
		str[b] = temporary[b];
		b++;
	}
	b = 0;
	while (read_result[b])
	{
		str[a + b] = read_result[b];
		b++;
	}
	str[a + b] = '\0';
	free(temporary);
	return (str);
}

char	*ft_temp_to_extract(char *temporary)
{
	int		a;
	char	*extract;

	a = 0;
	if (!temporary[a])
		return (NULL);
	while (temporary[a] && temporary[a] != '\n')
		a++;
	extract = ft_mem_alloc_fill(a + 2, 1);
	a = 0;
	while (temporary[a])
	{
		if (temporary[a] == '\n')
		{
			extract[a] = '\n';
			return (extract);
		}
		extract[a] = temporary[a];
		a++;
	}
	return (extract);
}

char	*ft_clear_for_next(char *temporary)
{
	int		a;
	int		b;
	char	*next;

	a = 0;
	b = ft_str_len(temporary);
	while (temporary[a] && temporary[a] != '\n')
		a++;
	if (!temporary[a])
	{
		free(temporary);
		return (NULL);
	}
	next = ft_mem_alloc_fill(b - a + 1, 1);
	a++;
	b = 0;
	while (temporary[a] && b < (ft_str_len(temporary) - a))
	{
		next[b] = temporary[a + b];
		b++;
	}
	temporary[(ft_str_len(temporary) - a)] = '\0';
	free(temporary);
	return (next);
}

char	*get_next_line(int fd)
{
	static char	*temporary;
	char		*extract;

	extract = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temporary = ft_read_to_temp(temporary, fd);
	if (!temporary)
		return (NULL);
	extract = ft_temp_to_extract(temporary);
	temporary = ft_clear_for_next(temporary);
	return (extract);
}

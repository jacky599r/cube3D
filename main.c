/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:43:43 by nico              #+#    #+#             */
/*   Updated: 2025/08/12 17:57:35 by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int ft_extension_check(char *file, char *ext)
{
	int len;

    len = ft_strlen(file);
    if (len < 5)
    	return (ft_error_msg("Error File Name", file, NULL, 3));
	if (ft_strncmp(file + len - 4, ext, 4) != 0)
		return (ft_error_msg("Error File Name", file, NULL, 3));
    return(0);
}
int ft_open_file(char *path)
{
    int dfd;
    int fd;
    
    dfd = open(path, O_RDONLY | __O_DIRECTORY);
    if (dfd >= 0) 
    {
        close(dfd);
        return (ft_error_msg("File is Directory", path, NULL, 3));
    }
    if (errno != ENOTDIR) 
        return (ft_error_msg("File Error", path, NULL, FAIL));
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (ft_error_msg("File Error", path, NULL, FAIL));
    close (fd);
    return (PASS);
}
int ft_read_map(t_data *data, char *path); //can we char *file_name instead?
int ft_parse_map(t_data *data);

int ft_data_validation(t_data *data, int argc,  char **argv)
{
    if (argc != 2)
        return(ft_error_msg("Error", "Invalid number of arguments", NULL, FAIL)); //added to streamline error_msg
    ft_data_init(&data);
    if (ft_strncmp(argv[0], "./cub3D", 7)) !=0
        return (ft_error_msg("Error", "Incorrect executable name", NULL, FAIL)); //added to streamline error_msg
    if (ft_extension_check(argv[1], ".cub") != PASS)
        return (FAIL);
    if (ft_open_file(argv[1]) != PASS)
        return (FAIL);
    if (ft_read_map(data, argv[1] != PASS))
        return (FAIL);
    return(PASS);
}

int main(int ac, char **av)
{
    t_data data;

    if (ac != 2)
        return (ft_error_msg("Error", "Wrong number of arguments", NULL, FAIL));
    ft_init_all(&data);
    data.map.og_map = ft_get_raw_map_data(av[1]);
    if (!data.map.og_map)
        return (FAIL);
    if (ft_check_map_config(&data) == FAIL)
    {
        ft_free_all(&data);
        return (FAIL);
    }
    if (ft_prepare_map_for_flood_fill(&data) == FAIL)
    {
        ft_free_all(&data);
        return (FAIL);
    }
    ft_set_initial_player_view(&data);
    if (ft_validate_map_enclosure(&data) == FAIL)
    {
        ft_free_all(&data);
        return (FAIL);
    }

    // Placeholder for now
    ft_free_all(&data);
    return (PASS);
}

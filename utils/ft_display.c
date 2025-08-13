/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:50:23 by nsamarin          #+#    #+#             */
/*   Updated: 2025/08/13 14:26:55 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_print_welcome(void)
{
	printf("%s\n", CYAN);
    printf("██████╗██╗ ██╗█████╗ ██████╗████╗  \n");
    printf("██╔═══╝██║ ██║██╔═██╗╚═══██║██╚██╗ \n");
    printf("██║    ██║ ██║█████╔╝   ██╔╝██ ╚██╗\n");
    printf("██║    ██║ ██║██╔═██╗   ╚██╗██ ██╔╝\n");
    printf("██████╗██████║█████╔╝█████╔╝████╔╝ \n");
    printf("╚═════╝╚═════╝╚════╝ ╚════╝ ╚═══╝  \n");
	printf("%s", YELLOW);
	printf("\n");
	printf("-----------------------------------\n");
	printf("      %sWelcome to Cub3D!          \n", GREEN);
	printf("     %s \"W\" - Move Front         \n", BLUE);
	printf("     %s \"S\" - Move Back          \n", BLUE);
	printf("     %s \"A\" - Move Left          \n", BLUE);
    printf("     %s \"D\" - Move Right         \n", BLUE);
    printf("     %s\"->\" - Look Left          \n", BLUE);
    printf("     %s\"<-\" - Look Right         \n", BLUE);
    printf("\n");
    printf("    %s\"Esc\" - Exit Game          \n", BLUE);
	printf("%s", YELLOW);
	printf("-----------------------------------\n");
	printf("%s\n", RESET);
}

void	ft_print_exit(void)
{
	printf("\n");
	printf("%s\n", MAGENTA);
	printf("    █████╗ ██╗   ██╗██╗████████╗   \n");
	printf("    ██╔══╝ ╚██╗ ██╔╝██║╚══██╔══╝   \n");
	printf("    █████╗  ╚████╔╝ ██║   ██║      \n");
	printf("    ██╔══╝  ██╔═██╗ ██║   ██║      \n");
	printf("    █████╗ ██╔╝ ╚██╗██║   ██║      \n");
	printf("    ╚════╝ ╚═╝   ╚═╝╚═╝   ╚═╝      \n");
	printf("%s", YELLOW);
	printf("\n");
	printf("-----------------------------------\n");
	printf("        %sExiting Cub3D!           \n", RED);
	printf("%s", YELLOW);
	printf("-----------------------------------\n");
	printf("%s\n", RESET);
}

void ft_print_coordiantes()
{
    
}
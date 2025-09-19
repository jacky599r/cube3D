/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:50:23 by nsamarin          #+#    #+#             */
/*   Updated: 2025/09/19 13:15:19 by nsamarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_print_welcome(void)
{
	printf("%s\n", CYAN);
	printf("\t██████╗██╗ ██╗█████╗ ██████╗████╗  \n");
	printf("\t██╔═══╝██║ ██║██╔═██╗╚═══██║██╚██╗ \n");
	printf("\t██║    ██║ ██║█████╔╝   ██╔╝██ ╚██╗\n");
	printf("\t██║    ██║ ██║██╔═██╗   ╚██╗██ ██╔╝\n");
	printf("\t██████╗██████║█████╔╝█████╔╝████╔╝ \n");
	printf("\t╚═════╝╚═════╝╚════╝ ╚════╝ ╚═══╝  \n");
	printf("%s", YELLOW);
	printf("\n");
	printf("\t-----------------------------------\n");
	printf("\t        %sWelcome to Cub3D!          \n", GREEN);
	printf("\t       %s\"W\" - Move Front         \n", BLUE);
	printf("\t       %s\"S\" - Move Back          \n", BLUE);
	printf("\t       %s\"A\" - Move Left          \n", BLUE);
	printf("\t       %s\"D\" - Move Right         \n", BLUE);
	printf("\t       %s\"<\" - Look Left          \n", BLUE);
	printf("\t       %s\">\" - Look Right         \n", BLUE);
	printf("\t\n");
	printf("\t      %s\"Esc\" - Exit Game          \n", BLUE);
	printf("%s", YELLOW);
	printf("\t-----------------------------------\n");
	printf("%s\n", RESET);
}

void	ft_print_exit(void)
{
	printf("\n");
	printf("%s\n", MAGENTA);
	printf("\t ██████╗  █████╗ ███╗   ███╗███████╗\n");
	printf("\t██╔════╝ ██╔══██╗████╗ ████║██╔════╝\n");
	printf("\t██║  ███╗███████║██╔████╔██║█████╗  \n");
	printf("\t██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  \n");
	printf("\t╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗\n");
	printf("\t ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝\n");
	printf("\n");
	printf("\t ██████╗ ██╗    ██╗███████╗██████╗ \n");
	printf("\t██╔═══██╗██║    ██║██╔════╝██╔══██╗\n");
	printf("\t██║   ██║╚██╗  ██╔╝█████╗  ██████╔╝\n");
	printf("\t██║   ██║ ╚██╗██╔╝ ██╔══╝  ██╔██╔╝ \n");
	printf("\t╚██████╔╝  ╚███╔╝  ███████╗██║╚██╗ \n");
	printf("\t ╚═════╝    ╚══╝   ╚══════╝╚═╝ ╚═╝ \n");
	printf("%s", YELLOW);
	printf("\n");
	printf("\t-----------------------------------\n");
	printf("\t         %sEXITING GAME!            \n", RED);
	printf("%s", YELLOW);
	printf("\t-----------------------------------\n");
	printf("%s\n", RESET);
}

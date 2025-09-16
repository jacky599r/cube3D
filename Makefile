# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jacky599r <jacky599r@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/26 13:28:54 by nico              #+#    #+#              #
#    Updated: 2025/09/16 14:59:07 by jacky599r        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
RM = rm -f
CFLAGS = -g -Wall -Wextra -Werror
LDFLAGS = -lX11 -lXext -lm -lbsd

# (no global silencing; keep verbose unless using @ on specific cmds)

# Directories
LIBFT_DR = libft
MLX_DIR = mlx
SRC_DIR = .
OBJ_DIR = obj

# Source Files (include all utility files)
SRCS = main.c \
       utils/ft_file_reader.c \
       utils/ft_param_parser.c \
       utils/ft_map_validator.c \
       utils/ft_map_processor.c \
       utils/ft_map_enclosure.c \
       utils/ft_utils.c \
       utils/ft_init.c \
       utils/ft_parse_elements.c \
       gnl/ft_gnl.c \
       gnl/ft_gnl_utils.c \
       data_validation/ft_game_start.c \
       exit_error/ft_exit.c \
       exit_error/ft_free.c \
       exit_error/ft_messaging.c
       # Removed duplicate files that were causing symbol conflicts
       # data_validation/ft_init.c \
       # data_validation/ft_init_2.c \
       # exit_error/ft_exit.c \
       # exit_error/ft_free.c \
       # exit_error/ft_messaging.c
       # Temporarily commented out until struct issues are resolved
       # player_action/ft_keyhook.c \
       # player_action/ft_movment.c \
       # raycast_engine/ft_raycaster_1.c \
       # raycast_engine/ft_raycaster_2.c \
       # raycast_engine/ft_dda.c

# Generate object files in OBJ_DIR
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# Libraries
LIBFT = $(LIBFT_DR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

# Include paths
INCLUDES = -I. -I$(LIBFT_DR) -I$(MLX_DIR)

HEADER = cub3D.h

all: $(NAME)

# Create object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) \
		$(addprefix $(OBJ_DIR)/, \
			raycast_engine \
			player_action \
			gnl \
			utils \
			data_validation \
			exit_error \
			data_initiation \
		)

# Build Libraries
$(LIBFT):
	@if [ ! -f "$(LIBFT)" ]; then \
		$(MAKE) -s --no-print-directory -C $(LIBFT_DR); \
	fi

$(MLX):
	@if [ ! -f "$(MLX)" ]; then \
		$(MAKE) -s --no-print-directory -C $(MLX_DIR); \
	fi

# Link everything (without MLX for now)
$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DR) -lft -o $@

# Compile objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(LIBFT_DR) fclean

re: fclean all

.PHONY: all clean fclean re
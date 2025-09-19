# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsamarin <nsamarin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/26 13:28:54 by nico              #+#    #+#              #
#    Updated: 2025/09/17 23:11:58 by jacky599r        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
RM = rm -f
CFLAGS = -g -Wall -Wextra -Werror
LDFLAGS = -lX11 -lXext -lm -lbsd

# Directories
LIBFT_DR = libft
MLX_DIR = mlx
SRC_DIR = .
OBJ_DIR = obj

# Source Files (include all utility files)
SRCS = main.c \
       utils/ft_args_validation.c \
       utils/ft_file_reader.c \
	   utils/ft_display.c \
       utils/ft_param_parser.c \
       utils/ft_texture_utils.c \
       utils/ft_rgb_utils.c \
       utils/ft_map_validation.c \
       utils/ft_map_parser.c \
       utils/ft_map_prep.c \
       utils/ft_prepare_to_fill.c \
       utils/ft_map_enclosure.c \
       utils/ft_data_validation.c \
       utils/ft_utils.c \
       utils/ft_string_utils.c \
       utils/ft_validation_utils.c \
       utils/ft_init.c \
       gnl/ft_gnl.c \
       gnl/ft_gnl_utils.c \
       data_validation/ft_game_start.c \
       exit_error/ft_exit.c \
       exit_error/ft_free.c \
       exit_error/ft_messaging.c \
       player_action/ft_keyhook.c \
       player_action/ft_movment.c \
       player_action/ft_door.c \
       raycast_engine/ft_raycaster_1.c \
       raycast_engine/ft_raycaster_2.c \
       raycast_engine/ft_dda.c \
       utils/ft_minimap.c

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
	@echo "Created object directories"

# Build Libraries
$(LIBFT):
	@if [ ! -f "$(LIBFT)" ]; then \
		echo "Built libft"; \
		make --no-print-directory -C $(LIBFT_DR); \
	fi

$(MLX):
	@if [ ! -f "$(MLX)" ]; then \
		echo "Built libmlx"; \
		make --no-print-directory -C $(MLX_DIR); \
	fi

# Link everything
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DR) -lft -L$(MLX_DIR) -lmlx $(LDFLAGS) -o $@
	@echo "Built everything for cub3D"

# Compile objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@find . -name "*.o" -not -path "./$(LIBFT_DR)/*" -not -path "./$(MLX_DIR)/*" -not -path "./$(OBJ_DIR)/*" -delete
	@make -C $(LIBFT_DR) clean
	@make -C $(MLX_DIR) clean
	@echo "Cleaned object files"

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIBFT_DR) fclean
	@make -C $(MLX_DIR) clean
	@echo "Cleaned executable files"

re: fclean all

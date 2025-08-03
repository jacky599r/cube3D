# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nico <nico@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/26 13:28:54 by nico              #+#    #+#              #
#    Updated: 2025/07/23 13:50:21 by nico             ###   ########.fr        #
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

# Source Files
SRCS = main.c 

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
	@make -C $(LIBFT_DR) clean
	@make -C $(MLX_DIR) clean
	@echo "Cleaned object files"

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIBFT_DR) fclean
	@make -C $(MLX_DIR) clean
	@echo "Cleaned executable files"

re: fclean all

.PHONY: all clean fclean re
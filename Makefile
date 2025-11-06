# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/31 10:18:07 by anpollan          #+#    #+#              #
#    Updated: 2025/10/31 17:58:36 by anpollan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Binary file
NAME			= miniRT

# Header inclusions
INCL_DIR		= ./incl/
MINIRT_HEADER	= ./incl/minirt.h
LIBFT_HEADER	= ./libft/libft.h
MLX_HEADER_DIR	= ./mlx42/include/
MLX_HEADER		= ./mlx42/include/MLX42/MLX42.h
MLX_INT_HEADER	= ./mlx42/include/MLX42/MLX42_Int.h
INCL			= -I$(INCL_DIR) -I$(LIBFT_DIR) -I$(MLX_HEADER_DIR)

# Libft
LIBFT_DIR		= ./libft/
LIBFT			= $(LIBFT_DIR)libft.a

# Minilibx
MLX_REPO		= https://github.com/codam-coding-college/MLX42.git
MLX_DIR			= ./mlx42/
MLX				= $(MLX_DIR)libmlx42.a

# C-files
C_FILES			= main.c parsing.c window_management.c initialize.c
SRC_DIR			= ./src/
SRCS			= $(addprefix $(SRC_DIR), $(C_FILES))

# OBJ-files
OBJ_DIR			= ./obj/
OBJS			= $(addprefix $(OBJ_DIR), $(C_FILES:%.c=%.o))

# Build flags
C_FLAGS			= -Wall -Wextra -Werror -g
MLX_FLAGS		= -lglfw -ldl -lpthread -lm

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	cc $(C_FLAGS) $(OBJS) $(LIBFT) $(MLX) $(INCL) $(MLX_FLAGS) -o $(NAME)

$(LIBFT): $(LIBFT_HEADER)
	$(MAKE) -C libft

$(MLX):
	git clone $(MLX_REPO) $(MLX_DIR)
	(cd $(MLX_DIR) && cmake -D DEBUG=1 .)
	$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(LIBFT_HEADER) $(MINIRT_HEADER) $(MLX)
	mkdir -p $(OBJ_DIR)
	cc $(C_FLAGS) $(INCL) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

frclean: fclean
	rm -rf $(MLX_DIR) compile_commands.json

phony: all clean fclean frclean

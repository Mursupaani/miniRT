# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhana <juhana@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/31 10:18:07 by anpollan          #+#    #+#              #
#    Updated: 2025/12/17 12:24:28 by juhana           ###   ########.fr        #
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
C_FILES			= main.c parsing.c initialize.c math_utils.c memory_and_exit.c \
				  tuple.c tuple_math.c tuple_utils.c vector_math.c \
				  rendering_utils.c parsing_utils.c matrix_utils.c \
				  matrix_multiplication.c matrix_transpose.c \
				  matrix_determinant.c submatrices.c hooks.c\
				  matrix_minor_and_cofactor.c matrix_inversion.c \
				  transformation.c rotations.c render_routine.c \
				  intersect_sphere.c intersection.c ray.c objects.c normal.c \
				  reflect.c lighting.c color.c color_utils.c material.c \
				  world.c intersect_world.c intersect_utils.c shading.c \
				  view_transform.c camera.c patterns.c pattern_stripe.c \
				  color_math.c pattern_gradient.c pattern_ring.c \
				  pattern_checkers.c plane.c \
				  \
				  debug.c test_tuples.c test_matrices.c test_transformation.c \
				  test_rays.c test.c test_normal.c test_color.c test_world.c \
				  test_camera.c test_render_chapter7.c test_shadows.c \
				  test_patterns.c

SRC_DIR			= ./src/
SRCS			= $(addprefix $(SRC_DIR), $(C_FILES))

# OBJ-files
OBJ_DIR			= ./obj/
OBJS			= $(addprefix $(OBJ_DIR), $(C_FILES:%.c=%.o))

# Build flags
C_FLAGS			= -Wall -Wextra -Werror -g -DTHREADS=$(THREADS)
MLX_FLAGS		= -lglfw -ldl -lpthread -lm

# Threads
THREADS			= $(shell nproc 2>/dev/null || sysctl -n hw.physicalcpu || echo 4)

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

re: fclean $(NAME)

fre: frclean $(NAME)

phony: all clean fclean frclean re fre

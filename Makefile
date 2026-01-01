# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/31 10:18:07 by anpollan          #+#    #+#              #
#    Updated: 2026/01/01 17:09:49 by anpollan         ###   ########.fr        #
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
C_FILES			= main.c initialize.c math_utils.c memory_and_exit.c \
				  tuple.c tuple_math.c tuple_utils.c vector_math.c \
				  rendering_utils.c matrix_utils.c \
				  matrix_multiplication.c matrix_transpose.c \
				  matrix_determinant.c submatrices.c hooks.c\
				  matrix_minor_and_cofactor.c matrix_inversion.c \
				  transformation.c rotations.c render_routine.c \
				  intersect.c sphere.c intersection.c ray.c objects.c normal.c \
				  reflect.c lighting.c color.c color_utils.c material.c \
				  world.c intersect_world.c intersect_utils.c shading.c \
				  view_transform.c camera.c patterns.c pattern_stripe.c \
				  color_math.c pattern_gradient.c pattern_ring.c \
				  parse_dispatcher.c parse_numbers.c parse_tuple.c \
				  parse_utils.c parse_light_and_camera.c parse_objects.c \
				  parse_objects_utils.c uv_patterns.c uv_checkers.c \
				  spherical_map.c pattern_checkers.c reflections.c plane.c \
				  prepare_computations.c prepare_computations_utils.c \
				  refraction.c cube.c cube_utils.c cylinder.c cone.c \
				  planar_map.c cylindrical_map.c cube_map.c uv_image.c \
				  cubic_map.c cubic_map_utils.c cubic_map_utils2.c \
				  bump_map.c uv_utils.c \
				  debug.c test_tuples.c test_matrices.c test_transformation.c \
				  test_rays.c test.c test_normal.c test_color.c \
				  test_camera.c test_render_chapter7.c test_shadows.c \
				  test_patterns.c test_reflections.c test_transparency.c \
				  test_cubes.c test_cylinder.c test_parsing.c test_cones.c \
				  test_render.c christmas.c test_uv_patterns.c test_bump_map.c

SRC_DIR			= ./src/
SRCS			= $(addprefix $(SRC_DIR), $(C_FILES))

# OBJ-files
OBJ_DIR			= ./obj/
OBJS			= $(addprefix $(OBJ_DIR), $(C_FILES:%.c=%.o))

# Build flags
C_FLAGS			= -Wall -Wextra -Werror -g -o3 -DTHREADS=$(THREADS)
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

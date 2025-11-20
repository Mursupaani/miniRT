/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:38:13 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/20 19:04:47 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <fcntl.h>
# include <float.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "libft.h"
# include "MLX42/MLX42.h"
# include "MLX42/MLX42_Int.h"

// FIXME: Find best value for epsilon! 0.00001 doesn't work like in guide

# ifndef THREADS
#  define THREADS 1
# endif

# ifndef EPSILON
#  define EPSILON 1e-4f
# endif

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_tuple;
typedef t_tuple	t_vector;
typedef t_tuple	t_point;

typedef struct s_color_255
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}	t_color_255;

typedef struct s_color_1
{
	float	r;
	float	g;
	float	b;
	float	a;
}	t_color_1;

//FIXME: Testing
typedef struct s_proj
{
	t_point		*p;
	t_vector	*v;
}	t_proj;

typedef struct s_env
{
	t_vector	*g;
	t_vector	*w;
}	t_env;
//FIXME: Testing

typedef enum s_exit_value
{
	SUCCESS,
	ERROR_NO_INPUT_FILE,
	ERROR_MLX_INIT,
	ERROR_MLX_IMG_INIT,
	ERROR_INVALID_FILE_TYPE,
	ERROR_OPEN,
	ERROR_SCENE,
	ERROR_PARSING,
	
}	t_exit_value;

typedef enum s_object_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_object_type;

typedef struct s_ambient_light
{
	float			brightness;
	t_color_1		*color_1;
	t_color_255		*color_255;
}	t_ambient_light;

typedef struct s_point_light
{
	float			brightness;
	t_point			*center;
	t_color_1		*color_1;
	t_color_255		*color_255;
}	t_point_light;

typedef struct s_camera
{
	t_point		*view_point;
	t_vector	*orientation;
	float		fov;
}	t_camera;

typedef struct s_object
{
	t_object_type	type;
	t_point			*center;
	t_vector		*normal;
	float			diameter;
	float			height;
	t_color_1		*color_1;
	t_color_255		*color_255;
}	t_object;

typedef struct s_scene
{
	t_camera		*camera;
	t_ambient_light	*ambient_light;
	t_point_light	*light;
	t_object		*objects[];
}	t_scene;

typedef struct s_app
{
	int			monitor_width;
	int			monitor_height;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		*scene;
}	t_app;

// Tests
void		test_tuples(void);
void		test_matrices(void);

// Debug
void		print_tuple(t_tuple *tuple);
void		print_matrix2(float (*matrix)[2]);
void		print_matrix3(float (*matrix)[3]);
void		print_matrix4(float (*matrix)[4]);
t_proj		*tick(t_env *env, t_proj *proj);
void		projectile(t_app *app);

// App initialize and management:
t_app		*initialize_app(void);

// Parsing:
void	parse_rt_file(char **av, t_app *app);
bool	filetype_is_valid(char *filename);
void	skip_whitespace(char **str);

// Memory handling and exit:
void		free_app_memory(t_app *app);
void		exit_and_free_memory(int exit_code, t_app *app);

// Tuples (vectors, points):
t_tuple		*new_tuple(float x, float y, float z, float w);
t_vector	*new_vector(float x, float y, float z);
t_point		*new_point(float x, float y, float z);

// Tuple math:
t_tuple		*tuple_sum(t_tuple *a, t_tuple *b);
t_tuple		*tuple_subtract(t_tuple *a, t_tuple *b);
t_tuple		*tuple_scale_multiply(t_tuple *tuple, float scalar);
t_tuple		*tuple_scale_divide(t_tuple *tuple, float divider);
t_tuple		*tuple_negate(t_tuple *tuple);

// Vector math:
float		vector_magnitude(t_tuple *vector);
t_vector	*vector_normalize(t_vector *vector);
float		vector_dot_product(t_vector *a, t_vector *b);
t_vector	*vector_cross_product(t_vector *a, t_vector *b);

// Matrix utils:
bool	matrix4s_are_equal(float (*m1)[4], float (*m2)[4]);

// Matrix math:
float	(*matrix4_multiply(float m1[4][4], float m2[4][4]))[4];
t_tuple	*matrix4_and_tuple_multiply(float (*matrix)[4] , t_tuple *tuple);
float	(*matrix4_transpose(float (*matrix)[4]))[4];
float	(*matrix4_invert(float (*matrix)[4]))[4];

// Matrix determinants, submatrices, minors and cofactors:
float	matrix2_determinant(float matrix[2][2]);
float	matrix3_determinant(float matrix[3][3]);
float	matrix4_determinant(float matrix[4][4]);
float	(*matrix3_submatrix(float matrix[3][3], int row, int column))[2];
float	(*matrix4_submatrix(float matrix[4][4], int row, int column))[3];
float	matrix3_minor(float (*matrix)[3], int row, int column);
float	matrix4_minor(float (*matrix)[4], int row, int column);
float	matrix3_cofactor(float (*matrix)[3], int row, int column);
float	matrix4_cofactor(float (*matrix)[4], int row, int column);

// Tuple utils:
bool		tuples_are_equal(t_tuple *a, t_tuple *b);

// Math utils:
bool		floats_are_equal(float a, float b);

// Rendering utils
bool		pixel_fits_image(float x, float y, t_app *app);

#endif

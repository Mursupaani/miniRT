/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:38:13 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/25 15:33:27 by juhana           ###   ########.fr       */
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
# include <pthread.h>
# include "MLX42/MLX42.h"
# include "MLX42/MLX42_Int.h"

// FIXME: Find best value for epsilon! 0.00001 doesn't work like in guide

# ifndef THREADS
#  define THREADS 4
# endif

# ifndef EPSILON
#  define EPSILON 1e-4f
# endif

typedef struct s_thread_data t_thread_data;

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_tuple;
typedef t_tuple	t_vector;
typedef t_tuple	t_point;

typedef struct s_matrix2
{
	float	data[2][2];
}	t_matrix2;

typedef struct s_matrix3
{
	float	data[3][3];
}	t_matrix3;

typedef struct s_matrix4
{
	float	data[4][4];
}	t_matrix4;

typedef struct s_shear
{
	float	xy;
	float	xz;
	float	yx;
	float	yz;
	float	zx;
	float	zy;
}	t_shear;

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
	t_point		p;
	t_vector	v;
}	t_proj;

typedef struct s_env
{
	t_vector	g;
	t_vector	w;
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
	ERROR_THREADS,
	
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
	t_point			center;
	t_vector		normal;
	float			diameter;
	float			height;
	t_color_1		*color_1;
	t_color_255		*color_255;
	t_matrix4		transform;
	t_matrix4		inverse_transform;
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
	int				monitor_width;
	int				monitor_height;
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_scene			*scene;
	t_thread_data	*threads;
}	t_app;

/**
 * @struct t_thread_data
 * @brief Holds all persistent data and state for the application.
 *
 * Contains:
 * - int id: the threads id
 * - int start_row: the row where the thread starts starts rendering
 * - int end_row: thread stops rendering at this row
 * - t_app *app: acces to data the thread might need
 *
 * @see launch_render()
 */
typedef struct s_thread_data
{
	int			id;
	int			start_row;
	int			end_row;
	t_app		*app;
	pthread_t	thread_handle;
}	t_thread_data;

/**
 * @struct t_ray
 * @brief holds origin and direction of ray
 * 
 * Contains:
 * - t_point origin: start point of ray
 * - t_vector direction: direction of the ray
 */
typedef struct	s_ray
{
	t_point 	origin;
	t_vector	direction;
}	t_ray;

/**
 * @struct t_intersection
 * @brief linked list to hold hits, e.g. entering and exiting a sphere
 * 
 * Contains:
 * - float t: multiplier to calculate the distance travelled, where along the vector did the hit occur
 * - t_object object: the object that the ray hit
 * - t_intersection *next: address of the next hit
 */
typedef struct	s_intersection
{
	float					t;
	t_object				*object;
	struct s_intersection	*next;
}	t_intersection;

// Tests
void		test_tuples(void);
void		test_matrices(void);
void		test_transformation(void);
void		test_rays(void);

// Debug
void		print_tuple(t_tuple tuple);
// void		print_matrix2(float (*matrix)[2]);
void		print_matrix2(t_matrix2 matrix);
// void		print_matrix3(float (*matrix)[3]);
void		print_matrix3(t_matrix3 matrix);
// void		print_matrix4(float (*matrix)[4]);
void		print_matrix4(t_matrix4 matrix);
t_proj		tick(t_env env, t_proj proj);
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
t_tuple		init_tuple(float x, float y, float z, float w);
t_vector	init_vector(float x, float y, float z);
t_point		init_point(float x, float y, float z);

// Transformation matrices
t_matrix4	init_translation_matrix4(
			float scale_x, float scale_y, float scale_z);
t_matrix4	init_scaling_matrix4(float scale_x, float scale_y, float scale_z);
t_matrix4	init_x_rotation_matrix(float radians);
t_matrix4	init_y_rotation_matrix4(float radians);
t_matrix4	init_z_rotation_matrix4(float radians);
t_matrix4	init_shearing_matrix4(t_shear shear);

// Tuple math:
t_tuple		tuple_sum(t_tuple a, t_tuple b);
t_tuple		tuple_subtract(t_tuple a, t_tuple b);
t_tuple		tuple_scale_multiply(t_tuple tuple, float scalar);
t_tuple		tuple_scale_divide(t_tuple tuple, float divider);
t_tuple		tuple_negate(t_tuple tuple);

// Vector math:
float		vector_magnitude(t_tuple vector);
t_vector	vector_normalize(t_vector vector);
float		vector_dot_product(t_vector a, t_vector b);
t_vector	vector_cross_product(t_vector a, t_vector b);

// Matrix utils:
bool		matrix4s_are_equal(t_matrix4 m1, t_matrix4 m2);
t_matrix4	matrix4_identity(void);

// Matrix math:
t_matrix4	matrix4_multiply(t_matrix4 m1, t_matrix4 m2);
t_tuple		matrix4_and_tuple_multiply(t_matrix4 matrix, t_tuple tuple);
t_matrix4	matrix4_transpose(t_matrix4 matrix);
t_matrix4	matrix4_invert(t_matrix4 matrix);

// Matrix determinants, submatrices, minors and cofactors:
float	matrix2_determinant(t_matrix2 matrix);
float	matrix3_determinant(t_matrix3 matrix);
float	matrix4_determinant(t_matrix4 matrix);
t_matrix2	matrix3_submatrix(t_matrix3 matrix, int row, int column);
t_matrix3	matrix4_submatrix(t_matrix4 matrix, int row, int column);
float	matrix3_minor(t_matrix3 matrix, int row, int column);
float	matrix4_minor(t_matrix4 matrix, int row, int column);
float	matrix3_cofactor(t_matrix3 matrix, int row, int column);
float	matrix4_cofactor(t_matrix4 matrix, int row, int column);

// Tuple utils:
bool	tuples_are_equal(t_tuple a, t_tuple b);

// Math utils:
bool		floats_are_equal(float a, float b);

// Rendering utils
bool		pixel_fits_image(float x, float y, t_app *app);

// Render_routine.c
void		*render_routine(void *arg);
void		launch_render(t_app *app);
void		join_threads(t_thread_data *thread_data, int thread_count);

// Intersections:
t_intersection	*new_intersection(float t, t_object *object);
t_intersection	*hit(t_intersection *xs);
void			intersection_add_back(t_intersection **lst, 
				t_intersection *new);
void			free_intersections(t_intersection *lst);
t_intersection	*intersect_sphere(t_object *sphere, t_ray ray);

// Rays:
t_ray		new_ray(t_point origin, t_vector direction);
t_point		ray_position(t_ray ray, float t);
t_ray		transform_ray(t_ray ray, t_matrix4 matrix);

// Objects:
t_object	*sphere_new(void);

#endif

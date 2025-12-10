/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:38:13 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/10 18:56:03 by anpollan         ###   ########.fr       */
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

// Material default max values
# ifndef AMBIENT
#  define AMBIENT 0.1
# endif

# ifndef DIFFUSE
#  define DIFFUSE 0.9
# endif

# ifndef SPECULAR
#  define SPECULAR 0.9
# endif

# ifndef SHININESS
#  define SHININESS 200.0
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
}	t_color255;

typedef struct s_color_1
{
	float	r;
	float	g;
	float	b;
}	t_color;

typedef struct s_lighting
{
	t_vector	normalv;
	t_vector	lightv;
	float		light_dot_normal;
	t_vector	reflectv;
	float		reflect_dot_eye;
	float		factor;
	t_color		ambient;
	t_color		effective_color;
	t_color		diffuse;
	t_color		specular;
}	t_lighting;

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
	ERROR_WORLD,
	ERROR_PARSING,
	ERROR_THREADS,
	
}	t_exit_value;

typedef enum s_object_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_object_type;

typedef struct s_light
{
	t_color			intensity;
	t_point			position;
	// t_color_255		color_255;
}	t_light;

typedef struct s_material
{
	float	ambient;
	float	diffuse;
	float	specular;
	float	shininess;
	t_color	color;
}	t_material;

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
	float			diameter;
	float			height;
	t_matrix4		transform;
	t_matrix4		inverse_transform;
	t_material		material;
}	t_object;

typedef struct s_world
{
	t_camera		*camera;
	t_light			*light;
	t_object		**objects;
}	t_world;

typedef struct s_app
{
	int				monitor_width;
	int				monitor_height;
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_world			*scene;
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

typedef struct s_intersections
{
	int				count;
	t_intersection	*arr;
}	t_intersections;

typedef struct s_computations
{
	bool		inside;
	float		t;
	t_object	*object;
	t_point		point;
	t_vector	eyev;
	t_vector	normalv;
}	t_computations;

// Tests
void		free_object(t_object *object);
void		run_tests();
void		test_tuples(void);
void		test_matrices(void);
void		test_transformation(void);
void		test_rays(void);
void		render_chapter_5_scene(t_app *app);
void		test_normal(void);
void		test_color();
void		render_chapter_7_scene(t_app *app);
void		test_world();

// Debug
void		print_tuple(t_tuple tuple);
void		print_matrix2(t_matrix2 matrix);
void		print_matrix3(t_matrix3 matrix);
void		print_matrix4(t_matrix4 matrix);
void		print_color(t_color color);
void		print_color_255(t_color255 color);
void		print_point_light(t_light *point_light);
void		print_material(t_material material);
void		print_material(t_material material);
void		print_intersections(t_intersections *xs);
void		print_world(t_world *world);
void		print_computations(t_computations comps);
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
void		free_world(t_world *w);
void		free_intersections(t_intersections *xs);

// Tuples (vectors, points):
t_tuple		tuple(float x, float y, float z, float w);
t_vector	vector(float x, float y, float z);
t_point		point(float x, float y, float z);

// Transformation matrices
t_matrix4	translation_matrix4(
			float scale_x, float scale_y, float scale_z);
t_matrix4	scaling_matrix4(float scale_x, float scale_y, float scale_z);
t_matrix4	x_rotation(float radians);
t_matrix4	y_rotation(float radians);
t_matrix4	z_rotation(float radians);
t_matrix4	shearing(t_shear shear);

// Tuple math:
t_tuple		tuple_sum(t_tuple a, t_tuple b);
t_tuple		tuple_subtract(t_tuple a, t_tuple b);
t_tuple		tuple_scale_multiply(t_tuple tuple, float scalar);
t_tuple		tuple_scale_divide(t_tuple tuple, float divider);
t_tuple		tuple_negate(t_tuple tuple);

// Vector math:
float		vector_magnitude(t_tuple vector);
t_vector	normalize(t_vector vector);
float		dot(t_vector a, t_vector b);
t_vector	cross(t_vector a, t_vector b);

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
t_intersection	*intersection_new(float t, t_object *object);
t_intersection	intersection(float t, t_object *object);
t_intersection	*intersection_hit(t_intersection *xs);
void			intersection_add_back(t_intersection **lst, 
				t_intersection *new);
void			intersection_free(t_intersection *lst);
t_intersection	*intersect_sphere(t_object *sphere, t_ray ray);
t_intersections	*intersect(t_object *obj, t_ray ray);
t_intersections	*intersect_world(t_world *w, t_ray r);
void			quick_sort_intersections(t_intersection *xs, int start, int end);
t_computations	prepare_computations(t_intersection x, t_ray r);
t_intersection	hit(t_intersections *xs);

// Rays:
t_ray		ray(t_point origin, t_vector direction);
t_point		ray_position(t_ray ray, float t);
t_ray		ray_transform(t_ray ray, t_matrix4 matrix);
t_vector	reflect(t_vector in, t_vector normal);

// Objects:
t_object	*sphere_new(void);
t_object	*sphere_new_args(t_point center, float diameter, t_color255 color);
void		set_transform(t_object *object, t_matrix4 transform);

// Color & shading:
t_color		color(float r, float g, float b);
t_color255	color255(
		unsigned char r, unsigned char g, unsigned char b);
t_color		color_mix(t_color color_obj, t_color color_light);
t_color		color_multiply(t_color color, float multiplier);
t_color		color_sum(t_color color1, t_color color2);
t_color		color_from_color255(t_color255 color_255);
t_color255	color255_from_color(t_color color);
int			color_hex_from_color255(t_color255 color255);
int			color_hex_from_color(t_color color);
t_color		shade_hit(t_world *w, t_computations comps);
t_color		color_at(t_world *w, t_ray r);

// Light:
t_light	*point_light(t_point position, t_color intensity);
t_color	lighting(t_object *obj, t_light *light, t_point point, t_vector eyev);

// Material:
t_material		material(void);
t_material		material_with_color(t_color color);
t_material		material_change_color(t_material material, t_color color);

// Normal
t_vector	normal_at(t_object *obj, t_point point);

// World
t_world		*world();
t_world		*default_world();

// Camera
t_matrix4	view_transform(t_point from, t_point to, t_vector up);

#endif

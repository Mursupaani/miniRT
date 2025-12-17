/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:38:13 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/17 11:47:11 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <fcntl.h>
# include <float.h>
# include <stdatomic.h>
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
#  define EPSILON 1e-5
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
	double	x;
	double	y;
	double	z;
	double	w;
}	t_tuple;
typedef t_tuple	t_vector;
typedef t_tuple	t_point;

typedef struct s_matrix2
{
	double	data[2][2];
}	t_matrix2;

typedef struct s_matrix3
{
	double	data[3][3];
}	t_matrix3;

typedef struct s_matrix4
{
	double	data[4][4];
}	t_matrix4;

typedef struct s_shear
{
	double	xy;
	double	xz;
	double	yx;
	double	yz;
	double	zx;
	double	zy;
}	t_shear;

typedef struct s_color_255
{
	int	r;
	int	g;
	int	b;
}	t_color255;

typedef struct s_color_1
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_lighting
{
	t_vector	normalv;
	t_vector	lightv;
	double		light_dot_normal;
	t_vector	reflectv;
	double		reflect_dot_eye;
	double		factor;
	t_color		ambient;
	t_color		effective_color;
	t_color		diffuse;
	t_color		specular;
	t_color		color_at_point;
}	t_lighting;

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

typedef enum s_pattern_type
{
	NONE,
	STRIPE,
	GRADIENT,
	RING,
	CHECKER,
	TEST,
}	t_pattern_type;

typedef struct s_light
{
	t_color			intensity;
	t_point			position;
	// t_color_255		color_255;
}	t_light;

typedef struct s_pattern
{
	t_pattern_type	type;
	t_color			a;
	t_color			b;
	t_matrix4		transform;
	t_matrix4		inverse_transform;
	t_matrix4		inverse_transpose;
}	t_pattern;

typedef struct s_material
{
	double		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
	double		reflective;
	t_color		color;
	t_pattern	pattern;
}	t_material;

typedef struct s_object
{
	t_object_type	type;
	t_point			center;
	double			diameter;
	double			height;
	t_matrix4		transform;
	t_matrix4		inverse_transform;
	t_matrix4		inverse_transpose;
	t_material		material;
}	t_object;

typedef struct s_camera
{
	// t_point	view_point;
	// t_vector	orientation;
	double		fov;
	int			hsize;
	int			vsize;
	t_matrix4	transform;
	double		half_width;
	double		half_height;
	double		pixel_size;
}	t_camera;

typedef struct s_world
{
	t_camera		*camera;
	t_light			*light;
	t_object		**objects;
	int				object_count;
}	t_world;

typedef struct s_app
{
	int				monitor_width;
	int				monitor_height;
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_world			*scene;
	t_thread_data	*threads;
	atomic_int		keep_rendering;
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
	int				id;
	unsigned int	start_row;
	unsigned int	end_row;
	t_app			*app;
	pthread_t		thread_handle;
	atomic_int		*keep_rendering;
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
 * - double t: multiplier to calculate the distance travelled, where along the vector did the hit occur
 * - t_object object: the object that the ray hit
 * - t_intersection *next: address of the next hit
 */
typedef struct	s_intersection
{
	double					t;
	t_object				*object;
	// FIXME: Delete
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
	double		t;
	t_object	*object;
	t_point		point;
	t_point		over_point;
	t_vector	eyev;
	t_vector	normalv;
	t_vector	reflectv;
	bool		shadowed;
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
void		test_camera();
void		build_chapter7_world(t_app *app);;
void		test_shadows();
t_pattern	test_pattern();
void		test_patterns(void);
void		test_reflections();

// Old functions / unused?:
t_color			lighting_old(t_object *obj, t_light *light, t_point point, t_vector eyev);
t_intersection	*intersection_new(double t, t_object *object);
t_intersection	*intersection_hit(t_intersection *xs);
void			intersection_add_back(t_intersection **lst, 
				t_intersection *new);
void			intersection_free(t_intersection *lst);
t_intersection	*intersect_sphere(t_object *sphere, t_ray ray);

// Debug
void		print_tuple(t_tuple tuple);
void		print_ray(t_ray r);
void		print_matrix2(t_matrix2 matrix);
void		print_matrix3(t_matrix3 matrix);
void		print_matrix4(t_matrix4 matrix);
void		print_color(t_color color);
void		print_color_255(t_color255 color);
void		print_point_light(t_light *point_light);
void		print_material(t_material material);
void		print_material(t_material material);
void		print_intersections(t_intersections *xs);
void		print_object(t_object *o);
void		print_world(t_world *world);
void		print_computations(t_computations comps);
void		print_camera(t_camera *camera);
void		print_pattern(t_pattern pattern);

// App initialize and management:
t_app		*initialize_app(void);
void		initialize_hooks(t_app *app);

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
t_tuple		tuple(double x, double y, double z, double w);
t_vector	vector(double x, double y, double z);
t_point		point(double x, double y, double z);

// Transformation matrices
t_matrix4	translation_matrix4(
			double scale_x, double scale_y, double scale_z);
t_matrix4	scaling_matrix4(double scale_x, double scale_y, double scale_z);
t_matrix4	rotation_x(double radians);
t_matrix4	rotation_y(double radians);
t_matrix4	rotation_z(double radians);
t_matrix4	shearing(t_shear shear);

// Tuple math:
t_tuple		tuple_sum(t_tuple a, t_tuple b);
t_tuple		tuple_subtract(t_tuple a, t_tuple b);
t_tuple		tuple_scale_multiply(t_tuple tuple, double scalar);
t_tuple		tuple_scale_divide(t_tuple tuple, double divider);
t_tuple		tuple_negate(t_tuple tuple);

// Vector math:
double		vector_magnitude(t_tuple vector);
t_vector	normalize(t_vector vector);
double		dot(t_vector a, t_vector b);
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
double	matrix2_determinant(t_matrix2 matrix);
double	matrix3_determinant(t_matrix3 matrix);
double	matrix4_determinant(t_matrix4 matrix);
t_matrix2	matrix3_submatrix(t_matrix3 matrix, int row, int column);
t_matrix3	matrix4_submatrix(t_matrix4 matrix, int row, int column);
double	matrix3_minor(t_matrix3 matrix, int row, int column);
double	matrix4_minor(t_matrix4 matrix, int row, int column);
double	matrix3_cofactor(t_matrix3 matrix, int row, int column);
double	matrix4_cofactor(t_matrix4 matrix, int row, int column);

// Tuple utils:
bool	tuples_are_equal(t_tuple a, t_tuple b);

// Math utils:
bool		doubles_are_equal(double a, double b);

// Rendering utils
bool		pixel_fits_image(double x, double y, t_app *app);

// Render_routine.c
void		*render_routine(void *arg);
void		launch_render(t_app *app);
void		join_threads(t_thread_data *thread_data, int thread_count);

// Intersections:
t_intersection	intersection(double t, t_object *object);
t_intersections	*intersect(t_object *obj, t_ray ray);
t_intersections	*intersect_world(t_world *w, t_ray r);
void			quick_sort_intersections(t_intersection *xs, int start, int end);
t_computations	prepare_computations(t_intersection x, t_ray r);
t_intersection	hit(t_intersections *xs);

// Rays:
t_ray		ray(t_point origin, t_vector direction);
t_point		ray_position(t_ray ray, double t);
t_ray		ray_transform(t_ray ray, t_matrix4 matrix);
t_vector	reflect(t_vector in, t_vector normal);
t_ray		ray_for_pixel(t_camera *c, int px, int py);

// Objects:
t_object	*sphere_new(void);
t_object	*sphere_new_args(t_point center, double diameter, t_color255 color);
void		set_transform(t_object *object, t_matrix4 transform);
void		add_transform(t_object *object, t_matrix4 transform);
void		free_object_array(t_object **objs);

// Color & shading:
t_color		color(double r, double g, double b);
t_color255	color255(
		unsigned char r, unsigned char g, unsigned char b);
t_color		color_mix(t_color color_obj, t_color color_light);
t_color		color_multiply(t_color color, double multiplier);
t_color		color_sum(t_color color1, t_color color2);
t_color		color_subtract(t_color color1, t_color color2);
t_color		color_from_color255(t_color255 color_255);
t_color255	color255_from_color(t_color color);
int			color_hex_from_color255(t_color255 color255);
int			color_hex_from_color(t_color color);
t_color		shade_hit(t_world *w, t_computations comps);
t_color		color_at(t_world *w, t_ray r);
bool		is_shadowed(t_world *w, t_point p);

// Reflections:
t_color		reflected_color(t_world *w, t_computations comps);

// Patterns:
t_pattern	stripe_pattern(t_color a, t_color b);
t_color		stripe_at(t_pattern pattern, t_point p);
t_color		stripe_at_object(t_pattern ptrn, t_object *obj, t_point p);
t_pattern	gradient_pattern(t_color a, t_color b);
t_color		gradient_at(t_pattern ptrn, t_point p);
t_pattern	ring_pattern(t_color a, t_color b);
t_color		ring_at(t_pattern gradient, t_point p);
t_pattern	checkers_pattern(t_color a, t_color b);
t_color		checkers_at(t_pattern gradient, t_point p);
void		set_pattern_transform(t_pattern *ptrn, t_matrix4 transform);
void		add_pattern_transform(t_pattern *ptrn, t_matrix4 transform);
t_color		pattern_at_shape(t_pattern ptrn, t_object *obj, t_point p);

// Light:
t_light	*point_light(t_point position, t_color intensity);
t_color	lighting(t_computations comps, t_light *light);

// Material:
t_material		material(void);
t_material		material_with_color(t_color color);
t_material		material_change_color(t_material material, t_color color);

// Normal
t_vector	normal_at(t_object *obj, t_point point);

// World
t_world		*world();
t_world		*default_world();
t_object	**world_add_object(t_world *w, t_object *obj);

// Camera and view
t_camera	*camera(int hsize, int vsize, double fov);
t_matrix4	view_transform(t_point from, t_point to, t_vector up);

#endif

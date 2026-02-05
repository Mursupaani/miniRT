/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:38:13 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/02 21:01:22 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// FIXME: no need / included in "libft.h"
// # include <unistd.h>
// # include <stdlib.h>
// # include <string.h>
// # include <stdio.h>
// # include "MLX42/MLX42_Int.h"
// # include <stdint.h>

# include "libft.h"
# include <math.h>
# include <fcntl.h>
# include <float.h>
# include <stdatomic.h>
# include <pthread.h>
# include <sys/time.h>
# include "MLX42/MLX42.h"

# ifndef THREADS
#  define THREADS 4
# endif

# ifndef EPSILON
#  define EPSILON 1e-8
# endif

// Material default max values
# ifndef AMBIENT
#  define AMBIENT 0.2
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

# ifndef RECURSIONS
#  define RECURSIONS 7
# endif

# ifndef PIXELATE_SCALE
#  define PIXELATE_SCALE 32
# endif

# ifndef AA_SAMPLES
#  define AA_SAMPLES 4
# endif

# ifndef BUMP_MAP_SCALE
#  define BUMP_MAP_SCALE 0.007
# endif

# ifndef MOVEMENT_SPEED
#  define MOVEMENT_SPEED 0.3
# endif

# ifndef MOUSE_SPEED
#  define MOUSE_SPEED 0.01
# endif

# ifndef FOV_CHANGE
#  define FOV_CHANGE 1
# endif

# ifndef TARGET_FRAME_TIME
#  define TARGET_FRAME_TIME 125
# endif

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
	ERROR_UI,
	ERROR_THREAD_MEMORY,
}	t_exit_value;

typedef enum s_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CUBE,
	CONE,
}	t_object_type;

typedef enum s_cube_face
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	FRONT,
	BACK,
}	t_cube_face;

typedef enum s_pattern_type
{
	NONE,
	STRIPE,
	GRADIENT,
	RING,
	CHECKERS,
	TEST,
	MAP,
}	t_pattern_type;

typedef enum s_uv_pattern_type
{
	UV_CHECKERS,
	UV_ALIGN_CHECK,
	UV_ALIGN_CUBE,
	UV_TEXTURE,
	UV_CUBE_TEXTURE,
}	t_uv_pattern_type;

typedef struct s_look
{
	int32_t		x;
	int32_t		y;
	double		dx;
	double		dy;
}	t_look;

typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_tuple;

typedef t_tuple					t_vector;
typedef t_tuple					t_point;

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

typedef struct s_t_vals
{
	double	t0;
	double	t1;
}	t_t_vals;

typedef struct s_coefs
{
	double	a;
	double	b;
	double	c;
}	t_coefs;

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

typedef struct s_refraction
{
	double		n_ratio;
	double		cos_i;
	double		cos_t;
	double		sin2_t;
}	t_refraction;

typedef struct s_uv_align
{
	t_color	main;
	t_color	ul;
	t_color	ur;
	t_color	bl;
	t_color	br;
}	t_uv_align;

typedef struct s_cube_align
{
	t_uv_align	left;
	t_uv_align	right;
	t_uv_align	up;
	t_uv_align	down;
	t_uv_align	front;
	t_uv_align	back;
}	t_cube_align;

typedef struct s_face_layout
{
	int	col;
	int	row;
}	t_face_layout;

typedef struct s_light
{
	t_color	intensity;
	t_point	position;
	t_color	ambient_color;
	double	ambient_ratio;
}	t_light;

typedef struct s_uv_map
{
	double		u;
	double		v;
	t_cube_face	face;
}	t_uv_map;

typedef struct s_uv_pattern
{
	t_uv_pattern_type	type;
	double				width;
	double				height;
	t_uv_align			align_cube_sides[6];
	mlx_texture_t		*textures[6];
	t_uv_map			(*uv_map)(t_point);
}	t_uv_pattern;

typedef struct s_pattern
{
	t_pattern_type	type;
	t_color			a;
	t_color			b;
	t_matrix4		transform;
	t_matrix4		inverse_transform;
	t_matrix4		inverse_transpose;
	t_uv_pattern	uv_pattern;
}	t_pattern;

typedef struct s_material
{
	double		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
	double		reflective;
	double		transparency;
	double		refractive_index;
	t_color		color;
	t_pattern	pattern;
}	t_material;

typedef struct s_bump_map
{
	bool			has_bump_map;
	float			step_u;
	float			step_v;
	float			slope_u;
	float			slope_v;
	t_color			sample_hit;
	t_color			sample_step_u;
	t_color			sample_step_v;
	t_vector		tangent;
	t_vector		bitangent;
	t_uv_map		(*uv_map)(t_point);
	mlx_texture_t	*bump_map;
}	t_bump_map;

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
	// Cylinder and cone logic
	double			minimum;
	double			maximum;
	bool			closed;
	// Bump mapping
	t_bump_map		bump_map;
}	t_object;

typedef struct s_camera
{
	t_point		from;
	t_point		to;
	t_vector	up;
	t_vector	world_up;
	t_vector	relative_up;
	t_vector	forward;
	t_vector	left;
	double		yaw;
	double		pitch;
	double		fov;
	int			hsize;
	int			vsize;
	t_matrix4	transform;
	t_matrix4	inverse_transform;
	double		half_width;
	double		half_height;
	double		pixel_size;
	double		aspect_ratio;
}	t_camera;

typedef struct s_world
{
	t_camera	*camera;
	t_light		*light;
	t_object	**objects;
	int			object_count;
}	t_world;

typedef struct s_thread_data	t_thread_data;

typedef struct s_app
{
	// FIXME: Use bitmask to track app status?
	atomic_int		bitmask;
	// FIXME: Use bitmask to track app status?
	bool			left_mouse_down;
	bool			right_mouse_down;
	bool			moving;
	bool			show_hud;
	bool			frame_done;
	uint64_t		last_frame_time;
	int32_t			prev_mouse_x;
	int32_t			prev_mouse_y;
	t_object		*selected_object;
	double			selected_object_t;
	t_vector		selected_object_offset;
	int				scrn_w;
	int				scrn_h;
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*img_buffers[2];
	mlx_image_t		*hud;
	int				ready_percent;
	int				threads_ready_count;
	int				bg_img_index;
	size_t			pixel_count;
	size_t			img_buffer_size;
	t_world			*scene;
	t_thread_data	*threads;
	atomic_int		error;
	atomic_int		keep_rendering;
	atomic_int		pixelate;
	atomic_int		restart_render;
	atomic_int		go_wait;
	atomic_int		start_next_frame;
	atomic_int		data_changed;
	atomic_int		current_pixelate_scale;
	bool			parsing_success;
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

/**
 * @struct t_ray
 * @brief holds origin and direction of ray
 * 
 * Contains:
 * - t_point origin: start point of ray
 * - t_vector direction: direction of the ray
 */
typedef struct s_ray
{
	t_point		origin;
	t_vector	direction;
}	t_ray;

typedef struct s_thread_data
{
	int				id;
	unsigned int	start_row;
	unsigned int	end_row;
	t_app			*app;
	pthread_t		thread_handle;
	unsigned int	pixelate_scale;
	atomic_int		*keep_rendering;
	atomic_int		*start_next_frame;
	atomic_int		*current_pixelate_scale;
	atomic_int		new_frame_started;
	atomic_int		render_done;
	atomic_int		frame_done;
	atomic_int		error;
	// Rendering
	unsigned int	i;
	unsigned int	j;
	unsigned int	x;
	unsigned int	x_offset;
	unsigned int	y;
	unsigned int	y_offset;
	t_ray			ray;
	t_color			color;
}	t_thread_data;

/**
 * @struct t_intersection
 * @brief linked list to hold hits, e.g. entering and exiting a sphere
 * 
 * Contains:
 * - double t: multiplier to calculate the distance travelled,
 *   where along the vector did the hit occur
 * - t_object object: the object that the ray hit
 * - t_intersection *next: address of the next hit
 */

typedef struct s_local_intersect
{
	double	min;
	double	max;
}	t_loc_intersect;

typedef struct s_local_intersections
{
	t_loc_intersect	xt;
	t_loc_intersect	yt;
	t_loc_intersect	zt;
}	t_loc_intersections;

typedef struct s_intersection
{
	double		t;
	t_object	*object;
	// int			id;
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
	double		n1;
	double		n2;
	t_object	*object;
	t_point		point;
	t_point		over_point;
	t_point		under_point;
	t_vector	eyev;
	t_vector	normalv;
	t_vector	reflectv;
	bool		shadowed;
}	t_computations;

typedef struct s_specs
{
	t_point		center;
	double		diameter;
	t_point		position;
	t_vector	normal;
	t_color		color;
	t_object	*obj;
	t_vector	axis;
	double		height;
}	t_specs;

// App initialize and management:
t_app			*initialize_app(void);
void			initialize_hooks(t_app *app);
void			wait_for_threads_to_be_ready(t_app *app);
void			signal_threads_to_go_wait(t_app *app);
void			restart_render(t_app *app);
void			display_finished_frame(t_app *app);
bool			all_threads_finished_frame(t_app *app);
bool			all_threads_started_new_frame(t_app *app);
void			empty_image_buffer(struct mlx_image *img, size_t pixel_count);
void			print_hud(t_app *app);
uint64_t		get_time_ms(void);

// Hooks:
void			handle_mouse_scroll(double xdelta, double ydelta, void *param);
void			handle_mouse(
					enum mouse_key key, enum action action,
					enum modifier_key mod_key, void *param);
void			handle_keypress(mlx_key_data_t keydata, void *param);
void			close_window_mouse(void *param);
void			per_frame_loop(void *param);
bool			mouse_not_moved(t_app *app, t_look look);

// Memory handling and exit:
void			free_app_memory(t_app *app);
void			exit_and_free_memory(int exit_code, t_app *app);
void			free_world(t_world *w);
void			*memory_alloc_error(atomic_int *err);
// void		free_intersections(t_intersections *xs);
void			free_intersections(t_intersections **xs);

// Tuples (vectors, points):
t_tuple			tuple(double x, double y, double z, double w);
t_vector		vector(double x, double y, double z);
t_point			point(double x, double y, double z);

// Transformation matrices
t_matrix4		translation_matrix4(
					double scale_x, double scale_y, double scale_z);
t_matrix4		scaling_matrix4(double scale_x, double scale_y, double scale_z);
t_matrix4		rotation_x(double radians);
t_matrix4		rotation_y(double radians);
t_matrix4		rotation_z(double radians);
t_matrix4		shearing(t_shear shear);
t_matrix4		rotation_matrix_from_orientation(t_vector orientation);

// Tuple math:
t_tuple			tuple_sum(t_tuple a, t_tuple b);
t_tuple			tuple_subtract(t_tuple a, t_tuple b);
t_tuple			tuple_scale_multiply(t_tuple tuple, double scalar);
t_tuple			tuple_scale_divide(t_tuple tuple, double divider);
t_tuple			tuple_negate(t_tuple tuple);

// Vector math:
double			vector_magnitude(t_tuple vector);
t_vector		normalize(t_vector vector);
double			dot(t_vector a, t_vector b);
t_vector		cross(t_vector a, t_vector b);

// Matrix utils:
bool			matrix4s_are_equal(t_matrix4 m1, t_matrix4 m2);
t_matrix4		matrix4_identity(void);

// Matrix math:
t_matrix4		matrix4_multiply(t_matrix4 m1, t_matrix4 m2);
t_tuple			matrix4_and_tuple_multiply(t_matrix4 matrix, t_tuple tuple);
t_matrix4		matrix4_transpose(t_matrix4 matrix);
t_matrix4		matrix4_invert(t_matrix4 matrix);

// Matrix determinants, submatrices, minors and cofactors:
double			matrix2_determinant(t_matrix2 matrix);
double			matrix3_determinant(t_matrix3 matrix);
double			matrix4_determinant(t_matrix4 matrix);
t_matrix2		matrix3_submatrix(t_matrix3 matrix, int row, int column);
t_matrix3		matrix4_submatrix(t_matrix4 matrix, int row, int column);
double			matrix3_minor(t_matrix3 matrix, int row, int column);
double			matrix4_minor(t_matrix4 matrix, int row, int column);
double			matrix3_cofactor(t_matrix3 matrix, int row, int column);
double			matrix4_cofactor(t_matrix4 matrix, int row, int column);

// Tuple utils:
bool			tuples_are_equal(t_tuple a, t_tuple b);

// Math utils:
bool			doubles_are_equal(double a, double b);
double			rad_to_deg(double rad);
double			deg_to_rad(double deg);

// Rendering utils
bool			pixel_fits_image(double x, double y, t_app *app);

// Render_routine.c
void			*render_routine(void *arg);
void			launch_render(t_app *app);
void			join_threads(t_thread_data *thread_data, int thread_count);
void			render_pixelated(t_thread_data *data);

// Intersections:
t_intersection	intersection(double t, t_object *object);
t_intersections	*intersect(t_object *obj, t_ray ray, atomic_int *err);
t_intersections	*intersect_world(t_world *w, t_ray r, atomic_int *err);
void			quick_sort_intersections(
					t_intersection *xs, int start, int end);
t_intersection	hit(t_intersections *xs);
t_intersections	*add_intersection_to_arr(
					t_intersection new, t_intersections *xs, atomic_int *err);
t_intersections	*malloc_intersections(int xs_count, atomic_int *err);

// Prepare computations:
t_computations	prepare_computations(
					t_intersection x, t_ray r,
					t_intersections *xs, atomic_int *err);
void			handle_n1(t_computations *comps, t_intersection **containers);
void			handle_n2(t_computations *comps, t_intersection **containers);

// Rays:
t_ray			ray(t_point origin, t_vector direction);
t_point			ray_position(t_ray ray, double t);
t_ray			ray_transform(t_ray ray, t_matrix4 matrix);
t_vector		reflect(t_vector in, t_vector normal);
t_ray			calculate_ray(t_camera *c, double world_x, double world_y);
t_ray			ray_for_pixel(t_camera *c, int px, int py);

// Objects:
t_object		*object_new(t_object_type type);
t_object		*plane_new(void);
t_object		*cube_new(void);
t_object		*cylinder_new(void);
void			set_transform(t_object *object, t_matrix4 transform);
void			add_transform(t_object *object, t_matrix4 transform);
void			free_object_array(t_object **objs);

// Color & shading:
t_color			color(double r, double g, double b);
t_color255		color255(
					unsigned char r, unsigned char g, unsigned char b);
t_color			color_from_hex_color(uint32_t hex_color);
t_color			color_mix(t_color color_obj, t_color color_light);
t_color			color_multiply(t_color color, double multiplier);
t_color			color_sum(t_color color1, t_color color2);
t_color			color_subtract(t_color color1, t_color color2);
t_color			color_from_color255(t_color255 color_255);
t_color255		color255_from_color(t_color color);
uint32_t		color_hex_from_color255(t_color255 color255);
uint32_t		color_hex_from_color(t_color color);
t_color			shade_hit(t_world *w, t_computations comps,
					int recursions, atomic_int *err);
t_color			color_at(t_world *w, t_ray r, int recursions, atomic_int *err);
bool			is_shadowed(t_world *w, t_point p, atomic_int *err);
t_color			pixel_at(mlx_texture_t *texture, int x, int y);

// Reflections:
t_color			reflected_color(t_world *w, t_computations comps,
					int reflections, atomic_int *err);

// Refractions:
t_color			refracted_color(t_world *w, t_computations comps,
					int recursions, atomic_int *err);
double			schlick(t_computations comps);

// Patterns:
t_pattern		create_pattern(int type, t_color a, t_color b);
t_pattern		stripe_pattern(t_color a, t_color b);
t_color			stripe_at(t_pattern pattern, t_point p);
t_color			stripe_at_object(t_pattern ptrn, t_object *obj, t_point p);
t_pattern		gradient_pattern(t_color a, t_color b);
t_color			gradient_at(t_pattern ptrn, t_point p);
t_pattern		ring_pattern(t_color a, t_color b);
t_color			ring_at(t_pattern gradient, t_point p);
t_pattern		checkers_pattern(t_color a, t_color b);
t_color			checkers_at(t_pattern gradient, t_point p);
void			set_pattern_transform(t_pattern *ptrn, t_matrix4 transform);
void			add_pattern_transform(t_pattern *ptrn, t_matrix4 transform);
t_color			pattern_at(t_pattern ptrn, t_point ptrn_point);
t_color			pattern_at_shape(t_pattern ptrn, t_object *obj, t_point p);

// UV Patterns:
t_pattern		texture_map(t_pattern ptrn, t_uv_map (*uv_map)(t_point));
t_pattern		uv_image(mlx_texture_t	*texture);
t_pattern		uv_image_cube(mlx_texture_t *textures[6]);
t_pattern		uv_image_cube_same_texture(mlx_texture_t *texture);
t_pattern		uv_checkers(double w, double h, t_color a, t_color b);
t_pattern		uv_align_cube_pattern(void);
t_pattern		uv_align_check_pattern(void);
t_uv_map		spherical_map(t_point p);
t_uv_map		planar_map(t_point p);
t_uv_map		cylindrical_map(t_point p);
t_uv_map		cubic_map(t_point p);
t_uv_map		cubic_atlas_map(t_point p);
int				calculate_pixel_offset(int x, int y, mlx_texture_t *texture);

t_color			handle_uv_pattern(t_pattern ptrn, t_point ptrn_point);
t_color			uv_pattern_at(t_pattern ptrn, t_uv_map uv);
t_cube_face		face_from_point(t_point p);
t_uv_map		cube_uv_up(t_point p);
t_uv_map		cube_uv_down(t_point p);
t_uv_map		cube_uv_left(t_point p);
t_uv_map		cube_uv_right(t_point p);
t_uv_map		cube_uv_front(t_point p);
t_uv_map		cube_uv_back(t_point p);

// Light:
t_light			*point_light(t_point position, t_color intensity);
t_color			lighting(t_computations comps, t_light *light);

// Material:
t_material		material(void);
t_material		material_with_color(t_color color);
t_material		material_change_color(t_material material, t_color color);

// Normal
t_vector		normal_at(t_object *obj, t_point point);
t_vector		local_normal_at(t_object *obj, t_point local_point);
t_vector		plane_normal_at(t_object *plane, t_point local_point);
t_vector		sphere_normal_at(t_object *sphere, t_point local_point);
t_vector		cylinder_normal_at(t_object *cylinder, t_point local_point);
t_vector		cone_normal_at(t_object *cone, t_point local_point);
t_vector		cube_normal_at(t_object *obj, t_point world_point);

// World
t_world			*world(void);
t_world			*default_world(void);
t_object		**add_object_to_world(t_object *obj, t_world *w);

// Camera and view
t_camera		*camera(int hsize, int vsize, double fov);
void			init_camera_yaw_and_pitch(t_camera *c);
double			pixel_size(t_camera *camera);
// t_matrix4	view_transform(t_point from, t_point to, t_vector up);
t_matrix4		view_transform(
					t_point from, t_point to, t_vector up, t_camera *c);
void			set_camera_transform(t_camera *camera, t_matrix4 transform);

// Sphere
t_object		*sphere_new(void);
t_object		*sphere_new_args(
					t_point center, double diameter, t_color255 color);
t_intersections	*intersect_sphere(
					t_object *sphere, t_ray local_ray, atomic_int *err);

// Plane
t_intersections	*intersect_plane(
					t_object *plane, t_ray local_ray, atomic_int *err);

// Cone
t_object		*cone_new(void);
t_intersections	*intersect_cone(
					t_object *cone, t_ray local_ray, atomic_int *err);
t_coefs			calculate_cone_coefs(t_ray local_ray);
t_intersections	*intersect_cone_caps(
					t_object *cone, t_ray local_ray,
					t_intersections *xs, atomic_int *err);
bool			check_cone_cap(t_ray local_ray, double t, double limit);

// Cube
t_intersections	*intersect_cube(
					t_object *cube, t_ray local_ray, atomic_int *err);
double			min_of_max_t(double xtmin, double ytmin, double ztmin);
double			max_of_min_t(double xtmin, double ytmin, double ztmin);
void			swap_doubles(double *tmin, double *tmax);
double			max_absolute_coord_component(double x, double y, double z);

// Cylinder
t_intersections	*intersect_cylinder(
					t_object *cylinder, t_ray local_ray, atomic_int *err);
t_intersections	*intersect_cylinder_caps(
					t_object *cylinder, t_ray local_ray,
					t_intersections *xs, atomic_int *err);
bool			check_cylinder_cap(t_ray local_ray, double t);

// Bump map
void			apply_bump_map_on_normal(
					t_object *obj, t_vector *local_normal, t_point local_point);
void			get_tangent_and_bitangent(t_object_type obj_type,
					t_vector local_normal, t_bump_map *bm);

// Interact world
void			select_object_from_screen(t_app *app, atomic_int *err);
void			move_oject_on_screen(t_app *app);
void			resize_selected_object(t_app *app, double ydelta);
void			rotate_selected_object(t_app *app, double ydelta);
void			transform_light(t_app *app, double ydelta);
void			handle_movement(t_app *app);
void			handle_looking_around(t_app *app);
void			change_camera_fov(t_app *app, double ydelta);

// Parsing
void			parse_rt_file(char **av, t_app *app);
void			skip_whitespace(char **str);
bool			filetype_is_valid(char *filename);
void			parse_error(char *message, t_app *app);
bool			parse_double(char **str, double *result);
bool			parse_int(char **str, int *result);
double			ft_strtod(const char *str, char **endptr, int *i);
bool			parse_vector(char **str, t_vector *vec);
bool			parse_point(char **str, t_point *point);
bool			parse_color(char **str, t_color *color);
// void			parse_ambient_component(char *line, t_app *app);
void			parse_ambient_component(char **line, t_app *app);
// void			parse_camera(char *line, t_app *app);
void			parse_camera(char **line, t_app *app);
// void			parse_light(char *line, t_app *app);
void			parse_light(char **line, t_app *app);
// void			parse_sphere(char *line, t_app *app);
void			parse_sphere(char **line, t_app *app);
// void			parse_plane(char *line, t_app *app);
void			parse_plane(char **line, t_app *app);
// void			parse_cylinder(char *line, t_app *app);
void			parse_cylinder(char **line, t_app *app);
// void			parse_cube(char *line, t_app *app);
void			parse_cube(char **line, t_app *app);
// void			parse_cone(char *line, t_app *app);
void			parse_cone(char **line, t_app *app);
t_object		*create_sphere_object(
					t_point pos, double diameter, t_color color);
t_object		*create_plane_object(
					t_point pos, t_vector normal, t_color color);
t_object		*create_cylinder_object(t_specs s);
t_object		*create_cube_object(t_specs s);
t_object		*create_cone_object(t_specs s);
void			get_cylinder_data(char **line, t_specs *s, t_app *app);
void			validate_normal_vector(t_vector normal, t_app *app);
void			validate_orientation_vector(t_vector ornt, t_app *app);
bool			is_valid_axis(t_vector v);

// Texture parsing
bool			parse_texture(char **str, mlx_texture_t **texture, t_app *app);
bool			parse_cube_textures(char **str, mlx_texture_t *textures[6],
					t_app *app);
void			apply_texture_or_pattern_to_object(
					t_object *obj, char **line, t_app *app);

// Pattern parsing
void			parse_pattern(t_object *obj, char **line, t_app *app);

// Bump map parsing
bool			parse_bump_map(char **str, t_bump_map *bump_map, t_app *app);
void			apply_bump_map_to_object(
					t_object *obj, char **line, t_app *app);

// Light behavior parsing
// void			apply_light_behavior(t_object *obj, t_app *app, char *line);
void			apply_light_behavior(t_object *obj, t_app *app, char **line);
// void			apply_reflect_and_refract(
// 					t_object *obj, t_app *app, char *line);
void			apply_reflect_and_refract(
					t_object *obj, t_app *app, char **line);

// Anti-aliasing 
double			pseudo_random(unsigned int x, unsigned int y, unsigned int s);
t_color			get_aa_color(t_thread_data *data);

#endif

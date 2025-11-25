#include "minirt.h"

static void	calculate_discriminant(t_ray ray, float *a, float *b, float *c)
{
	t_vector	sphere_to_ray;

	sphere_to_ray = tuple_subtract(ray.origin, new_point(0, 0, 0));
	*a = vector_dot_product(ray.direction, ray.direction);
	*b = 2 * vector_dot_product(ray.direction, sphere_to_ray);
	*c = vector_dot_product(sphere_to_ray, sphere_to_ray) - 1;
}

t_intersection	*intersect_sphere(t_object *sphere, t_ray ray)
{
	t_ray			local_ray;
	float			transform_inv[4][4];
	float			abc[3];
	float			disc;
	t_intersection	xs;

	xs = NULL;
	matrix4_invert(sphere->transform, transform_inv);
}

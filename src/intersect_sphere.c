#include "minirt.h"

static void	calculate_coefs(t_ray ray, float *a, float *b, float *c)
{
	t_vector	sphere_to_ray;

	sphere_to_ray = tuple_subtract(ray.origin, point(0, 0, 0));
	*a = dot(ray.direction, ray.direction);
	*b = 2 * dot(ray.direction, sphere_to_ray);
	*c = dot(sphere_to_ray, sphere_to_ray) - 1;
}

t_intersection	*intersect_sphere(t_object *sphere, t_ray ray)
{
	t_ray			local_ray;
	t_matrix4		inv_matrix;
	float			abc[3];
	float			disc;
	t_intersection	*xs;

	xs = NULL;
	inv_matrix = sphere->inverse_transform;
	local_ray = ray_transform(ray, inv_matrix);
	calculate_coefs(local_ray, &abc[0], &abc[1], &abc[2]);
	disc = (abc[1] * abc[1]) - (4 * abc[0] * abc[2]);
	if (disc < 0)
		return (NULL);
	intersection_add_back(&xs, intersection_new((-abc[1] - sqrtf(disc))
							/ (2 * abc[0]), sphere));
	intersection_add_back(&xs, intersection_new((-abc[1] + sqrtf(disc))
							/ (2 * abc[0]), sphere));
	return (xs);
}

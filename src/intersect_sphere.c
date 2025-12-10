#include "minirt.h"

static void	calculate_coefs(t_ray ray, float *a, float *b, float *c)
{
	t_vector	sphere_to_ray;

	sphere_to_ray = tuple_subtract(ray.origin, point(0, 0, 0));
	*a = dot(ray.direction, ray.direction);
	*b = 2 * dot(ray.direction, sphere_to_ray);
	*c = dot(sphere_to_ray, sphere_to_ray) - 1;
}

static t_intersections	*intersect_with_sphere(t_object *sphere, t_ray ray)
{
	t_ray			local_ray;
	t_matrix4		inv_matrix;
	float			abc[3];
	float			disc;
	t_intersections	*xs;

	inv_matrix = sphere->inverse_transform;
	local_ray = ray_transform(ray, inv_matrix);
	calculate_coefs(local_ray, &abc[0], &abc[1], &abc[2]);
	disc = (abc[1] * abc[1]) - (4 * abc[0] * abc[2]);
	if (disc < 0)
		return (NULL);
	xs = malloc(sizeof(t_intersections));
	if (!xs)
		// Exit and free if malloc fails?
		return (NULL);
	xs->arr = malloc(sizeof(t_intersection) * 2);
	if (!xs->arr)
		// Exit and free if malloc fails?
		return (NULL);
	xs->arr[0] = intersection((-abc[1] - sqrtf(disc)) / (2 * abc[0]), sphere);
	xs->arr[1] = intersection((-abc[1] + sqrtf(disc)) / (2 * abc[0]), sphere);
	xs->count = 2;
	quick_sort_intersections(xs->arr, 0, xs->count - 1);
	return (xs);
}

t_intersections *intersect(t_object *obj, t_ray ray)
{
	if (!obj)
		return (NULL);
	if (obj->type == SPHERE)
		return (intersect_with_sphere(obj, ray));
	else
		return (NULL);
}

// FIXME: Start using functions above?
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

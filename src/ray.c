#include "minirt.h"

t_ray	new_ray(t_point origin, t_vector direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_point	ray_position(t_ray ray, float t)
{
	t_vector	distance;

	distance = tuple_scale_multiply(ray.direction, t);
	return (tuple_sum(ray.origin, distance));
}

t_ray	transform(t_ray ray, float matrix[4][4])
{
	t_ray	new_ray;

	new_ray.origin = matrix4_and_tuple_multiply(matrix, ray.origin);
	new_ray.direction = matrix4_and_tuple_multiply(matrix, ray.direction);
	return (new_ray);
}

#include "minirt.h"

t_object	*plane_new()
{
	return (object_new(PLANE));
	// t_object	*plane;
	//
	// plane = ft_calloc(1, sizeof(t_object));
	// if (!plane)
	// 	return (NULL);
	// plane->type = PLANE;
	// plane->transform = matrix4_identity();
	// plane->inverse_transform = matrix4_identity();
	// plane->inverse_transpose = matrix4_identity();
	// plane->material = material();
	// return (plane);
}

t_intersections	*intersect_plane(t_object *plane, t_ray local_ray)
{
	t_intersections	*xs;
	double			t;

	if (fabs(local_ray.direction.y) < EPSILON)
		return (NULL);
	t = -local_ray.origin.y / local_ray.direction.y;
	xs = ft_calloc(1, sizeof(t_intersections));
	if (!xs)
		return (NULL);
	xs->count = 1;
	xs->arr = ft_calloc(1, sizeof(t_intersection));
	if (!xs->arr)
	{
		free(xs);
		return (NULL);
	}
	xs->arr[0] = intersection(t, plane);
	return (xs);
}

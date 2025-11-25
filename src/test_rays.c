#include "minirt.h"

static void	free_object(t_object *object)
{
	if (!object)
		return ;
	if (object->color_1)
		free(object->color_1);
	if (object->color_255)
		free(object->color_255);
	free(object);
	object = NULL;
}

static int	count_xs(t_intersection *xs)
{
	int i;

	i = 0;
	while (xs)
	{
		xs = xs->next;
		i++;
	}
	return (i);
}

void	test_rays(void)
{
	t_point	result;

	// Print position after applying t
	printf("--- Testing Ray implementation ---\n");
	result = ray_position(new_ray(init_point(2, 3, 4), init_vector(1, 0, 0)), 0);
	printf("1.0 Ray position(r, 0): %.1f, %.1f, %.1f, %.1f\n", result.x, result.y, result.z, result.w);
	result = ray_position(new_ray(init_point(2, 3, 4), init_vector(1, 0, 0)), 1);
	printf("1.1 Ray position(r, 1): %.1f, %.1f, %.1f, %.1f\n", result.x, result.y, result.z, result.w);
	result = ray_position(new_ray(init_point(2, 3, 4), init_vector(1, 0, 0)), -1);
	printf("1.2 Ray position(r, -1): %.1f, %.1f, %.1f, %.1f\n", result.x, result.y, result.z, result.w);
	result = ray_position(new_ray(init_point(2, 3, 4), init_vector(1, 0, 0)), 2.5);
	printf("1.3 Ray position(r, 2.5): %.1f, %.1f, %.1f, %.1f\n", result.x, result.y, result.z, result.w);
	
	// Print intersections with sphere
	t_ray	ray = new_ray(init_point(0, 0, -5), init_vector(0, 0, 1));
	t_object	*sphere = sphere_new();
	t_intersection	*xs = intersect_sphere(sphere, ray);
	t_intersection	*xs_head = xs;
	printf("--- Intersections ---\n");
	printf("1.0 Ray intersects sphere at center\n");
	printf("Intersection count: %d\n", count_xs(xs));
	int i = 0;
	while (xs)
	{
		printf("t%d is: %.1f\n", i, xs->t);
		xs = xs->next;
		i++;
	}
	free_intersections(xs_head);
	printf("2.0 Ray intersects sphere at a tangent\n");
	ray = new_ray(init_point(0, 1, -5), init_vector(0, 0, 1));
	xs = intersect_sphere(sphere, ray);
	xs_head = xs;
	printf("Intersection count: %d\n", count_xs(xs));
	i = 0;
	while (xs)
	{
		printf("t%d is %.1f\n", i, xs->t);
		xs = xs->next;
		i++;
	}
	free_intersections(xs_head);
	printf("3.0 Ray misses the sphere\n");
	ray = new_ray(init_point(0, 2, -5), init_vector(0, 0, 1));
	xs = intersect_sphere(sphere, ray);
	xs_head = xs;
	printf("Intersection count: %d\n", count_xs(xs));
	i = 0;
	while (xs)
	{
		printf("t%d is %.1f\n", i, xs->t);
		xs =xs->next;
		i++;
	}
	free_intersections(xs_head);
	printf("4.0 Ray originates inside a sphere\n");
	ray = new_ray(init_point(0, 0, 0), init_vector(0, 0, 1));
	xs = intersect_sphere(sphere, ray);
	xs_head = xs;
	printf("Intersection count: %d\n", count_xs(xs));
	i = 0;
	while (xs)
	{
		printf("t%d is %.1f\n", i, xs->t);
		xs = xs->next;
		i++;
	}
	free_intersections(xs_head);
	printf("5.0 A sphere is behind the ray\n");
	ray = new_ray(init_point(0, 0, 5), init_vector(0, 0, 1));
	xs = intersect_sphere(sphere, ray);
	xs_head = xs;
	printf("Intersection count: %d\n", count_xs(xs));
	i = 0;
	while (xs)
	{
		printf("t%d is %.1f\n", i, xs->t);
		xs = xs->next;
		i++;
	}
	free_intersections(xs_head);

	// Print hits
	printf("--- Hits ---\n");
	printf("1.0 Both are positive values, print the closest hit\n");
	xs = NULL;
	intersection_add_back(&xs, new_intersection(1, sphere));
	intersection_add_back(&xs, new_intersection(2, sphere));
	t_intersection	*closest = hit(xs);
	if (closest)
		printf("closet t is: %.1f\n", closest->t);
	else
		printf("No hit\n");
	free_intersections(xs);
	printf("2.0 One value is negative\n");
	xs = NULL;
	intersection_add_back(&xs, new_intersection(1, sphere));
	intersection_add_back(&xs, new_intersection(-1, sphere));
	closest = hit(xs);
	if (closest)
		printf("closet t is: %.1f\n", closest->t);
	else
		printf("No hit\n");
	free_intersections(xs);
	printf("3.0 All have negative values\n");
	xs = NULL;
	intersection_add_back(&xs, new_intersection(-2, sphere));
	intersection_add_back(&xs, new_intersection(-1, sphere));
	closest = hit(xs);
	if (closest)
	printf("closet t is: %.1f\n", closest->t);
	else
		printf("No hit\n");
	free_intersections(xs);

	free_object(sphere);
}

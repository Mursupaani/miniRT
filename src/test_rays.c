#include "MLX42/MLX42.h"
#include "minirt.h"

void	free_object(t_object *object)
{
	if (!object)
		return ;
	free(object);
	object = NULL;
}
/*
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
	result = ray_position(ray(point(2, 3, 4), vector(1, 0, 0)), 0);
	printf("1.0 Ray position(r, 0): %.1f, %.1f, %.1f, %.1f\n", result.x, result.y, result.z, result.w);
	result = ray_position(ray(point(2, 3, 4), vector(1, 0, 0)), 1);
	printf("1.1 Ray position(r, 1): %.1f, %.1f, %.1f, %.1f\n", result.x, result.y, result.z, result.w);
	result = ray_position(ray(point(2, 3, 4), vector(1, 0, 0)), -1);
	printf("1.2 Ray position(r, -1): %.1f, %.1f, %.1f, %.1f\n", result.x, result.y, result.z, result.w);
	result = ray_position(ray(point(2, 3, 4), vector(1, 0, 0)), 2.5);
	printf("1.3 Ray position(r, 2.5): %.1f, %.1f, %.1f, %.1f\n", result.x, result.y, result.z, result.w);
	
	// Print intersections with sphere
	t_ray	r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_object	*sphere = sphere_new_args(point(0, 0, 0), 1, color255(255, 255, 255));
	t_intersection	*xs = intersect(sphere, r);
	t_intersection	*xs_head = xs;
	printf("--- Intersections ---\n");
	printf("2.0 Ray intersects sphere at two points\n");
	printf("Intersection count: %d\n", count_xs(xs));
	int i = 0;
	while (xs)
	{
		printf("t%d is: %.1f\n", i, xs->t);
		xs = xs->next;
		i++;
	}
	intersection_free(xs_head);
	printf("2.1 Ray intersects sphere at a tangent\n");
	r = ray(point(0, 1, -5), vector(0, 0, 1));
	xs = intersect(sphere, r);
	xs_head = xs;
	printf("Intersection count: %d\n", count_xs(xs));
	i = 0;
	while (xs)
	{
		printf("t%d is %.1f\n", i, xs->t);
		xs = xs->next;
		i++;
	}
	intersection_free(xs_head);
	printf("2.2 Ray misses the sphere\n");
	r = ray(point(0, 2, -5), vector(0, 0, 1));
	xs = intersect(sphere, r);
	xs_head = xs;
	printf("Intersection count: %d\n", count_xs(xs));
	i = 0;
	while (xs)
	{
		printf("t%d is %.1f\n", i, xs->t);
		xs =xs->next;
		i++;
	}
	intersection_free(xs_head);
	printf("2.3 Ray originates inside a sphere\n");
	r = ray(point(0, 0, 0), vector(0, 0, 1));
	xs = intersect(sphere, r);
	xs_head = xs;
	printf("Intersection count: %d\n", count_xs(xs));
	i = 0;
	while (xs)
	{
		printf("t%d is %.1f\n", i, xs->t);
		xs = xs->next;
		i++;
	}
	intersection_free(xs_head);
	printf("2.4 A sphere is behind the ray\n");
	r = ray(point(0, 0, 5), vector(0, 0, 1));
	xs = intersect(sphere, r);
	xs_head = xs;
	printf("Intersection count: %d\n", count_xs(xs));
	i = 0;
	while (xs)
	{
		printf("t%d is %.1f\n", i, xs->t);
		xs = xs->next;
		i++;
	}
	intersection_free(xs_head);

	// Print hits
	printf("--- Hits ---\n");
	printf("3.0 Both are positive values, print the closest intersection_hit\n");
	xs = NULL;
	intersection_add_back(&xs, intersection_new(1, sphere));
	intersection_add_back(&xs, intersection_new(2, sphere));
	t_intersection	*closest = intersection_hit(xs);
	if (closest)
		printf("closet xs is at t: %.1f\n", closest->t);
	else
		printf("No intersection_hit\n");
	intersection_free(xs);
	printf("3.1 One value is negative\n");
	xs = NULL;
	intersection_add_back(&xs, intersection_new(1, sphere));
	intersection_add_back(&xs, intersection_new(-1, sphere));
	closest = intersection_hit(xs);
	if (closest)
		printf("closet xs is at t: %.1f\n", closest->t);
	else
		printf("No intersection_hit\n");
	intersection_free(xs);
	printf("3.2 All have negative values\n");
	xs = NULL;
	intersection_add_back(&xs, intersection_new(-2, sphere));
	intersection_add_back(&xs, intersection_new(-1, sphere));
	closest = intersection_hit(xs);
	if (closest)
	printf("closet xs is at t: %.1f\n", closest->t);
	else
		printf("No intersection_hit\n");
	intersection_free(xs);
	printf("3.3 Hit is always lowest nonnegative value\n");
	xs = NULL;
	intersection_add_back(&xs, intersection_new(5, sphere));
	intersection_add_back(&xs, intersection_new(7, sphere));
	intersection_add_back(&xs, intersection_new(-3, sphere));
	intersection_add_back(&xs, intersection_new(2, sphere));
	closest = intersection_hit(xs);
	if (closest)
	printf("closet xs is at t: %.1f\n", closest->t);
	else
		printf("No intersection_hit\n");
	intersection_free(xs);

	// Transforming Rays
	printf("--- Transform rays ---\n");
	t_ray	transformed_ray;
	r = ray(point(1, 2, 3), vector(0, 1, 0));
	t_matrix4	matrix = translation_matrix4(3, 4, 5);
	transformed_ray = ray_transform(r, matrix);
	printf("4.0 Translating a ray\n");
	printf("Translated ray origin: %.1f, %.1f, %.1f\n", transformed_ray.origin.x, transformed_ray.origin.y, transformed_ray.origin.z);
	printf("Translated ray direction: %.1f, %.1f, %.1f\n", transformed_ray.direction.x, transformed_ray.direction.y, transformed_ray.direction.z);
	printf("4.1 Scaling a ray\n");
	r = ray(point(1, 2, 3), vector(0, 1, 0));
	matrix = scaling_matrix4(2, 3, 4);
	transformed_ray = ray_transform(r, matrix);
	printf("Scaled ray origin: %.1f, %.1f, %.1f\n", transformed_ray.origin.x, transformed_ray.origin.y, transformed_ray.origin.z);
	printf("Scaled ray direction: %.1f, %.1f, %.1f\n", transformed_ray.direction.x, transformed_ray.direction.y, transformed_ray.direction.z);

	// Transforming sphere
	printf("--- Transforming sphere ---\n");
	printf("5.0 Intersecting a scaled sphere with a ray\n");
	r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_matrix4	scaling = scaling_matrix4(2, 2, 2);
	set_transform(sphere, scaling);
	xs = NULL;
	xs = intersect(sphere, r);
	xs_head = xs;
	printf("Intersection count is: %d\n", count_xs(xs));
	i = 0;
	while (xs)
	{
		printf("t%d is %.1f\n", i, xs->t);
		xs = xs->next;
		i++;
	}
	intersection_free(xs_head);
	printf("5.1 Intersecting a translated sphere with a ray\n");
	r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_matrix4	translation = translation_matrix4(5, 0, 0);
	set_transform(sphere, translation);
	xs = NULL;
	xs = intersect(sphere, r);
	xs_head = xs;
	printf("Intersection count is: %d\n", count_xs(xs));
	i = 0;
	while (xs)
	{
		printf("t%d is %.1f\n", i, xs->t);
		xs = xs->next;
		i++;
	}
	intersection_free(xs_head);

	free_object(sphere);
}

// Pipe the output to some output file and use some .ppm viewer to see the image
// E.g. ./miniRT > output.ppm
void	render_chapter_5_scene(t_app *app)
{
	t_point	ray_origin = point(0, 0, -5);
	double	wall_z = 10;
	double	wall_size = 7.0;
	int		canvas_pixels = 100;
	double	pixel_size = wall_size / canvas_pixels;
	double	half = wall_size / 2;

	t_object	*shape = sphere_new_args(point(0, 0, 0), 1, color255(0, 255, 0));

	printf("P3\n%d %d\n255\n", canvas_pixels, canvas_pixels);

	for (int y = 0; y < canvas_pixels; y++)
	{
		double	world_y = half - pixel_size * y;
		for (int x = 0; x < canvas_pixels; x++)
		{
			double	world_x = -half + pixel_size * x;
			t_point	position = point(world_x, world_y, wall_z);
			t_vector	direction = normalize(tuple_subtract(position, ray_origin));
			t_ray	r = ray(ray_origin, direction);
			t_intersection	*xs = intersect(shape, r);
			t_intersection	*hit = intersection_hit(xs);
			if (hit != NULL)
			{
				if (pixel_fits_image(x, y, app))
					mlx_put_pixel(app->img, x, y, color_hex_from_color(shape->material.color));
				printf("255 0 0 ");
			}
			else
			{
				if (pixel_fits_image(x, y, app))
					mlx_put_pixel(app->img, x, y, 0);

			}
				printf("0 0 0 ");
			intersection_free(xs);
		}
		printf("\n");
	}
	free_object(shape);
}
*/
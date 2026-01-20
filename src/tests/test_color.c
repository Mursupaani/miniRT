/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:31:13 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/12 11:05:41 by juhana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	test1()
{
	t_color			intensity;
	t_point			position;
	t_light	*light;

	printf("TEST 1:\n");
	printf("Scenario: A point light has a position and intensity\n\
Given intensity ← color(1, 1, 1)\n\
And position ← point(0, 0, 0)\n\
When light ← point_light(position, intensity)\n\
Then light.position = position\n\
And light.intensity = intensity\n");
	intensity = color(1, 1, 1);
	position = point(0, 0, 0);
	light = point_light(position, intensity);
	print_point_light(light);
	free(light);
}

static void	test2()
{
	t_color		c;
	t_material	m;

	printf("TEST 1:\n");
	printf("Scenario: The default material\n\
Given m ← material()\n\
Then m.color = color(1, 1, 1)\n\
And m.ambient = 0.1\n\
And m.diffuse = 0.9\n\
And m.specular = 0.9\n\
And m.shininess = 200.0\n");
	c = color(1, 1, 1);
	m = material();
	m.color = c;
	print_material(m);
}

static void	test3()
{
	t_object	*sphere;

	printf("TEST 3:\n");
	printf("Scenario: A sphere has a default material\n\
Given s ← sphere()\n\
When m ← s.material\n\
Then m = material()\n");
	sphere = sphere_new_args((point(0, 0, 0)), 1, color255(1, 1, 1));
	print_material(sphere->material);
	free(sphere);
}

static void	test4()
{
	t_object	*s;
	t_material	m;

	printf("TEST 4:\n");
	printf("Scenario: A sphere may be assigned a material\n\
Given s ← sphere()\n\
And m ← material()\n\
And m.ambient ← 1\n\
When s.material ← m\n\
Then s.material = m\n");
	s = sphere_new_args((point(0, 0, 0)), 1, color255(1, 1, 1));
	m = material();
	m.ambient = 1;
	s->material = m;
	print_material(s->material);
	free(s);
}

static void	test5()
{
	t_vector	eyev;
	t_light		*light;
	t_color		result;
	t_object	*sphere;

	printf("TEST 5:\n");
	printf("Scenario: Lighting with the eye between the light and the surface\n\
Given eyev ← vector(0, 0, -1)\n\
And normalv ← vector(0, 0, -1)\n\
And light ← point_light(point(0, 0, -10), color(1, 1, 1))\n\
When result ← lighting(m, light, position, eyev, normalv)\n\
Then result = color(1.9, 1.9, 1.9)\n");
	eyev = vector(0, 0, -1);
	light = point_light(point(0, 0, -10), color(1, 1, 1));
	sphere = sphere_new_args(point(0, 0, 1), 1, (t_color255){255,255,255});
	printf("--------------------\n");
	printf("EYEV:\n");
	print_tuple(eyev);
	printf("--------------------\n");
	printf("NORMALV:\n");
	print_tuple(normal_at(sphere, point(0, 0, 0)));
	result = lighting_old(sphere, light, point(0, 0, 0), eyev);
	print_color(result);
	free(sphere);
	free(light);
}

static void	test6()
{
	t_vector	eyev;
	t_light		*light;
	t_color		result;
	t_object	*sphere;

	printf("TEST 6:\n");
	printf("Scenario: Lighting with the eye between light and surface, eye offset 45°\n\
Given eyev ← vector(0, √2/2, -√2/2)\n\
And normalv ← vector(0, 0, -1)\n\
And light ← point_light(point(0, 0, -10), color(1, 1, 1))\n\
When result ← lighting(m, light, position, eyev, normalv)\n\
Then result = color(1.0, 1.0, 1.0)\n");
	eyev = vector(0, sqrt(2) / 2, -sqrt(2) / 2);
	light = point_light(point(0, 0, -10), color(1, 1, 1));
	sphere = sphere_new_args(point(0, 0, 1), 1, (t_color255){255,255,255});
	printf("--------------------\n");
	printf("EYEV:\n");
	print_tuple(eyev);
	printf("--------------------\n");
	printf("NORMALV:\n");
	print_tuple(normal_at(sphere, point(0, 0, 0)));
	result = lighting_old(sphere, light, point(0, 0, 0), eyev);
	print_color(result);
	free(sphere);
	free(light);
}

static void	test7()
{
	t_vector	eyev;
	t_light		*light;
	t_color		result;
	t_object	*sphere;

	printf("TEST 7:\n");
	printf("Scenario: Lighting with eye opposite surface, light offset 45°\n\
Given eyev ← vector(0, 0, -1)\n\
And normalv ← vector(0, 0, -1)\n\
And light ← point_light(point(0, 10, -10), color(1, 1, 1))\n\
When result ← lighting(m, light, position, eyev, normalv)\n\
Then result = color(0.7364, 0.7364, 0.7364)\n");
	eyev = vector(0, 0, -1);
	light = point_light(point(0, 10, -10), color(1, 1, 1));
	sphere = sphere_new_args(point(0, 0, 1), 1, (t_color255){255,255,255});
	printf("--------------------\n");
	printf("EYEV:\n");
	print_tuple(eyev);
	printf("--------------------\n");
	printf("NORMALV:\n");
	print_tuple(normal_at(sphere, point(0, 0, 0)));
	result = lighting_old(sphere, light, point(0, 0, 0), eyev);
	print_color(result);
	free(sphere);
	free(light);
}

static void	test8()
{
	t_vector	eyev;
	t_light		*light;
	t_color		result;
	t_object	*sphere;

	printf("TEST 8:\n");
	printf("Scenario: Lighting with eye in the path of the reflection vector\n\
Given eyev ← vector(0, -√2/2, -√2/2)\n\
And normalv ← vector(0, 0, -1)\n\
And light ← point_light(point(0, 10, -10), color(1, 1, 1))\n\
When result ← lighting(m, light, position, eyev, normalv)\n\
Then result = color(1.6364, 1.6364, 1.6364)\n");
	eyev = vector(0, -sqrt(2) / 2, -sqrt(2) / 2);
	light = point_light(point(0, 10, -10), color(1, 1, 1));
	sphere = sphere_new_args(point(0, 0, 1), 1, (t_color255){255,255,255});
	printf("--------------------\n");
	printf("EYEV:\n");
	print_tuple(eyev);
	printf("--------------------\n");
	printf("NORMALV:\n");
	print_tuple(normal_at(sphere, point(0, 0, 0)));
	result = lighting_old(sphere, light, point(0, 0, 0), eyev);
	print_color(result);
	free(sphere);
	free(light);
}

static void	test9()
{
	t_vector	eyev;
	t_light		*light;
	t_color		result;
	t_object	*sphere;

	printf("TEST 9:\n");
	printf("Scenario: Lighting with the light behind the surface\n\
Given eyev ← vector(0, 0, -1)\n\
And normalv ← vector(0, 0, -1)\n\
And light ← point_light(point(0, 0, 10), color(1, 1, 1))\n\
When result ← lighting(m, light, position, eyev, normalv)\n\
Then result = color(0.1, 0.1, 0.1)\n");
	eyev = vector(0, 0, -1);
	light = point_light(point(0, 0, 10), color(1, 1, 1));
	sphere = sphere_new_args(point(0, 0, 1), 1, (t_color255){255,255,255});
	result = lighting_old(sphere, light, point(0, 0, 0), eyev);
	print_color(result);
}

static void	test10()
{
	t_vector	eyev;
	t_light		*light;
	t_color		result;
	t_object	*sphere;

	printf("TEST 10\n");
	printf("Scenario: Lighting with the surface in shadow\n\
Given eyev ← vector(0, 0, -1)\n\
And normalv ← vector(0, 0, -1)\n\
And light ← point_light(point(0, 0, -10), color(1, 1, 1))\n\
When result ← lighting(m, light, position, eyev, normalv, in_shadow)\n\
Then result = color(0.1, 0.1, 0.1)\n");
	eyev = vector(0, 0, -1);
	light = point_light(point(0, 0, 10), color(1, 1, 1));
	sphere = sphere_new_args(point(0, 0, 1), 1, (t_color255){255,255,255});
	// light->in_shadow = true;
	result = lighting_old(sphere, light, point(0, 0, 0), eyev);
	print_color(result);
}

void	render_chapter_7_scene(t_app *app)
{
	t_point		ray_origin = point(0, 0, -5);
	double		wall_z = 10;
	double		wall_size = 7.0;
	int			canvas_pixels = 540;
	double		pixel_size = wall_size / canvas_pixels;
	double		half = wall_size / 2;
	t_object	*sphere = sphere_new_args(point(0, 0, 0), 1, color255(0, 255, 0));
	t_light		*light = point_light(point(-10, 10, -10), color(1, 1, 1));
	sphere->material.color = color(1, 0.5, 1);
	// print_material(sphere->material);

	// printf("P3\n%d %d\n255\n", canvas_pixels, canvas_pixels);
	for (int y = 0; y < canvas_pixels; y++)
	{
		double	world_y = half - pixel_size * y;
		for (int x = 0; x < canvas_pixels; x++)
		{
			double	world_x = -half + pixel_size * x;
			t_point	position = point(world_x, world_y, wall_z);
			t_vector	direction = normalize(tuple_subtract(position, ray_origin));
			t_ray	r = ray(ray_origin, direction);
			t_intersections	*xs = intersect(sphere, r, NULL);
			if (xs && xs->count > 0)
			{
				// Inside the x/y loop in render_chapter_7_scene
				t_point	point = ray_position(r, xs->arr[0].t);
				t_vector eye = tuple_negate(r.direction);
				if (pixel_fits_image(x, y, app))
					mlx_put_pixel(app->img, x, y, color_hex_from_color(lighting_old(xs->arr->object, light, point, eye)));
				free(xs->arr);
				free(xs);
			}
			else
			{
				if (pixel_fits_image(x, y, app))
					mlx_put_pixel(app->img, x, y, 0);

			}
		}
	}
	free_object(sphere);
}

void	test_color()
{
	printf("\n");
	printf("---------------- TESTING COLOR --------------\n");
	printf("_____________________________________________\n");
	test1();
	printf("_____________________________________________\n");
	test2();
	printf("_____________________________________________\n");
	test3();
	printf("_____________________________________________\n");
	test4();
	printf("_____________________________________________\n");
	test5();
	printf("_____________________________________________\n");
	test6();
	printf("_____________________________________________\n");
	test7();
	printf("_____________________________________________\n");
	test8();
	printf("_____________________________________________\n");
	test9();
	printf("_____________________________________________\n");
	test10();
	printf("_____________________________________________\n");
	printf("---------- TESTING COLOR FINISHED -----------\n");
	printf("\n");
}

// void	render_chapter_7_scene(t_app *app)
// {
// 	t_point		ray_origin = point(0, 0, -5);
// 	double		wall_z = 10;
// 	double		wall_size = 7.0;
// 	int			canvas_pixels = 2048;
// 	double		pixel_size = wall_size / canvas_pixels;
// 	double		half = wall_size / 2;
// 	t_object	*sphere = sphere_new_args(point(0, 0, 0), 1, color255(0, 255, 0));
// 	t_light		*light = point_light(point(-10, 10, -10), color(1, 1, 1));
// 	sphere->material.color = color(1, 0.5, 1);
// 	print_material(sphere->material);
//
// 	printf("P3\n%d %d\n255\n", canvas_pixels, canvas_pixels);
// 	for (int y = 0; y < canvas_pixels; y++)
// 	{
// 		double	world_y = half - pixel_size * y;
// 		for (int x = 0; x < canvas_pixels; x++)
// 		{
// 			double	world_x = -half + pixel_size * x;
// 			t_point	position = point(world_x, world_y, wall_z);
// 			t_vector	direction = vector_normalize(tuple_subtract(position, ray_origin));
// 			t_ray	r = ray(ray_origin, direction);
// 			t_intersection	*xs = intersect_sphere(sphere, r);
// 			t_intersection	*hit = intersection_hit(xs);
// 			if (hit != NULL)
// 			{
// // Inside the x/y loop in render_chapter_7_scene
// 				t_point	point = ray_position(r, hit->t);
// 				t_vector eye = tuple_negate(r.direction);
// 				if (pixel_fits_image(x, y, app))
// 					mlx_put_pixel(app->img, x, y, color_hex_from_color(lighting(hit->object, light, point, eye)));
// 			}
// 			else
// 			{
// 				if (pixel_fits_image(x, y, app))
// 					mlx_put_pixel(app->img, x, y, 0);
//
// 			}
// 			intersection_free(xs);
// 		}
// 	}
// 	free_object(sphere);
// }
//
// void	test_color()
// {
// 	printf("\n");
// 	printf("---------------- TESTING COLOR --------------\n");
// 	printf("_____________________________________________\n");
// 	test1();
// 	printf("_____________________________________________\n");
// 	test2();
// 	printf("_____________________________________________\n");
// 	test3();
// 	printf("_____________________________________________\n");
// 	test4();
// 	printf("_____________________________________________\n");
// 	test5();
// 	printf("_____________________________________________\n");
// 	test6();
// 	printf("_____________________________________________\n");
// 	test7();
// 	printf("_____________________________________________\n");
// 	test8();
// 	printf("_____________________________________________\n");
// 	test9();
// 	printf("_____________________________________________\n");
// 	printf("---------- TESTING COLOR FINISHED -----------\n");
// 	printf("\n");
// }

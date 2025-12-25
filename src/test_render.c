/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 12:04:16 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/23 12:04:18 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	build_test_render(t_app *app)
{
	t_camera	*c;
	t_world		*w;

	w = world();
	w->light = point_light(point(-20, 10, -20), color(1, 1, 1));
	c = camera(app->img->width, app->img->height, M_PI / 3);
	t_matrix4 c_trans = view_transform(point(0, 3, -7), point(0, 2, 0), vector(0, 1, 0));
	set_camera_transform(c, c_trans);

	t_object *base = cone_new();
	base->minimum = -1;
	base->maximum = 0;
	base->material.color = color(0.1, 0.1, 0.1);
	base->material.transparency = 0.9;
	base->material.reflective = 0.9;
	base->material.refractive_index = 1.5;
	add_transform(base, scaling_matrix4(1, 0.2, 1));
	add_transform(base, translation_matrix4(0, 0.2, 0));
	add_object_to_world(base, w);

	t_object *stem = cylinder_new();
	stem->minimum = 0.2;
	stem->maximum = 1.35;
	stem->material.color = color(0.1, 0.1, 0.1);
	stem->material.transparency = 0.9;
	stem->material.reflective = 0.9;
	stem->material.refractive_index = 1.5;
	add_transform(stem, scaling_matrix4(0.1, 1, 0.1));
	add_object_to_world(stem, w);

	t_object *glass = cone_new();
	glass->minimum = 2;
	glass->maximum = 3;
	glass->closed = true;
	glass->material.color = color(0.1, 0.1, 0.1);
	glass->material.transparency = 0.9;
	glass->material.reflective = 0.9;
	glass->material.refractive_index = 1.5;
	add_transform(glass, scaling_matrix4(0.5, 0.5, 0.5));
	add_transform(glass, translation_matrix4(0, 1.2, 0));
	add_object_to_world(glass, w);

	t_object *liquid = cone_new();
	liquid->minimum = 0.2;
	liquid->maximum = 2;
	liquid->closed = true;
	liquid->material.color = color(0.1, 0.1, 0.1);
	liquid->material.transparency = 1;
	liquid->material.reflective = 0.9;
	liquid->material.refractive_index = 1.33;
	add_transform(liquid, scaling_matrix4(0.5, 0.5, 0.5));
	add_transform(liquid, translation_matrix4(0, 1.2, 0));
	add_object_to_world(liquid, w);

	t_object *olive = sphere_new();
	olive->material.color = color(0.1, 0.6, 0.2);
	olive->material.reflective = 0.3;
	add_transform(olive, scaling_matrix4(0.2, 0.3, 0.2));
	add_transform(olive, rotation_z(M_PI / 3));
	add_transform(olive, translation_matrix4(0, 2.1, 0));
	add_object_to_world(olive, w);

	t_object *stick = cylinder_new();
	stick->minimum = 0;
	stick->maximum = 2;
	stick->material.color = color(0.6, 0.5, 0.4);
	add_transform(stick, scaling_matrix4(0.01, 1, 0.01));
	add_transform(stick, rotation_z(-M_PI / 3));
	add_transform(stick, translation_matrix4(0, 2.1, 0));
	add_object_to_world(stick, w);

	t_object *cube = cube_new();
	cube->material.color = color(0.5, 0.5, 0.5);
	cube->material.diffuse = 0.1;
	cube->material.specular = 0.3;
	cube->material.reflective = 0.9;
	cube->material.transparency = 0.9;
	cube->material.refractive_index = 1.40;
	add_transform(cube, scaling_matrix4(0.3, 0.3, 0.3));
	add_transform(cube, rotation_y(M_PI / 4));
	add_transform(cube, translation_matrix4(-2, 0.5, -0.5));
	add_object_to_world(cube, w);

	t_object *floor = plane_new();
	t_matrix4 m = scaling_matrix4(10, 0.01, 10);
	floor->material.color = color(0.1, 0.1, 0.1);
	floor->material.specular = 0.3;
	floor->material.reflective = 1;
	set_transform(floor, m);
	add_object_to_world(floor, w);

	t_object *back_wall = plane_new();
	m = rotation_x(M_PI / 2);
	m = matrix4_multiply(translation_matrix4(0, 0, 8), m);
	set_transform(back_wall, m);
	back_wall->material.color = color(0.33, 0.29, 0);
	back_wall->material.diffuse = 0.7;
	back_wall->material.specular = 0.3;
	back_wall->material.reflective = 1;
	// back_wall->material.pattern = ring_pattern(color(1, 1, 1), color(0.33, 0.29, 0));
	// set_pattern_transform(&back_wall->material.pattern, scaling_matrix4(7, 7, 7));
	add_object_to_world(back_wall, w);

	t_object *ring = sphere_new();
	ring->material.color = color(1, 1, 1);
	ring->material.reflective = 0.8;
	set_transform(ring, scaling_matrix4(7, 0.1, 7));
	add_transform(ring, rotation_x(M_PI / 2));
	add_transform(ring, translation_matrix4(0, 0, 7));
	add_object_to_world(ring, w);

	app->scene = w;
	app->scene->camera = c;
}

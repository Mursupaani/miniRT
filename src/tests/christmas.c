/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   christmas.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 12:04:16 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/07 14:13:59 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	christmas_tree(t_app *app)
{
	t_camera	*c;
	t_world		*w;
	t_matrix4	m;
	t_pattern	p;

	w = world();
	w->light = point_light(point(-20, 10, -20), color(1, 1, 1));
	c = camera(app->img->width, app->img->height, M_PI / 3);
	t_matrix4 c_trans = view_transform(point(0, 3, -7), point(0, 2, 0), vector(0, 1, 0), c);
	set_camera_transform(c, c_trans);

	p = gradient_pattern(color(0.1, 0.5, 0.1), color(0.4, 0.8, 0.2));
	add_pattern_transform(&p, scaling_matrix4(1, 0.3, 1));

	t_object *star1 = cube_new();
	star1->material.color = color(0.66, 0.58, 0);
	star1->material.transparency = 0.5;
	star1->material.reflective = 0.9;
	star1->material.refractive_index = 1.5;
	add_transform(star1, rotation_x(M_PI / 2));
	add_transform(star1, rotation_z(M_PI / 4));
	add_transform(star1, scaling_matrix4(0.2, 0.2, 0.015));
	add_transform(star1, translation_matrix4(0, 3.75, 0));
	add_object_to_world(star1, w);

	t_object *star0 = cube_new();
	star0->material.color = color(0.66, 0.58, 0);
	star0->material.transparency = 0.5;
	star0->material.reflective = 0.9;
	star0->material.refractive_index = 1.5;
	add_transform(star0, rotation_x(M_PI / 2));
	add_transform(star0, scaling_matrix4(0.2, 0.2, 0.01));
	add_transform(star0, translation_matrix4(0, 3.75, 0));
	add_object_to_world(star0, w);

	t_object *layer4 = cone_new();
	layer4->minimum = -0.5;
	layer4->maximum = 0;
	layer4->closed = true;
	layer4->material.color = color(0.1, 0.5, 0.1);
	layer4->material.transparency = 0.5;
	layer4->material.reflective = 0.9;
	layer4->material.refractive_index = 1.5;
	layer4->material.pattern = p;
	add_transform(layer4, scaling_matrix4(0.6, 1, 0.6));
	add_transform(layer4, translation_matrix4(0, 3.5, 0));
	add_object_to_world(layer4, w);

	t_object *layer3 = cone_new();
	layer3->minimum = -0.75;
	layer3->maximum = -0.25;
	layer3->closed = true;
	layer3->material.color = color(0.1, 0.5, 0.1);
	layer3->material.transparency = 0.5;
	layer3->material.reflective = 0.9;
	layer3->material.refractive_index = 1.5;
	layer3->material.pattern = p;
	add_transform(layer3, scaling_matrix4(0.6, 1, 0.6));
	add_transform(layer3, translation_matrix4(0, 3.25, 0));
	add_object_to_world(layer3, w);

	t_object *layer2 = cone_new();
	layer2->minimum = -1;
	layer2->maximum = -0.5;
	layer2->closed = true;
	layer2->material.color = color(0.1, 0.5, 0.1);
	layer2->material.transparency = 0.5;
	layer2->material.reflective = 0.9;
	layer2->material.refractive_index = 1.5;
	layer2->material.pattern = p;
	add_transform(layer2, scaling_matrix4(0.6, 1, 0.6));
	add_transform(layer2, translation_matrix4(0, 3, 0));
	add_object_to_world(layer2, w);

	t_object *layer1 = cone_new();
	layer1->minimum = -1.25;
	layer1->maximum = -0.75;
	layer1->closed = true;
	layer1->material.color = color(0.1, 0.5, 0.1);
	layer1->material.transparency = 0.5;
	layer1->material.reflective = 0.9;
	layer1->material.refractive_index = 1.5;
	p = ring_pattern(color(0.1, 0.5, 0.1), color(0.4, 0.8, 0.2));
	add_pattern_transform(&p, scaling_matrix4(1, 0.3, 1));
	layer1->material.pattern = p;
	add_transform(layer1, scaling_matrix4(0.6, 1, 0.6));
	add_transform(layer1, translation_matrix4(0, 2.75, 0));
	add_object_to_world(layer1, w);

	t_object *layer0 = cone_new();
	layer0->minimum = -1.5;
	layer0->maximum = -1;
	layer0->closed = true;
	layer0->material.color = color(0.1, 0.5, 0.1);
	layer0->material.transparency = 0.5;
	layer0->material.reflective = 0.9;
	layer0->material.refractive_index = 1.5;
	layer0->material.pattern = p;
	add_transform(layer0, scaling_matrix4(0.6, 1, 0.6));
	add_transform(layer0, translation_matrix4(0, 2.5, 0));
	add_object_to_world(layer0, w);

	t_object *stem = cylinder_new();
	stem->minimum = 0;
	stem->maximum = 1.35;
	stem->closed = true;
	stem->material.color = color(0.4, 0.3, 0.2);
	stem->material.transparency = 0.5;
	stem->material.reflective = 0.9;
	stem->material.refractive_index = 2;
	add_transform(stem, scaling_matrix4(0.2, 1, 0.2));
	add_object_to_world(stem, w);

	t_object *present = cube_new();
	p = checkers_pattern(color(0.8, 0.2, 0.3), color(0.2, 0.1, 0.8));
	set_pattern_transform(&p, scaling_matrix4(0.3, 0.3, 0.3));
	present->material.pattern = p;
	present->material.reflective = 0.2;
	add_transform(present, scaling_matrix4(0.33, 0.33, 0.33));
	add_transform(present, rotation_y(M_PI / 3));
	add_transform(present, translation_matrix4(-1, 0.5, 1));
	add_object_to_world(present, w);

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

	t_object *floor = plane_new();
	// m = rotation_x(M_PI / 2);
	// m = matrix4_multiply(translation_matrix4(0, 0, 8), m);
	// set_transform(floor, m);
	floor->material.color = color(0.33, 0.29, 0);
	floor->material.diffuse = 0.7;
	// floor->material.specular = 0.3;
	// floor->material.reflective = 1;
	// back_wall->material.pattern = ring_pattern(color(1, 1, 1), color(0.33, 0.29, 0));
	// set_pattern_transform(&back_wall->material.pattern, scaling_matrix4(7, 7, 7));
	add_object_to_world(floor, w);

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

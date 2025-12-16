/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_render_chapter7.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 13:56:21 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/16 17:48:40 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	build_chapter7_world(t_app *app)
{
	t_camera	*c;
	t_world		*w;

	w = world();
	w->light = point_light(point(-20, 10, -20), color(1, 1, 1));
	c = camera(app->img->width, app->img->height, M_PI / 3);
	c->transform = view_transform(point(-2, 1.5, -7), point(0, 1, 0), vector(0, 1, 0));

	t_object *floor = sphere_new();
	t_matrix4 m = scaling_matrix4(10, 0.01, 10);
	floor->material.color = color(1, 0.9, 0.9);
	floor->material.specular = 0;
	set_transform(floor, m);
	world_add_object(w, floor);

    // --- LEFT WALL ---
    t_object *left_wall = sphere_new();
    m = scaling_matrix4(10, 0.01, 10);
    m = matrix4_multiply(rotation_x(M_PI / 2), m); 
    m = matrix4_multiply(rotation_y(-M_PI / 4), m); 
    m = matrix4_multiply(translation_matrix4(0, 0, 5), m);
	set_transform(left_wall, m);
    left_wall->material = floor->material;
	left_wall->material.pattern = stripe_pattern(color(1, 1, 1), color(1, 0, 0));
	set_pattern_transform(&left_wall->material.pattern, scaling_matrix4(0.1, 0.1, 0.1));
	add_pattern_transform(&left_wall->material.pattern, rotation_z(M_PI / 2.5));
    world_add_object(w, left_wall);

    // --- RIGHT WALL ---
    t_object *right_wall = sphere_new();
    m = scaling_matrix4(10, 0.01, 10);
    m = matrix4_multiply(rotation_x(M_PI / 2), m);
    m = matrix4_multiply(rotation_y(M_PI / 4), m);
    m = matrix4_multiply(translation_matrix4(0, 0, 5), m);
	set_transform(right_wall, m);
    right_wall->material = floor->material;
	right_wall->material.pattern = stripe_pattern(color(1, 1, 1), color(1, 0, 0));
    world_add_object(w, right_wall);

	// MIDDLE SPHERE
	t_object *middle = sphere_new();
	m = translation_matrix4(-0.5, 1, 0.5);
	middle->material.color = color(0.1, 1, 0.5);
	middle->material.diffuse = 0.7;
	middle->material.specular = 0.3;
	middle->material.pattern = gradient_pattern(color(1, 0, 0), color(0, 0, 1));
	set_transform(middle, m);
	set_pattern_transform(&middle->material.pattern, scaling_matrix4(1, 1, 1));
	world_add_object(w, middle);

	t_object *right = sphere_new();
	m = matrix4_multiply(translation_matrix4(1.5, 0.5, -0.5), scaling_matrix4(0.5, 0.5, 0.5));
	right->material.color = color(0.5, 1, 0.1);
	right->material.diffuse = 0.7;
	right->material.specular = 0.3;
	set_transform(right, m);
	right->material.pattern = stripe_pattern(color(1, 1, 1), color(1, 0, 0));
	set_pattern_transform(&right->material.pattern, rotation_z(M_PI / 5));
	add_pattern_transform(&right->material.pattern, scaling_matrix4(0.1, 0.1, 0.1));
	add_pattern_transform(&right->material.pattern, rotation_z(M_PI / 3));
	world_add_object(w, right);
	app->scene = w;
	app->scene->camera = c;

	t_object *left = sphere_new();
	m = matrix4_multiply(translation_matrix4(-1.5, 0.33, -0.75), scaling_matrix4(0.33, 0.33, 0.33));
	left->material.color = color(1, 0.8, 0.1);
	left->material.diffuse = 0.7;
	left->material.specular = 0.3;
	set_transform(left, m);
	left->material.pattern = test_pattern();
	// set_pattern_transform(&left->material.pattern, translation_matrix4(0.5, 1, 1.5));
	world_add_object(w, left);
	app->scene = w;
	app->scene->camera = c;

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_render_chapter7.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 13:56:21 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/21 15:28:12 by anpollan         ###   ########.fr       */
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
	t_matrix4 c_trans = view_transform(point(0, 1.5, -7), point(0, 1, 0), vector(0, 1, 0));
	set_camera_transform(c, c_trans);

	t_object *floor = plane_new();
	t_matrix4 m = scaling_matrix4(10, 0.01, 10);
	floor->material.color = color(0.1, 0.1, 0.1);
	floor->material.specular = 0.1;
	floor->material.reflective = 0.5;
	set_transform(floor, m);
	add_object_to_world(floor, w);

	// MIDDLE 
	// t_object *cylinder = cylinder_new();
	// cylinder->closed = true;
	// cylinder->minimum = 0;
	// cylinder->maximum = 1;
	// cylinder->material.color = color(1, 0.5, 0.5);
	// cylinder->material.diffuse = 0.1;
	// cylinder->material.specular = 0.3;
	// cylinder->material.reflective = 0.1;
	// cylinder->material.transparency = 0.9;
	// cylinder->material.refractive_index = 1.5;
	// add_object_to_world(cylinder, w);

	t_object *cone = cone_new();
	cone->maximum = 0;
	cone->minimum = -1;
	cone->material.reflective = 0.5;
	// cone->material.transparency = 0.5;
	// cone->material.refractive_index = 1.5;
	set_transform(cone, translation_matrix4(0, 1, 0));
	add_object_to_world(cone, w);

	// t_object *cube = cube_new();
	// cube->material.color = color(0.5, 0.5, 0.5);
	// cube->material.diffuse = 0.1;
	// cube->material.specular = 0.3;
	// cube->material.reflective = 0.9;
	// cube->material.transparency = 0.9;
	// cube->material.refractive_index = 1.2;
	// // m = translation_matrix4(-10, 5, 0.5);
	// m = rotation_x(M_PI / 4);
	// // m = rotation_y(M_PI / 4);
	// set_transform(cube, m);
	// // m = rotation_x(M_PI / 4);
	// // set_transform(cube, m);
	// add_object_to_world(cube, w);
	//
	// t_object *middle = glass_sphere();
	// middle->material.color = color(0.5, 0.5, 0.5);
	// middle->material.diffuse = 0.1;
	// middle->material.specular = 0.3;
	// middle->material.reflective = 0.9;
	// middle->material.transparency = 0.9;
	// // m = translation_matrix4(-0.5, 1, 0.5);
	// // set_transform(middle, m);
	// add_object_to_world(middle, w);
	//
	// t_object *middle_inner = glass_sphere();
	// middle_inner->material.color = color(0, 0, 0);
	// middle_inner->material.diffuse = 0;
	// middle_inner->material.specular = 0;
	// middle_inner->material.reflective = 0;
	// middle_inner->material.transparency = 1;
	// middle_inner->material.refractive_index = 1;
	// set_transform(middle_inner, scaling_matrix4(0.8, 0.8, 0.8));
	// // m = translation_matrix4(-0.5, 1, 0.5);
	// // add_transform(middle_inner, m);
	// // middle->material.pattern = gradient_pattern(color(1, 0, 0), color(0, 0, 1));
	// // set_pattern_transform(&middle->material.pattern, scaling_matrix4(1, 1, 1));
	// add_object_to_world(middle_inner, w);

	t_object *right = sphere_new();
	m = scaling_matrix4(0.5, 0.5, 0.5);
	right->material.color = color(0.5, 1, 0.1);
	right->material.diffuse = 0.7;
	right->material.specular = 0.3;
	right->material.reflective = 1;
	set_transform(right, m);
	// add_transform(right, translation_matrix4(-0.5, 1, 0.5));
	right->material.pattern = stripe_pattern(color(1, 1, 1), color(1, 0, 0));
	set_pattern_transform(&right->material.pattern, rotation_z(M_PI / 5));
	add_pattern_transform(&right->material.pattern, scaling_matrix4(0.1, 0.1, 0.1));
	add_pattern_transform(&right->material.pattern, rotation_z(M_PI / 3));
	add_object_to_world(right, w);

	t_object *left = sphere_new();
	m = matrix4_multiply(translation_matrix4(-2.5, 0.33, -1.25), scaling_matrix4(0.33, 0.33, 0.33));
	left->material.color = color(1, 0.8, 0.1);
	left->material.diffuse = 0.7;
	left->material.specular = 0.3;
	left->material.reflective = 0.5;
	set_transform(left, m);
	left->material.pattern = test_pattern();
	set_pattern_transform(&left->material.pattern, rotation_z(M_PI / 2));
	add_pattern_transform(&left->material.pattern, scaling_matrix4(1.5, 1.5, 1.5));
	add_object_to_world(left, w);

	t_object *up_right = sphere_new();
	m = matrix4_multiply(translation_matrix4(2, 2, -2), scaling_matrix4(0.5, 0.5, 0.5));
	up_right->material.color = color(1, 0.8, 0.1);
	up_right->material.diffuse = 0.7;
	up_right->material.specular = 0.3;
	up_right->material.reflective = 0.1;
	set_transform(up_right, rotation_y(M_PI / 4));
	add_transform(up_right, m);
	up_right->material.pattern = ring_pattern(color(0.5, 0.1, 0.8), color(0, 0, 0));
	set_pattern_transform(&up_right->material.pattern, rotation_x(M_PI / 2));
	add_pattern_transform(&up_right->material.pattern, scaling_matrix4(0.2, 0.2, 0.2));
	add_object_to_world(up_right, w);

	t_object *up_left = sphere_new();
	m = matrix4_multiply(translation_matrix4(-2, 2, -2), scaling_matrix4(0.5, 0.5, 0.5));
	up_left->material.color = color(1, 0.8, 0.1);
	up_left->material.diffuse = 0.7;
	up_left->material.specular = 0.3;
	up_left->material.reflective = 0.7;
	set_transform(up_left, rotation_y(M_PI / 2));
	add_transform(up_left, m);
	up_left->material.pattern = checkers_pattern(color(0.2, 0.7, 0.5), color(0, 0, 0));
	set_pattern_transform(&up_left->material.pattern, rotation_y(M_PI / 4));
	add_pattern_transform(&up_left->material.pattern, scaling_matrix4(0.3, 0.3, 0.3));
	add_object_to_world(up_left, w);

	// BACK WALL - A plane behind the scene
	t_object *back_wall = plane_new();
	m = rotation_x(M_PI / 2);
	m = matrix4_multiply(translation_matrix4(0, 0, 8), m);
	set_transform(back_wall, m);
	back_wall->material.color = color(0.8, 0.8, 0.9);
	back_wall->material.diffuse = 0.7;
	back_wall->material.specular = 0.1;
	back_wall->material.reflective = 0.2;
	back_wall->material.pattern = checkers_pattern(color(0.5, 0.5, 0.5), color(0.1, 0.1, 0.1));
	set_pattern_transform(&back_wall->material.pattern, scaling_matrix4(0.5, 0.5, 0.5));
	add_object_to_world(back_wall, w);

	app->scene = w;
	app->scene->camera = c;
}

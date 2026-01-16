/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 12:04:16 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/15 16:10:37 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	build_test_render(t_app *app)
{
	t_camera	*c;
	t_world		*w;

	w = world();
	w->light = point_light(point(-20, 10, -20), color(0, 1, 1));
	w->light->ambient_color = color (1, 0, 0);
	w->light->ambient_ratio = 0.1;
	c = camera(app->img->width, app->img->height, M_PI / 3);
	t_matrix4 c_trans = view_transform(point(0, 3, -11), point(0, 3, 0), vector(0, 1, 0), c);
	init_camera_yaw_and_pitch(c);
	set_camera_transform(c, c_trans);

	mlx_texture_t *earth = mlx_load_png("./Textures/earthmap1k.png");
	mlx_texture_t *pattern = mlx_load_png("./Textures/pattern.png");
	// mlx_texture_t *space = mlx_load_png("./Textures/space.png");
	mlx_texture_t *space_sphere = mlx_load_png("./Textures/space_sphere.png");
	// mlx_texture_t *honey = mlx_load_png("./Textures/honey.png");
	mlx_texture_t *bump	 = mlx_load_png("./Textures/bump.png");
	mlx_texture_t *cube	 = mlx_load_png("./Textures/minecraft.png");
	mlx_texture_t *cube_bump = mlx_load_png("./Textures/minecraft_bump.png");
	// mlx_texture_t *cube	 = mlx_load_png("./Textures/stone.png");
	// mlx_texture_t *cube_bump = mlx_load_png("./Textures/stone_bump.png");
	// mlx_texture_t *cube	 = mlx_load_png("./Textures/cube2.png");
	// mlx_texture_t *cube_bump = mlx_load_png("./Textures/cube2_bump.png");


	t_object *cubenew = cube_new();
	ft_bzero(&cubenew->bump_map, sizeof(t_bump_map));
	cubenew->bump_map.has_bump_map = true;
	cubenew->bump_map.bump_map = cube_bump;
	cubenew->bump_map.uv_map = cubic_atlas_map;
	// cubenew->material.transparency = 0.5;
	// cubenew->material.refractive_index = 1.5;
	// cubenew->material.pattern = uv_align_cube_pattern();
	// mlx_texture_t *cube[6];
	// cube[UP] = mlx_load_png("./Textures/Storforsen4/posy.png");
	// cube[DOWN] = mlx_load_png("./Textures/Storforsen4/negy.png");
	// cube[LEFT] = mlx_load_png("./Textures/Storforsen4/negx.png");
	// cube[RIGHT] = mlx_load_png("./Textures/Storforsen4/posx.png");
	// cube[FRONT] = mlx_load_png("./Textures/Storforsen4/posz.png");
	// cube[BACK] = mlx_load_png("./Textures/Storforsen4/negz.png");
	// cubenew->material.pattern = uv_image_cube(cube);
	cubenew->material.pattern = uv_image(cube);
	cubenew->material.pattern = texture_map(cubenew->material.pattern, cubic_atlas_map);
	cubenew->material.reflective = 0.5;
	cubenew->material.transparency = 0.5;
	// cubenew->material.refractive_index = 1.5;
	add_transform(cubenew, rotation_x(-M_PI / 2));
	add_transform(cubenew, rotation_y(-M_PI / 5));
	add_transform(cubenew, rotation_z(M_PI));
	add_transform(cubenew, translation_matrix4(3, 2, 1));
	add_object_to_world(cubenew, w);

	t_object *sphere = sphere_new();
	// sphere->material.transparency = 0.5;
	// sphere->material.refractive_index = 1.5;
	sphere->material.pattern = uv_image(earth);
	sphere->material.pattern = texture_map(sphere->material.pattern, spherical_map);
	ft_bzero(&sphere->bump_map, sizeof(t_bump_map));
	sphere->bump_map.has_bump_map = true;
	sphere->material.reflective = 0.5;
	sphere->material.transparency = 1;
	sphere->material.refractive_index = 1.5;
	sphere->bump_map.bump_map = bump;
	sphere->bump_map.uv_map = spherical_map;
	add_transform(sphere, rotation_y(1.9));
	add_transform(sphere, translation_matrix4(-3, 2, 0));
	add_object_to_world(sphere, w);

	// t_object *sphere2 = sphere_new();
	// // sphere->material.transparency = 0.5;
	// // sphere->material.refractive_index = 1.5;
	// ft_bzero(&sphere2->bump_map, sizeof(t_bump_map));
	// sphere2->bump_map.has_bump_map = true;
	// sphere2->bump_map.bump_map = bump;
	// sphere2->bump_map.uv_map = spherical_map;
	// add_transform(sphere2, rotation_y(1.9));
	// add_transform(sphere2, translation_matrix4(-3, 2, -1));
	// add_object_to_world(sphere2, w);

	t_object *floor = plane_new();
	floor->material.color = color(1, 1, 1);
	floor->material.diffuse = 0.7;
	floor->material.specular = 0.3;
	// floor->material.transparency = 0.9;
	// floor->material.refractive_index = 1;
	// floor->material.reflective = 0.5;
	floor->material.pattern = texture_map(uv_image(pattern), planar_map);
	set_pattern_transform(&floor->material.pattern, scaling_matrix4(10, 10, 10));
	add_object_to_world(floor, w);

	t_object *sky_sphere = sphere_new();
	sky_sphere->material.pattern = texture_map(uv_image(space_sphere), spherical_map);
	sky_sphere->material.ambient = 1;
	sky_sphere->material.diffuse = 1;
	sky_sphere->material.specular = 0;
	add_transform(sky_sphere, rotation_y(-M_PI / 3));
	add_transform(sky_sphere, scaling_matrix4(5000, 5000, 5000));
	add_transform(sky_sphere, c->transform);
	add_object_to_world(sky_sphere, w);

	// t_object *cylinder = cylinder_new();
	// cylinder->material.pattern = texture_map(uv_image(honey), cylindrical_map);
	// set_transform(cylinder, scaling_matrix4(1, 3.1415, 1));
	// add_transform(cylinder, translation_matrix4(0, 0, 8));
	// add_object_to_world(cylinder, w);
	//
	// t_object *cone = cone_new();
	// cone->material.pattern = texture_map(uv_image(honey), cylindrical_map);
	// set_transform(cone, scaling_matrix4(1, 3.1415, 1));
	// add_transform(cone, translation_matrix4(0, 0, 8));
	// add_object_to_world(cone, w);

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
	glass->closed = false;
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
//
// 	t_object *cube = cube_new();
// 	cube->material.color = color(0.5, 0.5, 0.5);
// 	cube->material.diffuse = 0.1;
// 	cube->material.specular = 0.3;
// 	cube->material.reflective = 0.9;
// 	cube->material.transparency = 0.9;
// 	cube->material.refractive_index = 1.40;
// 	add_transform(cube, scaling_matrix4(0.3, 0.3, 0.3));
// 	add_transform(cube, rotation_y(M_PI / 4));
// 	add_transform(cube, translation_matrix4(-2, 0.5, -0.5));
// 	add_object_to_world(cube, w);
//
	// t_object *back_wall = plane_new();
	// m = rotation_x(M_PI / 2);
	// m = matrix4_multiply(translation_matrix4(0, 0, 8), m);
	// set_transform(back_wall, m);
	// back_wall->material.color = color(0.33, 0.29, 0);
	// back_wall->material.diffuse = 0.7;
	// back_wall->material.specular = 0.3;
	// back_wall->material.reflective = 0.5;
	// // back_wall->material.pattern = ring_pattern(color(1, 1, 1), color(0.33, 0.29, 0));
	// // set_pattern_transform(&back_wall->material.pattern, scaling_matrix4(7, 7, 7));
	// add_object_to_world(back_wall, w);
//
// 	t_object *ring = sphere_new();
// 	ring->material.color = color(1, 1, 1);
// 	ring->material.reflective = 0.8;
// 	set_transform(ring, scaling_matrix4(7, 0.1, 7));
// 	add_transform(ring, rotation_x(M_PI / 2));
// 	add_transform(ring, translation_matrix4(0, 0, 7));
// 	add_object_to_world(ring, w);
//
	app->scene = w;
	app->scene->camera = c;
	printf("fov: %lf\n", app->scene->camera->fov);
}

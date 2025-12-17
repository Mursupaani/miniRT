// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   test_world.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/12/09 15:38:13 by anpollan          #+#    #+#             */
// /*   Updated: 2025/12/12 14:07:45 by juhana           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */
//
// #include "minirt.h"
//
// static	void test1()
// {
// 	t_world	*w;
//
// 	printf("TEST 1:\n");
// 	printf("Scenario: The default world\n\
// Given light ← point_light(point(-10, 10, -10), color(1, 1, 1))\n\
// And s1 ← sphere() with:\n\
// | material.color\n\
// | (0.8, 1.0, 0.6)\n\
// | material.diffuse\n\
// | 0.7\n\
// | material.specular | 0.2\n\
// And s2 ← sphere() with:\n\
// | transform | scaling(0.5, 0.5, 0.5) |\n\
// When w ← default_world()\n\
// Then w.light = light\n\
// And w contains s1\n\
// And w contains s2\n");
// 	w = default_world();
// 	print_world(w);
// 	free_world(w);
// }
//
// static	void test2()
// {
// 	t_world			*w;
// 	t_ray			r;
// 	t_intersections	*xs;
//
// 	printf("TEST 2:\n");
// 	printf("Scenario: Intersect a world with a ray\n\
// Given w ← default_world()\n\
// And r ← ray(point(0, 0, -5), vector(0, 0, 1))\n\
// When xs ← intersect_world(w, r)Building a World • 93\n\
// Then xs.count = 4\n\
// And xs[0].t = 4\n\
// And xs[1].t = 4.5\n\
// And xs[2].t = 5.5\n\
// And xs[3].t = 6\n");
// 	w = default_world();
// 	r = ray(point(0, 0, -5), vector(0, 0, 1));
// 	xs = intersect_world(w, r);
// 	print_world(w);
// 	print_intersections(xs);
// 	free_intersections(xs);
// 	free_world(w);
// }
//
// static	void test3()
// {
// 	t_ray			r;
// 	t_object		*shape;
// 	t_intersection	i;
// 	t_computations	comps;
//
// 	printf("TEST 3:\n");
// 	printf("Scenario: The hit, when an intersection occurs on the outside\n\
// Given r ← ray(point(0, 0, -5), vector(0, 0, 1))\n\
// And shape ← sphere()\n\
// And i ← intersection(4, shape)\n\
// When comps ← prepare_computations(i, r)\n\
// Then comps.inside = false\n");
// 	r = ray(point(0, 0, -5), vector(0, 0, 1));
// 	shape = sphere_new();
// 	i = intersection(4, shape);
// 	comps = prepare_computations(i, r);
// 	print_computations(comps);
// 	free(shape);
// }
//
// static	void test4()
// {
// 	t_ray			r;
// 	t_object		*shape;
// 	t_intersection	i;
// 	t_computations	comps;
//
// 	printf("TEST 4:\n");
// 	printf("Scenario: The hit, when an intersection occurs on the inside\n\
// Given r ← ray(point(0, 0, 0), vector(0, 0, 1))\n\
// And shape ← sphere()\n\
// And i ← intersection(1, shape)\n\
// When comps ← prepare_computations(i, r)\n\
// Then comps.point = point(0, 0, 1)\n\
// And comps.eyev = vector(0, 0, -1)\n\
// And comps.inside = true\n\
// # normal would have been (0, 0, 1), but is inverted!\n\
// And comps.normalv = vector(0, 0, -1)\n");
// 	r = ray(point(0, 0, 0), vector(0, 0, 1));
// 	shape = sphere_new();
// 	i = intersection(1, shape);
// 	comps = prepare_computations(i, r);
// 	print_computations(comps);
// 	free(shape);
// }
//
// static	void test5()
// {
// 	t_world			*w;
// 	t_ray			r;
// 	t_object		*shape;
// 	t_intersection	i;
// 	t_computations	comps;
// 	t_color			c;
//
// 	printf("TEST 5:\n");
// 	printf("Scenario: Shading an intersection\n\
// Given w ← default_world()\n\
// And r ← ray(point(0, 0, -5), vector(0, 0, 1))\n\
// And shape ← the first object in w\n\
// And i ← intersection(4, shape)\n\
// When comps ← prepare_computations(i, r)\n\
// And c ← shade_hit(w, comps)\n\
// Then c = color(0.38066, 0.47583, 0.2855)\n");
// 	w = default_world();
// 	r = ray(point(0, 0, -5), vector(0, 0, 1));
// 	shape = w->objects[0];
// 	i = intersection(4, shape);
// 	comps = prepare_computations(i, r);
// 	print_computations(comps);
// 	c = shade_hit(w, comps);
// 	print_color(c);
// 	free_world(w);
// }
//
// static	void test6()
// {
// 	t_world			*w;
// 	t_ray			r;
// 	t_object		*shape;
// 	t_intersection	i;
// 	t_computations	comps;
// 	t_color			c;
//
// 	printf("TEST 6:\n");
// 	printf("Scenario: Shading an intersection from the inside\n\
// Given w ← default_world()\n\
// And w.light ← point_light(point(0, 0.25, 0), color(1, 1, 1))\n\
// And r ← ray(point(0, 0, 0), vector(0, 0, 1))\n\
// And shape ← the second object in w\n\
// And i ← intersection(0.5, shape)\n\
// When comps ← prepare_computations(i, r)\n\
// And c ← shade_hit(w, comps)\n\
// Then c = color(0.90498, 0.90498, 0.90498)\n");
// 	w = default_world();
// 	free(w->light);
// 	w->light = point_light(point(0, 0.25, 0), color(1, 1, 1));
// 	r = ray(point(0, 0, 0), vector(0, 0, 1));
// 	shape = w->objects[1];
// 	i = intersection(0.5, shape);
// 	comps = prepare_computations(i, r);
// 	print_computations(comps);
// 	c = shade_hit(w, comps);
// 	print_color(c);
// 	free_world(w);
// }
//
// static	void test7()
// {
// 	t_world			*w;
// 	t_ray			r;
// 	t_color			c;
//
// 	printf("TEST 7:\n");
// 	printf("Scenario: The color when a ray misses\n\
// Given w ← default_world()\n\
// And r ← ray(point(0, 0, -5), vector(0, 1, 0))\n\
// When c ← color_at(w, r)\n\
// Then c = color(0, 0, 0)\n");
// 	w = default_world();
// 	r = ray(point(0, 0, -5), vector(0, 1, 0));
// 	c = color_at(w, r);
// 	print_color(c);
// 	free_world(w);
// }
//
// static	void test8()
// {
// 	t_world			*w;
// 	t_ray			r;
// 	t_color			c;
//
// 	printf("TEST 8:\n");
// 	printf("Scenario: The color when a ray hits\n\
// Given w ← default_world()\n\
// And r ← ray(point(0, 0, -5), vector(0, 0, 1))\n\
// When c ← color_at(w, r)\n\
// Then c = color(0.38066, 0.47583, 0.2855)\n");
// 	w = default_world();
// 	r = ray(point(0, 0, -5), vector(0, 0, 1));
// 	c = color_at(w, r);
// 	print_color(c);
// 	free_world(w);
// }
//
// static	void test9()
// {
// 	t_world			*w;
// 	t_ray			r;
// 	t_color			c;
//
// 	printf("TEST 9:\n");
// 	printf("Scenario: The color with an intersection behind the ray\n\
// Given w ← default_world()\n\
// And outer ← the first object in w\n\
// And outer.material.ambient ← 1\n\
// And inner ← the second object in w\n\
// And inner.material.ambient ← 1\n\
// And r ← ray(point(0, 0, 0.75), vector(0, 0, -1))\n\
// When c ← color_at(w, r)\n\
// Then c = inner.material.color\n");
// 	w = default_world();
// 	w->objects[0]->material.ambient = 1;
// 	w->objects[1]->material.ambient = 1;
// 	r = ray(point(0, 0, 0.75), vector(0, 0, -1));
// 	c = color_at(w, r);
// 	printf("CALCULATED ");
// 	print_color(c);
// 	printf("INNER OBJECT ");
// 	print_color(w->objects[1]->material.color);
// 	free_world(w);
// }
//
// static	void test10()
// {
// 	t_point		from;
// 	t_point		to;
// 	t_vector	up;
// 	t_matrix4	t;
// 	t_matrix4	identity;
//
// 	printf("TEST 10:\n");
// 	printf("Scenario: The transformation matrix for the default orientation\n\
// Given from ← point(0, 0, 0)\n\
// And to ← point(0, 0, -1)\n\
// And up ← vector(0, 1, 0)\n\
// When t ← view_transform(from, to, up)\n\
// Then t = identity_matrix\n");
// 	from = point(0, 0, 0);
// 	to = point(0, 0, -1);
// 	up = vector(0, 1, 0);
// 	t = view_transform(from, to, up);
// 	identity = matrix4_identity();
// 	printf("CALCULATED ");
// 	print_matrix4(t);
// 	printf("CORRECT ");
// 	print_matrix4(identity);
// 		printf("\n");
// 	if (matrix4s_are_equal(t, identity))
// 		printf("Matrices are equal\n");
// 	else
// 		printf("Matrices are NOT equal\n");
// }
//
// static	void test11()
// {
// 	t_point		from;
// 	t_point		to;
// 	t_vector	up;
// 	t_matrix4	t;
// 	t_matrix4	scaling;
//
// 	printf("TEST 11:\n");
// 	printf("Scenario: A view transformation matrix looking in positive z direction\n\
// Given from ← point(0, 0, 0)\n\
// And to ← point(0, 0, 1)\n\
// And up ← vector(0, 1, 0)\n\
// When t ← view_transform(from, to, up)\n\
// Then t = scaling(-1, 1, -1)\n");
// 	from = point(0, 0, 0);
// 	to = point(0, 0, 1);
// 	up = vector(0, 1, 0);
// 	t = view_transform(from, to, up);
// 	scaling = scaling_matrix4(-1, 1, -1);
// 	printf("CALCULATED ");
// 	print_matrix4(t);
// 	printf("CORRECT ");
// 	print_matrix4(scaling);
// 		printf("\n");
// 	if (matrix4s_are_equal(t, scaling))
// 		printf("Matrices are equal\n");
// 	else
// 		printf("Matrices are NOT equal\n");
// }
//
// static	void test12()
// {
// 	t_point		from;
// 	t_point		to;
// 	t_vector	up;
// 	t_matrix4	t;
// 	t_matrix4	translation;
//
// 	printf("TEST 12:\n");
// 	printf("Scenario: The view transformation moves the world\n\
// Given from ← point(0, 0, 8)\n\
// And to ← point(0, 0, 0)\n\
// And up ← vector(0, 1, 0)\n\
// When t ← view_transform(from, to, up)\n\
// Then t = translation(0, 0, -8)\n");
// 	from = point(0, 0, 8);
// 	to = point(0, 0, 0);
// 	up = vector(0, 1, 0);
// 	t = view_transform(from, to, up);
// 	translation = translation_matrix4(0, 0, -8);
// 	printf("CALCULATED ");
// 	print_matrix4(t);
// 	printf("CORRECT ");
// 	print_matrix4(translation);
// 		printf("\n");
// 	if (matrix4s_are_equal(t, translation))
// 		printf("Matrices are equal\n");
// 	else
// 		printf("Matrices are NOT equal\n");
// }
//
// static void	test13()
// {
// 	t_point		from;
// 	t_point		to;
// 	t_vector	up;
// 	t_matrix4	t;
//
// 	printf("Scenario: An arbitrary view transformation\n\
// Given from ← point(1, 3, 2)\n\
// And to ← point(4, -2, 8)\n\
// And up ← vector(1, 1, 0)\n\
// When t ← view_transform(from, to, up)\n\
// Then t is the following 4x4 matrix:\n\
// | -0.50709 | 0.50709 | 0.67612 | -2.36643 |\n\
// | 0.76772 | 0.60609 | 0.12122 | -2.82843 |\n\
// | -0.35857 | 0.59761 | -0.71714 | 0.00000 |\n\
// | 0.00000 | 0.00000 | 0.00000 | 1.00000 |\n");
// 	from = point(1, 3, 2);
// 	to = point(4, -2, 8);
// 	up = vector(1, 1, 0);
// 	t = view_transform(from, to, up);
// 	printf("CALCULATED ");
// 	print_matrix4(t);
// }
//
// static	void test14()
// {
// 	t_world			*w;
// 	t_ray			r;
// 	t_object		*shape;
// 	t_intersection	i;
// 	t_computations	comps;
// 	t_color			c;
//
// 	printf("TEST 14:\n");
// 	printf("Scenario: shade_hit() is given an intersection in shadow\n\
// Given w ← world()\n\
// And w.light ← point_light(point(0, 0, -10), color(1, 1, 1))\n\
// And s1 ← sphere()\n\
// And s1 is added to w\n\
// And s2 ← sphere() with:\n\
// | transform | translation(0, 0, 10) |\n\
// And s2 is added to w\n\
// And r ← ray(point(0, 0, 5), vector(0, 0, 1))\n\
// And i ← intersection(4, s2)\n\
// When comps ← prepare_computations(i, r)\n\
// And c ← shade_hit(w, comps)\n\
// Then c = color(0.1, 0.1, 0.1)\n");
// 	w = default_world();
// 	free(w->light);
// 	w->light = point_light(point(0, 0, -10), color(1, 1, 1));
// 	r = ray(point(0, 0, 5), vector(0, 0, 1));
// 	shape = w->objects[1];
// 	set_transform(shape, translation_matrix4(0, 0, 10));
// 	i = intersection(4, shape);
// 	comps = prepare_computations(i, r);
// 	print_computations(comps);
// 	if (is_shadowed(w, comps.point) == true)
// 	{
// 		// w->light->in_shadow = true;
// 		printf("is shadowed\n");
// 	}
// 	c = shade_hit(w, comps);
// 	print_color(c);
// 	free_world(w);
// }
//
// static void	test15()
// {
// 	t_ray			r;
// 	t_object		*shape;
// 	t_intersection	i;
// 	t_computations	comps;
//
// 	printf("TEST 15:\n");
// 	printf("Scenario: The hit should offset the point\n\
// Given r ← ray(point(0, 0, -5), vector(0, 0, 1))\n\
// And shape ← sphere() with:\n\
// | transform | translation(0, 0, 1) |\n\
// And i ← intersection(5, shape)\n\
// When comps ← prepare_computations(i, r)\n\
// Then comps.over_point.z < -EPSILON/2\n\
// And comps.point.z > comps.over_point.z\n");
// 	r = ray(point(0, 0, -5), vector(0, 0, 1));
// 	shape = sphere_new();
// 	set_transform(shape, translation_matrix4(0, 0, 1));
// 	i = intersection(5, shape);
// 	comps = prepare_computations(i, r);
// 	if (comps.over_point.z < -EPSILON/2 && comps.point.z > comps.over_point.z)
// 		printf("\033[0;32mpass\n\033[0m");
// 	else
// 		printf("\033[0;31mfail\n\033[0m");
// }
//
// void	test_world()
// {
// 	printf("\n");
// 	printf("--------------- TESTING WORLD ---------------\n");
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
// 	test10();
// 	printf("_____________________________________________\n");
// 	test11();
// 	printf("_____________________________________________\n");
// 	test12();
// 	printf("_____________________________________________\n");
// 	test13();
// 	printf("_____________________________________________\n");
// 	test14();
// 	printf("_____________________________________________\n");
// 	test15();
// 	printf("_____________________________________________\n");
// 	printf("---------- TESTING WORLD FINISHED -----------\n");
// 	printf("\n");
// 	return;
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 12:35:01 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/21 15:59:53 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

static void	test1()
{
	printf("TEST 1:\n");
	printf("Scenario Outline: A ray misses a cylinder\n\
Given cyl ← cylinder()\n\
And direction ← normalize(<direction>)\n\
And r ← ray(<origin>, direction)\n\
When xs ← local_intersect(cyl, r)\n\
Then xs.count = 0Intersecting a Ray with a Cylinder • 179\n\
Examples:\n\
| origin\n\
| direction |\n\
| point(1, 0, 0) | vector(0, 1, 0) |\n\
| point(0, 0, 0) | vector(0, 1, 0) |\n\
| point(0, 0, -5) | vector(1, 1, 1) |\n");
	t_object *cylinder = cylinder_new();
	t_vector v = vector(0, 1, 0);
	t_point origin = point(1, 0, 0);
	t_vector direction = normalize(v);
	t_ray r = ray(origin, direction);
	t_intersections *xs = intersect(cylinder, r);
	print_intersections(xs);
	printf("\n");
	if (!xs)
		printf("1 / 3 success\n");
	else
		printf("1 / 3 fail\n");
	origin = point(0, 0, 0);
	v = vector(0, 1, 0);
	direction = normalize(v);
	r = ray(origin, direction);
	xs = intersect(cylinder, r);
	print_intersections(xs);
	if (!xs)
		printf("2 / 3 success\n");
	else
		printf("2 / 3 fail\n");
	origin = point(0, 0, -5);
	v = vector(1, 1, 1);
	direction = normalize(v);
	r = ray(origin, direction);
	xs = intersect(cylinder, r);
	if (!xs)
		printf("3 / 3 success\n");
	else
		printf("3 / 3 fail\n");
	print_intersections(xs);
	free_intersections(xs);
}

static void	test2()
{
	printf("TEST 2:\n");
	printf(" Scenario Outline: A ray strikes a cylinder\n\
Given cyl ← cylinder()\n\
And direction ← normalize(<direction>)\n\
And r ← ray(<origin>, direction)\n\
When xs ← local_intersect(cyl, r)\n\
Then xs.count = 2\n\
And xs[0].t = <t0>\n\
And xs[1].t = <t1>\n");
	t_object *cylinder = cylinder_new();
	t_point origin = point(1, 0, -5);
	t_vector v = vector(0, 0, 1);
	t_vector direction = normalize(v);
	t_ray r = ray(origin, direction);
	t_intersections *xs = intersect(cylinder, r);
	print_intersections(xs);
	printf("\n");
	origin = point(0, 0, -5);
	v = vector(0, 0, 1);
	direction = normalize(v);
	r = ray(origin, direction);
	xs = intersect(cylinder, r);
	print_intersections(xs);
	origin = point(0.5, 0, -5);
	v = vector(0.1, 1, 1);
	direction = normalize(v);
	r = ray(origin, direction);
	xs = intersect(cylinder, r);
	print_intersections(xs);
	free_intersections(xs);
}

static void	test3()
{
	printf("TEST 3:\n");
	printf("Scenario Outline: Normal vector on a cylinder\n\
Given cyl ← cylinder()\n\
When n ← local_normal_at(cyl, <point>)\n\
Then n = <normal>\n");
	t_object *cylinder = cylinder_new();
	t_point	p = point(1, 0, 0);
	t_vector normal = normal_at(cylinder, p);
	print_tuple(normal);
	p = point(0, 5, -1);
	normal = normal_at(cylinder, p);
	print_tuple(normal);
	p = point(0, -2, 1);
	normal = normal_at(cylinder, p);
	print_tuple(normal);
	p = point(-1, 1, 0);
	normal = normal_at(cylinder, p);
	print_tuple(normal);
}

static void	test4()
{
	printf("TEST 4:\n");
	printf("Scenario: The default minimum and maximum for a cylinder\n\
Given cyl ← cylinder()\n\
Then cyl.minimum = -infinity\n\
And cyl.maximum = infinity\n");
	t_object *cylinder = cylinder_new();
	print_object(cylinder);
}

static void	test5()
{
	printf("TEST 5:\n");
	printf("Scenario Outline: Intersecting a constrained cylinder\n\
Given cyl ← cylinder()\n\
And cyl.minimum ← 1\n\
And cyl.maximum ← 2\n\
And direction ← normalize(<direction>)\n\
And r ← ray(<point>, direction)\n\
When xs ← local_intersect(cyl, r)\n\
Then xs.count = <count>\n\\n");
	t_object *cylinder = cylinder_new();
	cylinder->minimum = 1;
	cylinder->maximum = 2;
	t_point origin = point(0, 1.5, 0);
	t_vector v = vector(0.1, 1, 0);
	t_vector direction = normalize(v);
	t_ray r = ray(origin, direction);
	t_intersections *xs = intersect(cylinder, r);
	print_intersections(xs);
	printf("\n");
	origin = point(0, 3, -5);
	v = vector(0, 0, 1);
	direction = normalize(v);
	r = ray(origin, direction);
	xs = intersect(cylinder, r);
	print_intersections(xs);
	origin = point(0, 0, -5);
	v = vector(0, 0, 1);
	direction = normalize(v);
	r = ray(origin, direction);
	xs = intersect(cylinder, r);
	print_intersections(xs);
	free_intersections(xs);
	origin = point(0, 2, -5);
	v = vector(0, 0, 1);
	direction = normalize(v);
	r = ray(origin, direction);
	xs = intersect(cylinder, r);
	print_intersections(xs);
	free_intersections(xs);
	origin = point(0, 1, -5);
	v = vector(0, 0, 1);
	direction = normalize(v);
	r = ray(origin, direction);
	xs = intersect(cylinder, r);
	print_intersections(xs);
	free_intersections(xs);
	origin = point(0, 1.5, -2);
	v = vector(0, 0, 1);
	direction = normalize(v);
	r = ray(origin, direction);
	xs = intersect(cylinder, r);
	print_intersections(xs);
	free_intersections(xs);
}

void	test_cylinders()
{

	printf("\n");
	printf("------------ TESTING CYLINDERS --------------\n");
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
	printf("-------- TESTING CYLINDERS FINISHED ---------\n");
	printf("\n");
}

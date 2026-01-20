/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cones.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:16:48 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/22 12:50:32 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	test1()
{
	printf("TEST 1:\n");
	printf("Scenario Outline: Intersecting a cone with a ray\n\
Given shape ← cone()\n\
And direction ← normalize(<direction>)\n\
And r ← ray(<origin>, direction)\n\
When xs ← local_intersect(shape, r)\n\
Then xs.count = 2\n\
And xs[0].t = <t0>\n\
And xs[1].t = <t1>\n");
	t_object *cone = cone_new();
	t_point origin = point(0, 0, -5);
	t_vector v = vector(0, 0, 1);
	t_vector direction = normalize(v);
	t_ray r = ray(origin, direction);
	t_intersections *xs = intersect(cone, r, NULL);
	printf("1: count = %d\tt0 = %lf\t t1 = %lf\n", xs->count, xs->arr[0].t, xs->arr[1].t);
	free_intersections(&xs);
	origin = point(0, 0, -5);
	v = vector(1, 1, 1);
	direction = normalize(v);
	r = ray(origin, direction);
	xs = intersect(cone, r, NULL);
	printf("2: count = %d\tt0 = %lf\t t1 = %lf\n", xs->count, xs->arr[0].t, xs->arr[1].t);
	free_intersections(&xs);
	origin = point(1, 1, -5);
	v = vector(-0.5, -1, 1);
	direction = normalize(v);
	r = ray(origin, direction);
	xs = intersect(cone, r, NULL);
	printf("3: count = %d\tt0 = %lf\t t1 = %lf\n", xs->count, xs->arr[0].t, xs->arr[1].t);
	free_intersections(&xs);
	free(cone);
}

static void	test2()
{
	printf("TEST 2:\n");
	printf("Scenario: Intersecting a cone with a ray parallel to one of its halves\n\
Given shape ← cone()\n\
And direction ← normalize(vector(0, 1, 1))\n\
And r ← ray(point(0, 0, -1), direction)\n\
When xs ← local_intersect(shape, r)\n\
Then xs.count = 1\n\
And xs[0].t = 0.35355\n");
	t_object *cone = cone_new();
	t_vector direction = normalize(vector(0, 1, 1));
	t_ray r = ray(point(0, 0, -1), direction);
	t_intersections *xs = intersect(cone, r, NULL);
	printf("xs->count = %d\n", xs->count);
	printf("t0 = %lf\n", xs->arr[0].t);
	free_intersections(&xs);
	free(cone);
}

static void	test3()
{
	printf("TEST 3:\n");
	printf("Scenario Outline: Intersecting a cone's end caps\n\
Given shape ← cone()\n\
And shape.minimum ← -0.5\n\
And shape.maximum ← 0.5\n\
And shape.closed ← true\n\
And direction ← normalize(<direction>)\n\
And r ← ray(<origin>, direction)\n\
When xs ← local_intersect(shape, r)\n\
Then xs.count = <count>\n");
	t_object *cone = cone_new();
	cone->minimum = -0.5;
	cone->maximum = 0.5;
	cone->closed = true;
	t_point origin = point(0, 0, -5);
	t_vector v = vector(0, 1, 0);
	t_vector direction = normalize(v);
	t_ray r = ray(origin, direction);
	t_intersections *xs = intersect(cone, r, NULL);
	if (xs)
		printf("1: count = %d\n", xs->count);
	else
		printf("1: count = 0\n");
	free_intersections(&xs);
	origin = point(0, 0, -0.25);
	v = vector(0, 1, 1);
	direction = normalize(v);
	r = ray(origin, direction);
	xs = intersect(cone, r, NULL);
	if (xs)
		printf("2: count = %d\n", xs->count);
	else
		printf("1: count = 0\n");
	free_intersections(&xs);
	origin = point(0, 0, -0.25);
	v = vector(0, 1, 0);
	direction = normalize(v);
	r = ray(origin, direction);
	xs = intersect(cone, r, NULL);
	if (xs)
		printf("3: count = %d\n", xs->count);
	else
		printf("1: count = 0\n");
	free_intersections(&xs);
	free(cone);
}

static void	test4()
{
	printf("TEST 4:\n");
	printf("Scenario Outline: Intersecting a cone's end caps\n\
Given shape ← cone()\n\
And shape.minimum ← -0.5\n\
And shape.maximum ← 0.5\n\
And shape.closed ← true\n\
And direction ← normalize(<direction>)\n\
And r ← ray(<origin>, direction)\n\
When xs ← local_intersect(shape, r)\n\
Then xs.count = <count>\n");
	t_object *cone = cone_new();
	t_point p = point(0, 0, 0);
	t_vector normal = local_normal_at(cone, p);
	print_tuple(normal);
	p = point(1, 1, 1);
	normal = local_normal_at(cone, p);
	print_tuple(normal);
	p = point(-1, -1, 0);
	normal = local_normal_at(cone, p);
	print_tuple(normal);
	free(cone);
}

void	test_cones()
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
	printf("-------- TESTING CYLINDERS FINISHED ---------\n");
	printf("\n");
}

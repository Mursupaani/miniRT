/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cubes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:27:45 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/21 14:59:27 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	test1()
{
	printf("TEST 1:\n");
	printf("Scenario Outline: A ray intersects a cube\n\
Given c ← cube()\n\
And r ← ray(<origin>, <direction>)\n\
When xs ← local_intersect(c, r)\n\
Then xs.count = 2\n\
And xs[0].t = <t1>\n\
And xs[1].t = <t2>\n");
	t_object	*cube = cube_new();
	t_ray	r = ray(point(5, 0.5, 0), vector(-1, 0, 0));
	t_intersections *xs = intersect_cube(cube, r, NULL);
	printf("\n");
	printf("t1 = %lf\n", xs->arr[0].t);
	printf("t2 = %lf\n", xs->arr[1].t);
	printf("\n");
	free_intersections(&xs);

	r = ray(point(-5, 0.5, 0), vector(1, 0, 0));
	xs = intersect_cube(cube, r, NULL);
	printf("t1 = %lf\n", xs->arr[0].t);
	printf("t2 = %lf\n", xs->arr[1].t);
	printf("\n");
	free_intersections(&xs);

	r = ray(point(0.5, 5, 0), vector(0, -1, 0));
	xs = intersect_cube(cube, r, NULL);
	printf("t1 = %lf\n", xs->arr[0].t);
	printf("t2 = %lf\n", xs->arr[1].t);
	printf("\n");
	free_intersections(&xs);

	r = ray(point(0.5, -5, 0), vector(0, 1, 0));
	xs = intersect_cube(cube, r, NULL);
	printf("t1 = %lf\n", xs->arr[0].t);
	printf("t2 = %lf\n", xs->arr[1].t);
	printf("\n");
	free_intersections(&xs);

	r = ray(point(0.5, 0, 5), vector(0, 0, -1));
	xs = intersect_cube(cube, r, NULL);
	printf("t1 = %lf\n", xs->arr[0].t);
	printf("t2 = %lf\n", xs->arr[1].t);
	printf("\n");
	free_intersections(&xs);

	r = ray(point(0.5, 0, -5), vector(0, 0, 1));
	xs = intersect_cube(cube, r, NULL);
	printf("t1 = %lf\n", xs->arr[0].t);
	printf("t2 = %lf\n", xs->arr[1].t);
	printf("\n");
	free_intersections(&xs);

	r = ray(point(0, 0.5, 0), vector(0, 0, 1));
	xs = intersect_cube(cube, r, NULL);
	printf("t1 = %lf\n", xs->arr[0].t);
	printf("t2 = %lf\n", xs->arr[1].t);
	printf("\n");
	free_intersections(&xs);

}

static void	test2()
{
	printf("TEST 2:\n");
	printf("Scenario Outline: A ray misses a cube\n\
Given c ← cube()\n\
And r ← ray(<origin>, <direction>)\n\
When xs ← local_intersect(c, r)\n\
Then xs.count = 0\n\
Examples:\n\
| origin\n\
| point(-2, 0, 0)\n\
| point(0, -2, 0)\n\
| point(0, 0, -2)\n\
| point(2, 0, 2)\n\
| point(0, 2, 2)\n\
| point(2, 2, 0)\n\
| direction\n\
|\n\
| vector(0.2673, 0.5345, 0.8018) |\n\
| vector(0.8018, 0.2673, 0.5345) |\n\
| vector(0.5345, 0.8018, 0.2673) |\n\
| vector(0, 0, -1)\n\
| vector(0, -1, 0)\n\
| vector(-1, 0, 0)\n");
	t_object	*cube = cube_new();
	t_ray	r = ray(point(-2, 0, 0), vector(0.2673, 0.5345, 0.8018));
	t_intersections *xs = intersect_cube(cube, r, NULL);
	if (!xs)
		printf("1 / 6 is NULL aka SUCCESS!\n");
	else
		printf("1 / 6 FAIL\n");
	free_intersections(&xs);

	r = ray(point(0, -2, 0), vector(0.8018, 0.2673, 0.5345));
	xs = intersect_cube(cube, r, NULL);
	if (!xs)
		printf("2 / 6 is NULL aka SUCCESS!\n");
	else
		printf("2 / 6 FAIL\n");
	free_intersections(&xs);

	r = ray(point(0, 0, -2), vector(0.5345, 0.8018, 0.2673));
	xs = intersect_cube(cube, r, NULL);
	xs = intersect_cube(cube, r, NULL);
	if (!xs)
		printf("3 / 6 is NULL aka SUCCESS!\n");
	else
		printf("3 / 6 FAIL\n");
	free_intersections(&xs);

	r = ray(point(2, 0, 2), vector(0, 0, -1));
	xs = intersect_cube(cube, r, NULL);
	xs = intersect_cube(cube, r, NULL);
	if (!xs)
		printf("4 / 6 is NULL aka SUCCESS!\n");
	else
		printf("4 / 6 FAIL\n");
	free_intersections(&xs);

	r = ray(point(0, 2, 2), vector(0, -1, 0));
	xs = intersect_cube(cube, r, NULL);
	xs = intersect_cube(cube, r, NULL);
	if (!xs)
		printf("5 / 6 is NULL aka SUCCESS!\n");
	else
		printf("5 / 6 FAIL\n");
	free_intersections(&xs);

	r = ray(point(2, 2, 0), vector(-1, 0, 0));
	xs = intersect_cube(cube, r, NULL);
	xs = intersect_cube(cube, r, NULL);
	if (!xs)
		printf("6 / 6 is NULL aka SUCCESS!\n");
	else
		printf("6 / 6 FAIL\n");
	free_intersections(&xs);
}

static void	test3()
{
	printf("TEST 3:\n");
	printf("Scenario Outline: The normal on the surface of a cube\n\
Given c ← cube()\n\
And p ← <point>\n\
When normal ← local_normal_at(c, p)\n\
Then normal = <normal>\n");
	t_object	*cube = cube_new();
	t_point	p = point(1, 0.5, -0.8);
	t_vector normal = local_normal_at(cube, p);
	print_tuple(normal);
	printf("\n");

	p = point(-1, -0.2, 0.9);
	normal = local_normal_at(cube, p);
	print_tuple(normal);

	p = point(-0.4, 1, -0.1);
	normal = local_normal_at(cube, p);
	print_tuple(normal);

	p = point(0.3, -1, -0.7);
	normal = local_normal_at(cube, p);
	print_tuple(normal);

	p = point(-0.6, 0.3, 1);
	normal = local_normal_at(cube, p);
	print_tuple(normal);

	p = point(0.4, 0.4, -1);
	normal = local_normal_at(cube, p);
	print_tuple(normal);

	p = point(1, 1, 1);
	normal = local_normal_at(cube, p);
	print_tuple(normal);

	p = point(-1, -1, -1);
	normal = local_normal_at(cube, p);
	print_tuple(normal);

	free(cube);
}

void	test_cubes()
{

	printf("\n");
	printf("-------------- TESTING CUBES ----------------\n");
	printf("_____________________________________________\n");
	test1();
	printf("_____________________________________________\n");
	test2();
	printf("---------- TESTING CUBES FINISHED -----------\n");
	test3();
	printf("---------- TESTING CUBES FINISHED -----------\n");
	printf("\n");
}

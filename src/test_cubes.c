/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cubes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:27:45 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/19 17:28:16 by anpollan         ###   ########.fr       */
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
	t_intersections *xs = local_intersect(cube, r);
	printf("\n");
	printf("t1 = %lf\n", xs->arr[0].t);
	printf("t2 = %lf\n", xs->arr[1].t);
	printf("\n");
	free_intersections(xs);

	r = ray(point(-5, 0.5, 0), vector(1, 0, 0));
	xs = local_intersect(cube, r);
	printf("t1 = %lf\n", xs->arr[0].t);
	printf("t2 = %lf\n", xs->arr[1].t);
	printf("\n");
	free_intersections(xs);

	r = ray(point(0.5, 5, 0), vector(0, -1, 0));
	xs = local_intersect(cube, r);
	printf("t1 = %lf\n", xs->arr[0].t);
	printf("t2 = %lf\n", xs->arr[1].t);
	printf("\n");
	free_intersections(xs);

	r = ray(point(0.5, -5, 0), vector(0, 1, 0));
	xs = local_intersect(cube, r);
	printf("t1 = %lf\n", xs->arr[0].t);
	printf("t2 = %lf\n", xs->arr[1].t);
	printf("\n");
	free_intersections(xs);

	r = ray(point(0.5, 0, 5), vector(0, 0, -1));
	xs = local_intersect(cube, r);
	printf("t1 = %lf\n", xs->arr[0].t);
	printf("t2 = %lf\n", xs->arr[1].t);
	printf("\n");
	free_intersections(xs);

	r = ray(point(0.5, 0, -5), vector(0, 0, 1));
	xs = local_intersect(cube, r);
	printf("t1 = %lf\n", xs->arr[0].t);
	printf("t2 = %lf\n", xs->arr[1].t);
	printf("\n");
	free_intersections(xs);

	r = ray(point(0, 0.5, 0), vector(0, 0, 1));
	xs = local_intersect(cube, r);
	printf("t1 = %lf\n", xs->arr[0].t);
	printf("t2 = %lf\n", xs->arr[1].t);
	printf("\n");
	free_intersections(xs);

}

void	test_cubes()
{

	printf("\n");
	printf("-------------- TESTING CUBES ----------------\n");
	printf("_____________________________________________\n");
	test1();
	printf("_____________________________________________\n");
	printf("---------- TESTING CUBES FINISHED -----------\n");
	printf("\n");
}

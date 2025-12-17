/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_reflections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:15:27 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/17 11:35:09 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

static void	test1()
{
	printf("TEST 1:");
	printf("Scenario: Reflectivity for the default material\n\
Given m ← material()\n\
Then m.reflective = 0.0\n");
	t_material	m = material();
	print_material(m);
}

static void	test2()
{
	printf("TEST 2:");
	printf("Scenario: Precomputing the reflection vector\n\
Given shape ← plane()\n\
And r ← ray(point(0, 1, -1), vector(0, -√2/2, √2/2))\n\
And i ← intersection(√2, shape)\n\
When comps ← prepare_computations(i, r)\n\
Then comps.reflectv = vector(0, √2/2, √2/2)\n");
	t_object *shape = plane();
	t_ray r = ray(point(0, 1, -1), vector(0, -sqrt(2) / 2, sqrt(2) / 2));
	t_intersection i = intersection(sqrt(2), shape);
	t_computations comps = prepare_computations(i, r);
	print_computations(comps);
	free(shape);
}

static void	test3()
{
	printf("TEST 3:");
	printf("Scenario: The reflected color for a nonreflective material\n\
Given w ← default_world()\n\
And r ← ray(point(0, 0, 0), vector(0, 0, 1))\n\
And shape ← the second object in w\n\
And shape.material.ambient ← 1\n\
And i ← intersection(1, shape)\n\
When comps ← prepare_computations(i, r)\n\
And color ← reflected_color(w, comps)\n\
Then color = color(0, 0, 0)\n");
	t_world	*w = default_world();
	t_ray r = ray(point(0, 0, 0), vector(0, 0, 1));
	t_object *shape = w->objects[1];
	shape->material.ambient = 1;
	t_intersection i = intersection(1, shape);
	t_computations comps = prepare_computations(i, r);
	print_computations(comps);
	free(shape);
}

void	test_reflections()
{
	printf("\n");
	printf("------------ TESTING REFLECTIONS ------------\n");
	printf("_____________________________________________\n");
	test1();
	printf("_____________________________________________\n");
	test2();
	printf("_____________________________________________\n");
	printf("-------- TESTING REFLECTIONS FINISHED -------\n");
	printf("\n");
}

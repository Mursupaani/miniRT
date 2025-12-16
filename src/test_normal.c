/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_normal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:54:51 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/16 12:09:08 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

static void	test1()
{
	t_object	*sphere;
	t_vector	normal;

	printf("TEST 1:\n");
	sphere = sphere_new_args(point(0, 0, 0), 1, color255(255, 0, 0));
	printf("Scenario: The normal on a sphere at a point on the x axis\n\
Given s ← sphere()\n\
When n ← normal_at(s, point(1, 0, 0))\n\
Then n = vector(1, 0, 0)\n");
	normal = normal_at(sphere, point(1, 0, 0));
	print_tuple(normal);
	free(sphere);
}

static void	test2()
{
	t_object	*sphere;
	t_vector	normal;

	printf("TEST 2:\n");
	sphere = sphere_new_args(point(0, 0, 0), 1, color255(255, 0, 0));
	printf("Scenario: The normal on a sphere at a nonaxial point\n\
Given s ← sphere()\n\
When n ← normal_at(s, point(√3/3, √3/3, √3/3))\n\
Then n = vector(√3/3, √3/3, √3/3)\n");
	normal = normal_at(sphere, point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
	print_tuple(normal);
	free(sphere);
}

static void	test3()
{
	t_object	*sphere;
	t_vector	normal;

	printf("TEST 3:\n");
	printf("Scenario: Computing the normal on a translated sphere\n\
Given s ← sphere()\n\
And set_transform(s, translation(0, 1, 0))\n\
When n ← normal_at(s, point(0, 1.70711, -0.70711))\n\
Then n = vector(0, 0.70711, -0.70711)\n");
	sphere = sphere_new_args(point(0, 0, 0), 1, color255(255, 0, 0));
	set_transform(sphere, translation_matrix4(0, 1, 0));
	normal = normal_at(sphere, point(0, 1.70711, -0.70711));
	print_tuple(normal);
	free(sphere);
	sphere = sphere_new_args(point(0, 1, 0), 1, color255(255, 0, 0));
	// set_transform(sphere, translation_matrix4(0, 1, 0));
	normal = normal_at(sphere, point(0, 1.70711, -0.70711));
	print_tuple(normal);
	free(sphere);
}

static void	test4()
{
	t_object	*sphere;
	t_matrix4	m;
	t_vector	normal;

	printf("TEST 4:\n");
	printf("Scenario: Computing the normal on a transformed sphere\n\
Given s ← sphere()\n\
And m ← scaling(1, 0.5, 1) * rotation_z(π/5)\n\
And set_transform(s, m)\n\
When n ← normal_at(s, point(0, √2/2, -√2/2))\n\
Then n = vector(0, 0.97014, -0.24254)\n");
	sphere = sphere_new_args(point(0, 0, 0), 1, color255(255, 0, 0));
	m = matrix4_multiply(scaling_matrix4(1, 0.5, 1), rotation_z(M_PI / 5));
	set_transform(sphere, m);
	normal = normal_at(sphere, point(0, sqrt(2) / 2, -sqrt(2) / 2));
	print_tuple(normal);
	free(sphere);
}

static void	test5()
{
	t_vector	v;
	t_vector	n;
	t_vector	r;
	
	printf("TEST 5:\n");
	printf("Scenario: Reflecting a vector approaching at 45°\n\
Given v ← vector(1, -1, 0)\n\
And n ← vector(0, 1, 0)\n\
When r ← reflect(v, n)\n\
Then r = vector(1, 1, 0)\n");
	v = vector(1, -1, 0);
	n = vector(0, 1, 0);
	r = reflect(v, n);
	print_tuple(r);
}

static void	test6()
{
	t_vector	v;
	t_vector	n;
	t_vector	r;
	
	printf("TEST 6:\n");
	printf("Scenario: Reflecting a vector off a slanted surface\n\
Given v ← vector(0, -1, 0)\n\
And n ← vector(√2/2, √2/2, 0)\n\
When r ← reflect(v, n)\n\
Then r = vector(1, 0, 0)\n");
	v = vector(0, -1, 0);
	n = vector(sqrt(2) / 2, sqrt(2) / 2, 0);
	r = reflect(v, n);
	print_tuple(r);
}

void	test_normal(void)
{
	printf("\n");
	printf("--------------- TESTING NORMAL --------------\n");
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
	test6();
	printf("_____________________________________________\n");
	printf("---------- TESTING NORMAL FINISHED ----------\n");
	printf("\n");
}

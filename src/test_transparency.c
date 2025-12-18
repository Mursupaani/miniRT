/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_transparency.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:36:44 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/18 15:15:49 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*glass_sphere()
{
	t_object	*sphere;

	sphere = sphere_new();
	sphere->material.transparency = 1;
	sphere->material.refractive_index = 1.5;
	return (sphere);
}

static void	test1()
{
	printf("TEST 1:");
	printf("Scenario: Transparency and Refractive Index for the default material\n\
Given m ← material()\n\
Then m.transparency = 0.0\n\
And m.refractive_index = 1.0\n");
	t_material	m = material();
	print_material(m);
}

static void	test2()
{
	printf("TEST 2:");
	printf("Scenario: A helper for producing a sphere with a glassy material\n\
Given s ← glass_sphere()\n\
Then s.transform = identity_matrix\n\
And s.material.transparency = 1.0\n\
And s.material.refractive_index = 1.5\n");
	t_object	*sphere = glass_sphere();
	print_object(sphere);
}

static void	test3()
{
	printf("TEST 3:");
	printf("Scenario Outline: Finding n1 and n2 at various intersections\n\
Given A ← glass_sphere() with:\n\
| transform | scaling(2, 2, 2) |\n\
| material.refractive_index | 1.5 |\n\
And B ← glass_sphere() with:\n\
| transform | translation(0, 0, -0.25) |\n\
| material.refractive_index | 2.0 |\n\
And C ← glass_sphere() with:\n\
| transform | translation(0, 0, 0.25) |\n\
| material.refractive_index | 2.5 |\n\
And r ← ray(point(0, 0, -4), vector(0, 0, 1))\n\
And xs ← intersections(2:A, 2.75:B, 3.25:C, 4.75:B, 5.25:C, 6:A)\n\
When comps ← prepare_computations(xs[<index>], r, xs)\n\
Then comps.n1 = <n1>\n\
And comps.n2 = <n2>\n");
	t_object	*a = glass_sphere();
	set_transform(a, scaling_matrix4(2, 2, 2));
	a->material.refractive_index = 1.5;
	t_object	*b = glass_sphere();
	set_transform(b, translation_matrix4(0, 0, -0.25));
	b->material.refractive_index = 2;
	t_object	*c = glass_sphere();
	set_transform(c, translation_matrix4(0, 0, 0.25));
	c->material.refractive_index = 2.5;
	t_ray r = ray(point(0, 0, -4), vector(0, 0, 1));
	t_intersections *xs = malloc(sizeof(t_intersections));
	xs->arr = malloc(sizeof(t_intersection) * 6);
	xs->arr[0] = (t_intersection){2, a};
	xs->arr[1] = (t_intersection){2.75, b};
	xs->arr[2] = (t_intersection){3.25, c};
	xs->arr[3] = (t_intersection){4.75, b};
	xs->arr[4] = (t_intersection){5.25, c};
	xs->arr[5] = (t_intersection){6, a};
	xs->count = 6;
	t_computations comps = prepare_computations(xs->arr[0], r, xs);
	printf("[0]: | n1 = %f |\t| n2 = %f |\n", comps.n1, comps.n2);
	comps = prepare_computations(xs->arr[1], r, xs);
	printf("[1]: | n1 = %f |\t| n2 = %f |\n", comps.n1, comps.n2);
	comps = prepare_computations(xs->arr[2], r, xs);
	printf("[2]: | n1 = %f |\t| n2 = %f |\n", comps.n1, comps.n2);
	comps = prepare_computations(xs->arr[3], r, xs);
	printf("[3]: | n1 = %f |\t| n2 = %f |\n", comps.n1, comps.n2);
	comps = prepare_computations(xs->arr[4], r, xs);
	printf("[4]: | n1 = %f |\t| n2 = %f |\n", comps.n1, comps.n2);
	comps = prepare_computations(xs->arr[5], r, xs);
	printf("[5]: | n1 = %f |\t| n2 = %f |\n", comps.n1, comps.n2);
}

static void	test4()
{
	printf("TEST 4:");
	printf("Scenario: The under point is offset below the surface\n\
Given r ← ray(point(0, 0, -5), vector(0, 0, 1))\n\
And shape ← glass_sphere() with:\n\
| transform | translation(0, 0, 1) |\n\
And i ← intersection(5, shape)\n\
And xs ← intersections(i)\n\
When comps ← prepare_computations(i, r, xs)\n\
Then comps.under_point.z > EPSILON/2\n\
And comps.point.z < comps.under_point.z\n");
	t_ray	r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_object	*sphere = glass_sphere();
	set_transform(sphere, translation_matrix4(0, 0, 1));
	t_intersection	i = intersection(5, sphere);
	t_intersections	*xs = malloc(sizeof(t_intersections));
	xs->arr = malloc(sizeof(t_intersection));
	xs->arr[0] = i;
	xs->count = 1;
	t_computations	comps = prepare_computations(i, r, xs);
	print_computations(comps);
}

void	test_transparency()
{
	printf("\n");
	printf("------------ TESTING REFRACTIONS ------------\n");
	printf("_____________________________________________\n");
	test1();
	printf("_____________________________________________\n");
	test2();
	printf("_____________________________________________\n");
	test3();
	printf("_____________________________________________\n");
	test4();
	printf("_____________________________________________\n");
	printf("-------- TESTING REFRACTIONS FINISHED -------\n");
	printf("\n");
}

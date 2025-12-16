/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_patterns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 12:07:23 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/16 12:44:13 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	black;
t_color	white;

static void	test1()
{
	t_pattern	pattern;

	printf("TEST 1:\n");
	printf("Scenario: Creating a stripe pattern\n\
Given pattern ← stripe_pattern(white, black)\n\
Then pattern.a = white\n\
And pattern.b = black\n");
	pattern = stripe_pattern(white, black);
	print_pattern(pattern);
}

static void	test2()
{
	t_color		c;
	t_pattern	pattern;
	t_point		p;

	printf("TEST 2:\n");
	printf("Scenario: A stripe pattern is constant in y\n\
Given pattern ← stripe_pattern(white, black)\n\
Then stripe_at(pattern, point(0, 0, 0)) = white\n\
And stripe_at(pattern, point(0, 1, 0)) = white\n\
And stripe_at(pattern, point(0, 2, 0)) = white\n");
	pattern = stripe_pattern(white, black);
	printf("----------\n");
	p = point(0, 0, 0);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
	printf("----------\n");
	p = point(0, 1, 0);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
	printf("----------\n");
	p = point(0, 2, 0);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
}

static void	test3()
{
	t_color		c;
	t_pattern	pattern;
	t_point		p;

	printf("TEST 3:\n");
	printf("Scenario: A stripe pattern is constant in z\n\
Given pattern ← stripe_pattern(white, black)\n\
Then stripe_at(pattern, point(0, 0, 0)) = white\n\
And stripe_at(pattern, point(0, 0, 1)) = white\n\
And stripe_at(pattern, point(0, 0, 2)) = white\n");
	pattern = stripe_pattern(white, black);
	printf("----------\n");
	p = point(0, 0, 0);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
	printf("----------\n");
	p = point(0, 0, 1);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
	printf("----------\n");
	p = point(0, 0, 2);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
}

static void	test4()
{
	t_color		c;
	t_pattern	pattern;
	t_point		p;

	printf("TEST 4:\n");
	printf("Scenario: A stripe pattern alternates in x\n\
Given pattern ← stripe_pattern(white, black)\n\
Then stripe_at(pattern, point(0, 0, 0)) = white\n\
And stripe_at(pattern, point(0.9, 0, 0)) = white\n\
And stripe_at(pattern, point(1, 0, 0)) = black\n\
And stripe_at(pattern, point(-0.1, 0, 0)) = black\n\
And stripe_at(pattern, point(-1, 0, 0)) = black\n\
And stripe_at(pattern, point(-1.1, 0, 0)) = white\n");
	printf("----------\n");
	pattern = stripe_pattern(white, black);
	p = point(0, 0, 0);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
	printf("----------\n");
	p = point(0.9, 0, 0);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
	printf("----------\n");
	p = point(1, 0, 0);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
	printf("----------\n");
	p = point(-0.1, 0, 0);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
	printf("----------\n");
	p = point(-1, 0, 0);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
	printf("----------\n");
	p = point(-1.1, 0, 0);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
}

static void	test5()
{
	printf("TEST 5:\n");
	printf("Scenario: Lighting with a pattern applied\n\
Given m.pattern ← stripe_pattern(color(1, 1, 1), color(0, 0, 0))\n\
And m.ambient ← 1\n\
And m.diffuse ← 0\n\
And m.specular ← 0\n\
And eyev ← vector(0, 0, -1)\n\
And normalv ← vector(0, 0, -1)\n\
And light ← point_light(point(0, 0, -10), color(1, 1, 1))\n\
When c1 ← lighting(m, light, point(0.9, 0, 0), eyev, normalv, false)\n\
And c2 ← lighting(m, light, point(1.1, 0, 0), eyev, normalv, false)\n\
Then c1 = color(1, 1, 1)\n\
And c2 = color(0, 0, 0)\n");
	printf("----------\n");
	t_object *obj = sphere_new();
	t_material m = material();
	m.pattern = stripe_pattern(white, black);
	m.ambient = 1;
	m.diffuse = 0;
	m.specular = 0;
	obj->material = m;
	t_vector eyev = vector(0, 0, -1);
	t_vector normalv = vector(0, 0, -1);
	t_light *light = point_light(point(0, 0, -10), color(1, 1, 1));
	t_computations comps;
	comps.over_point = point(0.9, 0, 0);
	comps.normalv = normalv;
	comps.eyev = eyev;
	comps.in_shadow = false;
	comps.object = obj;
	t_color c1 = lighting(comps, light);
	print_tuple(comps.over_point);
	print_color(c1);
	printf("----------\n");
	comps.over_point = point(1.1, 0, 0);
	t_color c2 = lighting(comps, light);
	print_tuple(comps.over_point);
	print_color(c2);
	free(obj);
}

static void	test6()
{
	printf("TEST 6:\n");
	printf("Scenario: Stripes with an object transformation\n\
Given object ← sphere()\n\
And set_transform(object, scaling(2, 2, 2))\n\
And pattern ← stripe_pattern(white, black)\n\
When c ← stripe_at_object(pattern, object, point(1.5, 0, 0))\n\
Then c = white\n");
	printf("----------\n");
	t_object *obj = sphere_new();
	set_transform(obj, scaling_matrix4(2, 2, 2));
	t_pattern pattern = stripe_pattern(white, black);
	t_color c = stripe_at_object(pattern, obj, point(1.5, 0, 0));
	print_color(c);
	free(obj);
}

static void	test7()
{
	printf("TEST 7:\n");
	printf("Scenario: Stripes with a pattern transformation\n\
Given object ← sphere()\n\
And pattern ← stripe_pattern(white, black)\n\
And set_pattern_transform(pattern, scaling(2, 2, 2))\n\
When c ← stripe_at_object(pattern, object, point(1.5, 0, 0))\n\
Then c = white\n");
	printf("----------\n");
	t_object *obj = sphere_new();
	t_pattern pattern = stripe_pattern(white, black);
	set_pattern_transform(&pattern, scaling_matrix4(2, 2, 2));
	t_color c = stripe_at_object(pattern, obj, point(1.5, 0, 0));
	print_color(c);
	free(obj);
}

static void	test8()
{
	printf("TEST 8:\n");
	printf("Scenario: Stripes with both an object and a pattern transformation\n\
Given object ← sphere()\n\
And set_transform(object, scaling(2, 2, 2))\n\
And pattern ← stripe_pattern(white, black)\n\
And set_pattern_transform(pattern, translation(0.5, 0, 0))\n\
When c ← stripe_at_object(pattern, object, point(2.5, 0, 0))\n\
Then c = white\n");
	printf("----------\n");
	t_object *obj = sphere_new();
	set_transform(obj, scaling_matrix4(2, 2, 2));
	t_pattern pattern = stripe_pattern(white, black);
	set_pattern_transform(&pattern, translation_matrix4(0.5, 0, 0));
	t_color c = stripe_at_object(pattern, obj, point(2.5, 0, 0));
	print_color(c);
	free(obj);
}

void	test_patterns(void)
{
	black = color(0, 0, 0);
	white = color(1, 1, 1);
	printf("\n");
	printf("------------- TESTING PATTERNS --------------\n");
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
	test7();
	printf("_____________________________________________\n");
	test8();
	printf("_____________________________________________\n");
	printf("--------- TESTING PATTERNS FINISHED ---------\n");
	printf("\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_uv_patterns.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 13:28:59 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/26 21:03:23 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "minirt.h"
#include <math.h>

static t_color	black;
static t_color	white;

static void	test1()
{
	t_uv_ptrn	pattern;

	printf("TEST 1:\n");
	printf("Scenario Outline: Checker pattern in 2D\n\
  Given checkers ← uv_checkers(2, 2, black, white)\n\
  When color ← uv_pattern_at(checkers, <u>, <v>)\n\
  Then color = <expected>\n\
  Examples:\n\
    | u   | v   | expected |\n\
    | 0.0 | 0.0 | black    |\n\
    | 0.5 | 0.0 | white    |\n\
    | 0.0 | 0.5 | white    |\n\
    | 0.5 | 0.5 | black    |\n\
    | 1.0 | 1.0 | black    |\n");
	pattern = uv_checkers(2, 2, black, white);
	print_uv_pattern(pattern);
	double u = 0;
	double v = 0;
	t_color c = uv_pattern_at(pattern, u, v);
	printf("\n");
	print_color(c);
	u = 0.5;
	v = 0;
	c = uv_pattern_at(pattern, u, v);
	printf("\n");
	print_color(c);
	u = 0;
	v = 0.5;
	c = uv_pattern_at(pattern, u, v);
	printf("\n");
	print_color(c);
	u = 0.5;
	v = 0.5;
	c = uv_pattern_at(pattern, u, v);
	printf("\n");
	print_color(c);
	u = 1;
	v = 1;
	c = uv_pattern_at(pattern, u, v);
	printf("\n");
	print_color(c);
}

static void	test2()
{
	printf("TEST 2:\n");
	printf("Scenario Outline: Using a spherical mapping on a 3D point\n\
  Given p ← <point>\n\
  When (u, v) ← spherical_map(p)\n\
  Then u = <u>\n\
    And v = <v>\n\
  Examples:\n\
    | point                | u    | v    |\n\
    | point(0, 0, -1)      | 0.0  | 0.5  |\n\
    | point(1, 0, 0)       | 0.25 | 0.5  |\n\
    | point(0, 0, 1)       | 0.5  | 0.5  |\n\
    | point(-1, 0, 0)      | 0.75 | 0.5  |\n\
    | point(0, 1, 0)       | 0.5  | 1.0  |\n\
    | point(0, -1, 0)      | 0.5  | 0.0  |\n\
    | point(√2/2, √2/2, 0) | 0.25 | 0.75 |\n");
	t_point	p;
	t_uv_map	uv;
	p = point(0, 0 ,-1);
	uv = spherical_map(p);
	print_uv_map(uv);
	p = point(1, 0 ,0);
	uv = spherical_map(p);
	print_uv_map(uv);
	p = point(0, 0 ,1);
	uv = spherical_map(p);
	print_uv_map(uv);
	p = point(-1, 0 ,0);
	uv = spherical_map(p);
	print_uv_map(uv);
	p = point(0, 1 ,0);
	uv = spherical_map(p);
	print_uv_map(uv);
	p = point(0, -1 ,0);
	uv = spherical_map(p);
	print_uv_map(uv);
	p = point(sqrt(2) / 2, sqrt(2) / 2, 0);
	uv = spherical_map(p);
	print_uv_map(uv);
}

static void	test3()
{
	printf("TEST 3:\n");
	printf("Scenario Outline: Using a texture map pattern with a spherical map\n\
  Given checkers ← uv_checkers(16, 8, black, white)\n\
    And pattern ← texture_map(checkers, spherical_map)\n\
  Then pattern_at(pattern, <point>) = <color>\n\
  Examples:\n\
    | point                            | color |\n\
    | point(0.4315, 0.4670, 0.7719)    | white |\n\
    | point(-0.9654, 0.2552, -0.0534)  | black |\n\
    | point(0.1039, 0.7090, 0.6975)    | white |\n\
    | point(-0.4986, -0.7856, -0.3663) | black |\n\
    | point(-0.0317, -0.9395, 0.3411)  | black |\n\
    | point(0.4809, -0.7721, 0.4154)   | black |\n\
    | point(0.0285, -0.9612, -0.2745)  | black |\n\
    | point(-0.5734, -0.2162, -0.7903) | white |\n\
    | point(0.7688, -0.1470, 0.6223)   | black |\n\
    | point(-0.7652, 0.2175, 0.6060)   | black |\n");
	t_point	p;
	t_color c;
	t_uv_ptrn checkers = uv_checkers(16, 8, black, white);
	t_pattern pattern = texture_map(checkers, spherical_map);
	printf("\n");
	printf("1:\n");
	p = point(0.4315, 0.4670, 0.7719);
	c = pattern_at(pattern, p);
	print_color(c);
	printf("\n");
	printf("2:\n");
	p = point(-0.9654, 0.2552, -0.0534);
	c = pattern_at(pattern, p);
	print_color(c);
	printf("\n");
	printf("3:\n");
	p = point(0.1039, 0.7090, 0.6975);
	c = pattern_at(pattern, p);
	print_color(c);
	printf("\n");
	printf("4:\n");
	p = point(-0.4986, -0.7856, -0.3663);
	c = pattern_at(pattern, p);
	print_color(c);
	printf("\n");
	printf("5:\n");
	p = point(-0.0317, -0.9395, 0.3411);
	c = pattern_at(pattern, p);
	print_color(c);
	printf("\n");
	printf("6:\n");
	p = point(0.4809, -0.7721, 0.4154);
	c = pattern_at(pattern, p);
	print_color(c);
	printf("\n");
	printf("7:\n");
	p = point(0.0285, -0.9612, -0.2745);
	c = pattern_at(pattern, p);
	print_color(c);
	printf("\n");
	printf("8:\n");
	p = point(-0.5734, -0.2162, -0.7903);
	c = pattern_at(pattern, p);
	print_color(c);
	printf("\n");
	printf("9:\n");
	p = point(0.7688, -0.1470, 0.6223);
	c = pattern_at(pattern, p);
	print_color(c);
	printf("\n");
	printf("10:\n");
	p = point(-0.7652, 0.2175, 0.6060);
	c = pattern_at(pattern, p);
	print_color(c);
}

static void	test4()
{
	printf("TEST 4:\n");
	printf("Scenario Outline: Using a planar mapping on a 3D point\n\
  Given p ← <point>\n\
  When (u, v) ← planar_map(p)\n\
  Then u = <u>\n\
    And v = <v>\n\
  Examples:\n\
    | point                   | u    | v    |\n\
    | point(0.25, 0, 0.5)     | 0.25 | 0.5  |\n\
    | point(0.25, 0, -0.25)   | 0.25 | 0.75 |\n\
    | point(0.25, 0.5, -0.25) | 0.25 | 0.75 |\n\
    | point(1.25, 0, 0.5)     | 0.25 | 0.5  |\n\
    | point(0.25, 0, -1.75)   | 0.25 | 0.25 |\n\
    | point(1, 0, -1)         | 0.0  | 0.0  |\n\
    | point(0, 0, 0)          | 0.0  | 0.0  |\n");
	t_point	p;
	t_uv_map	uv;
	printf("1:\n");
	p = point(0.25, 0, 0.5);
	uv = planar_map(p);
	print_uv_map(uv);
	printf("\n");
	printf("2:\n");
	p = point(0.25, 0, -0.25);
	uv = planar_map(p);
	print_uv_map(uv);
	printf("\n");
	printf("3:\n");
	p = point(0.25, 0.5, -0.25);
	uv = planar_map(p);
	print_uv_map(uv);
	printf("\n");
	printf("4:\n");
	p = point(1.25, 0, 0.5);
	uv = planar_map(p);
	print_uv_map(uv);
	printf("\n");
	printf("5:\n");
	p = point(0.25, 0, -1.75);
	uv = planar_map(p);
	print_uv_map(uv);
	printf("\n");
	printf("6:\n");
	p = point(1, 0, -1);
	uv = planar_map(p);
	print_uv_map(uv);
	printf("\n");
	printf("7:\n");
	p = point(0, 0, 0);
	uv = planar_map(p);
	print_uv_map(uv);
}

static void	test5()
{
	printf("TEST 5:\n");
	printf("Scenario Outline: Using a cylindrical mapping on a 3D point\n\
  Given p ← <point>\n\
  When (u, v) ← cylindrical_map(p)\n\
  Then u = <u>\n\
    And v = <v>\n\
  Examples:\n\
    | point                          | u     | v    |\n\
    | point(0, 0, -1)                | 0.0   | 0.0  |\n\
    | point(0, 0.5, -1)              | 0.0   | 0.5  |\n\
    | point(0, 1, -1)                | 0.0   | 0.0  |\n\
    | point(0.70711, 0.5, -0.70711)  | 0.125 | 0.5  |\n\
    | point(1, 0.5, 0)               | 0.25  | 0.5  |\n\
    | point(0.70711, 0.5, 0.70711)   | 0.375 | 0.5  |\n\
    | point(0, -0.25, 1)             | 0.5   | 0.75 |\n\
    | point(-0.70711, 0.5, 0.70711)  | 0.625 | 0.5  |\n\
    | point(-1, 1.25, 0)             | 0.75  | 0.25 |\n\
    | point(-0.70711, 0.5, -0.70711) | 0.875 | 0.5  |\n");
	t_point	p;
	t_uv_map	uv;
	printf("1:\n");
	p = point(0, 0, -1);
	uv = cylindrical_map(p);
	print_uv_map(uv);
	printf("\n");
	printf("2:\n");
	p = point(0, 0.5, -1);
	uv = cylindrical_map(p);
	print_uv_map(uv);
	printf("\n");
	printf("3:\n");
	p = point(0, 1, -1);
	uv = cylindrical_map(p);
	print_uv_map(uv);
	printf("\n");
	printf("4:\n");
	p = point(0.70711, 0.5, -0.70711);
	uv = cylindrical_map(p);
	print_uv_map(uv);
	printf("\n");
	printf("5:\n");
	p = point(1, 0.5, 0);
	uv = cylindrical_map(p);
	print_uv_map(uv);
	printf("\n");
	printf("6:\n");
	p = point(0.70711, 0.5, 0.70711);
	uv = cylindrical_map(p);
	print_uv_map(uv);
	printf("\n");
	printf("7:\n");
	p = point(0, -0.25, 1);
	uv = cylindrical_map(p);
	print_uv_map(uv);
	printf("\n");
	printf("8:\n");
	p = point(-0.70711, 0.5, 0.70711);
	uv = cylindrical_map(p);
	print_uv_map(uv);
	printf("\n");
	printf("9:\n");
	p = point(-1, 1.25, 0);
	uv = cylindrical_map(p);
	print_uv_map(uv);
	printf("\n");
	printf("10:\n");
	p = point(-0.70711, 0.5, -0.70711);
	uv = cylindrical_map(p);
	print_uv_map(uv);
}

static void	test6()
{
	printf("TEST 6:\n");
	printf("Scenario Outline: Layout of the align check pattern\n\
  Given main ← color(1, 1, 1)\n\
    And ul ← color(1, 0, 0)\n\
    And ur ← color(1, 1, 0)\n\
    And bl ← color(0, 1, 0)\n\
    And br ← color(0, 1, 1)\n\
    And pattern ← uv_align_check(main, ul, ur, bl, br)\n\
  When c ← uv_pattern_at(pattern, <u>, <v>)\n\
  Then c = <expected>\n\
  Examples:\n\
    | u    | v    | expected |\n\
    | 0.5  | 0.5  | main     |\n\
    | 0.1  | 0.9  | ul       |\n\
    | 0.9  | 0.9  | ur       |\n\
    | 0.1  | 0.1  | bl       |\n\
    | 0.9  | 0.1  | br       |\n");
	t_color c;
	// t_uv_align a;
	// a.main = color(1, 1, 1);
	// a.ul = color(1, 0, 0);
	// a.ur = color(1, 1, 0);
	// a.bl = color(0, 1, 0);
	// a.br = color(0, 1, 1);
	t_uv_ptrn pattern = uv_align_check();
	printf("1:\n");
	c = uv_pattern_at(pattern, 0.5, 0.5);
	print_color(c);
	printf("2:\n");
	c = uv_pattern_at(pattern, 0.1, 0.9);
	print_color(c);
	printf("3:\n");
	c = uv_pattern_at(pattern, 0.9, 0.9);
	print_color(c);
	printf("4:\n");
	c = uv_pattern_at(pattern, 0.1, 0.1);
	print_color(c);
	printf("5:\n");
	c = uv_pattern_at(pattern, 0.9, 0.1);
	print_color(c);
}

void	test_uv_patterns(void)
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
	printf("--------- TESTING PATTERNS FINISHED ---------\n");
	printf("\n");
}

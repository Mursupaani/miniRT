/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_uv_patterns.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 13:28:59 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/26 23:17:06 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	t_color c = uv_pattern_at(pattern, u, v, 0);
	printf("\n");
	print_color(c);
	u = 0.5;
	v = 0;
	c = uv_pattern_at(pattern, u, v, 0);
	printf("\n");
	print_color(c);
	u = 0;
	v = 0.5;
	c = uv_pattern_at(pattern, u, v, 0);
	printf("\n");
	print_color(c);
	u = 0.5;
	v = 0.5;
	c = uv_pattern_at(pattern, u, v, 0);
	printf("\n");
	print_color(c);
	u = 1;
	v = 1;
	c = uv_pattern_at(pattern, u, v, 0);
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
	t_uv_ptrn pattern = uv_align_check_pattern();
	printf("1:\n");
	c = uv_pattern_at(pattern, 0.5, 0.5, 0);
	print_color(c);
	printf("2:\n");
	c = uv_pattern_at(pattern, 0.1, 0.9, 0);
	print_color(c);
	printf("3:\n");
	c = uv_pattern_at(pattern, 0.9, 0.9, 0);
	print_color(c);
	printf("4:\n");
	c = uv_pattern_at(pattern, 0.1, 0.1, 0);
	print_color(c);
	printf("5:\n");
	c = uv_pattern_at(pattern, 0.9, 0.1, 0);
	print_color(c);
}

static void	test7()
{
	printf("TEST 7:\n");
	printf("Scenario Outline: Identifying the face of a cube from a point\n\
  When face ← face_from_point(<point>)\n\
  Then face = <face>\n\
  Examples:\n\
    | point                  | face  |\n\
    | point(-1, 0.5, -0.25)  | left  |\n\
    | point(1.1, -0.75, 0.8) | right |\n\
    | point(0.1, 0.6, 0.9)   | front |\n\
    | point(-0.7, 0, -2)     | back  |\n\
    | point(0.5, 1, 0.9)     | up    |\n\
    | point(-0.2, -1.3, 1.1) | down  |\n");
	t_point p;
	t_cube_face face;
	printf("1:\n");
	p = point(-1, 0.5, -0.25);
	face = face_from_point(p);
	if (face == LEFT)
		printf("PASS\n");
	else
		printf("FAIL\n");
	printf("2:\n");
	p = point(1.1, -0.75, 0.8);
	face = face_from_point(p);
	if (face == RIGHT)
		printf("PASS\n");
	else
		printf("FAIL\n");
	printf("3:\n");
	p = point(0.1, 0.6, 0.9);
	face = face_from_point(p);
	if (face == FRONT)
		printf("PASS\n");
	else
		printf("FAIL\n");
	printf("4:\n");
	p = point(-0.7, 0, -2);
	face = face_from_point(p);
	if (face == BACK)
		printf("PASS\n");
	else
		printf("FAIL\n");
	printf("5:\n");
	p = point(0.5, 1, 0.9);
	face = face_from_point(p);
	if (face == UP)
		printf("PASS\n");
	else
		printf("FAIL\n");
	printf("6:\n");
	p = point(-0.2, -1.3, 1.1);
	face = face_from_point(p);
	if (face == DOWN)
		printf("PASS\n");
	else
		printf("FAIL\n");
}

static void	test8()
{
	printf("TEST 8:\n");
	printf("Scenario Outline: UV mapping the front face of a cube\n\
  When (u, v) ← cube_uv_front(<point>)\n\
  Then u = <u>\n\
    And v = <v>\n\
\n\
  Examples:\n\
    | point                | u    | v    |\n\
    | point(-0.5, 0.5, 1)  | 0.25 | 0.75 |\n\
    | point(0.5, -0.5, 1)  | 0.75 | 0.25 |\n\
\n\
Scenario Outline: UV mapping the back face of a cube\n\
  When (u, v) ← cube_uv_back(<point>)\n\
  Then u = <u>\n\
    And v = <v>\n\
\n\
  Examples:\n\
    | point                 | u    | v    |\n\
    | point(0.5, 0.5, -1)   | 0.25 | 0.75 |\n\
    | point(-0.5, -0.5, -1) | 0.75 | 0.25 |\n\
\n\
Scenario Outline: UV mapping the left face of a cube\n\
  When (u, v) ← cube_uv_left(<point>)\n\
  Then u = <u>\n\
    And v = <v>\n\
\n\
  Examples:\n\
    | point                | u    | v    |\n\
    | point(-1, 0.5, -0.5) | 0.25 | 0.75 |\n\
    | point(-1, -0.5, 0.5) | 0.75 | 0.25 |\n\
\n\
Scenario Outline: UV mapping the right face of a cube\n\
  When (u, v) ← cube_uv_right(<point>)\n\
  Then u = <u>\n\
    And v = <v>\n\
\n\
  Examples:\n\
    | point                | u    | v    |\n\
    | point(1, 0.5, 0.5)   | 0.25 | 0.75 |\n\
    | point(1, -0.5, -0.5) | 0.75 | 0.25 |\n\
\n\
Scenario Outline: UV mapping the upper face of a cube\n\
  When (u, v) ← cube_uv_up(<point>)\n\
  Then u = <u>\n\
    And v = <v>\n\
\n\
  Examples:\n\
    | point               | u    | v    |\n\
    | point(-0.5, 1, -0.5) | 0.25 | 0.75 |\n\
    | point(0.5, 1, 0.5) | 0.75 | 0.25 |\n\
\n\
Scenario Outline: UV mapping the lower face of a cube\n\
  When (u, v) ← cube_uv_down(<point>)\n\
  Then u = <u>\n\
    And v = <v>\n\
\n\
  Examples:\n\
    | point                 | u    | v    |\n\
    | point(-0.5, -1, 0.5) | 0.25 | 0.75 |\n\
    | point(0.5, -1, -0.5)   | 0.75 | 0.25 |\n");
	t_point p;
	t_uv_map uv;
	printf("\n");
	printf("front 1:\n");
	p = point(-0.5, 0.5, 1);
	uv = cube_uv_front(p);
	print_uv_map(uv);
	printf("\n");
	printf("front 2:\n");
	p = point(0.5, -0.5, 1);
	uv = cube_uv_front(p);
	print_uv_map(uv);
	printf("\n");
	printf("back 1:\n");
	p = point(0.5, 0.5, -1);
	uv = cube_uv_back(p);
	print_uv_map(uv);
	printf("\n");
	printf("back 2:\n");
	p = point(-0.5, -0.5, -1);
	uv = cube_uv_back(p);
	print_uv_map(uv);
	printf("\n");
	printf("left 1:\n");
	p = point(-1, 0.5, -0.5);
	uv = cube_uv_left(p);
	print_uv_map(uv);
	printf("\n");
	printf("left 2:\n");
	p = point(-1, -0.5, 0.5);
	uv = cube_uv_left(p);
	print_uv_map(uv);
	printf("\n");
	printf("right 1:\n");
	p = point(1, 0.5, 0.5);
	uv = cube_uv_right(p);
	print_uv_map(uv);
	printf("\n");
	printf("right 2:\n");
	p = point(1, -0.5, -0.5);
	uv = cube_uv_right(p);
	print_uv_map(uv);
	printf("\n");
	printf("up 1:\n");
	p = point(-0.5, 1, -0.5);
	uv = cube_uv_up(p);
	print_uv_map(uv);
	printf("\n");
	printf("up 2:\n");
	p = point(0.5, 1, 0.5);
	uv = cube_uv_up(p);
	print_uv_map(uv);
	printf("\n");
	printf("down 1:\n");
	p = point(-0.5, -1, 0.5);
	uv = cube_uv_down(p);
	print_uv_map(uv);
	printf("\n");
	printf("down 2:\n");
	p = point(0.5, -1, -0.5);
	uv = cube_uv_down(p);
	print_uv_map(uv);
}

static void	test9()
{
	printf("TEST 9:\n");
	printf("Scenario Outline: Finding the colors on a mapped cube\n\
  When red ← color(1, 0, 0)\n\
    And yellow ← color(1, 1, 0)\n\
    And brown ← color(1, 0.5, 0)\n\
    And green ← color(0, 1, 0)\n\
    And cyan ← color(0, 1, 1)\n\
    And blue ← color(0, 0, 1)\n\
    And purple ← color(1, 0, 1)\n\
    And white ← color(1, 1, 1)\n\
    And left ← uv_align_check(yellow, cyan, red, blue, brown)\n\
    And front ← uv_align_check(cyan, red, yellow, brown, green)\n\
    And right ← uv_align_check(red, yellow, purple, green, white)\n\
    And back ← uv_align_check(green, purple, cyan, white, blue)\n\
    And up ← uv_align_check(brown, cyan, purple, red, yellow)\n\
    And down ← uv_align_check(purple, brown, green, blue, white)\n\
    And pattern ← cube_map(left, front, right, back, up, down)\n\
  Then pattern_at(pattern, <point>) = <color>\n");
	t_color red = color(1, 0, 0);
	t_color yellow = color(1, 1, 0);
	t_color brown = color(1, 0.5, 0);
	t_color green = color(0, 1, 0);
	t_color cyan = color(0, 1, 1);
	t_color blue = color(0, 0, 1);
	t_color purple = color(1, 0, 1);
	t_color white = color(1, 1, 1);
	t_pattern cube_pattern;
	cube_pattern.type = MAP;
	cube_pattern.texture_map.pattern.type = UV_CUBE;
	cube_pattern.texture_map.pattern.sides[LEFT] = uv_align_check(yellow, cyan, red, blue, brown);
	cube_pattern.texture_map.pattern.sides[FRONT] = uv_align_check(cyan, red, yellow, brown, green);
	cube_pattern.texture_map.pattern.sides[RIGHT] = uv_align_check(red, yellow, purple, green, white);
	cube_pattern.texture_map.pattern.sides[BACK] = uv_align_check(green, purple, cyan, white, blue);
	cube_pattern.texture_map.pattern.sides[UP] = uv_align_check(brown, cyan, purple, red, yellow);
	cube_pattern.texture_map.pattern.sides[DOWN] = uv_align_check(purple, brown, green, blue, white);
	t_point	p;
	t_color	c;
	printf("\n");
	printf("L 1:\n");
	p = point(-1, 0, 0);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("L 2:\n");
	p = point(-1, 0.9, -0.9);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("L 3:\n");
	p = point(-1, 0.9, 0.9);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("L 4:\n");
	p = point(-1, -0.9, -0.9);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("L 5:\n");
	p = point(-1, -0.9, 0.9);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("F 1:\n");
	p = point(0, 0, 1);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("F 2:\n");
	p = point(-0.9, 0.9, 1);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("F 3:\n");
	p = point(0.9, 0.9, 1);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("F 4:\n");
	p = point(-0.9, -0.9, 1);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("F 5:\n");
	p = point(0.9, -0.9, 1);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("R 1:\n");
	p = point(1, 0, 0);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("R 2:\n");
	p = point(1, 0.9, 0.9);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("R 3:\n");
	p = point(1, 0.9, -0.9);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("R 4:\n");
	p = point(1, -0.9, 0.9);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("R 5:\n");
	p = point(1, -0.9, -0.9);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("B 1:\n");
	p = point(0, 0, -1);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("B 2:\n");
	p = point(0.9, 0.9, -1);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("B 3:\n");
	p = point(-0.9, 0.9, -1);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("B 4:\n");
	p = point(0.9, -0.9, -1);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("B 5:\n");
	p = point(-0.9, -0.9, -1);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("U 1:\n");
	p = point(0, 1, 0);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("U 2:\n");
	p = point(-0.9, 1, -0.9);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("U 3:\n");
	p = point(0.9, 1, -0.9);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("U 4:\n");
	p = point(-0.9, 1, 0.9);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("U 5:\n");
	p = point(0.9, 1, 0.9);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("D 1:\n");
	p = point(0, -1, 0);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("D 2:\n");
	p = point(-0.9, -1, 0.9);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("D 3:\n");
	p = point(0.9, -1, 0.9);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("D 4:\n");
	p = point(-0.9, -1, -0.9);
	c = pattern_at(cube_pattern, p);
	print_color(c);
	printf("D 5:\n");
	p = point(0.9, -1, -0.9);
	c = pattern_at(cube_pattern, p);
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
	test7();
	printf("_____________________________________________\n");
	test8();
	printf("_____________________________________________\n");
	test9();
	printf("_____________________________________________\n");
	printf("--------- TESTING PATTERNS FINISHED ---------\n");
	printf("\n");
}

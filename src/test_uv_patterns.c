/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_uv_patterns.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 13:28:59 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/25 18:33:16 by anpollan         ###   ########.fr       */
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
	print_uv_points(uv);
	p = point(1, 0 ,0);
	uv = spherical_map(p);
	print_uv_points(uv);
	p = point(0, 0 ,1);
	uv = spherical_map(p);
	print_uv_points(uv);
	p = point(-1, 0 ,0);
	uv = spherical_map(p);
	print_uv_points(uv);
	p = point(0, 1 ,0);
	uv = spherical_map(p);
	print_uv_points(uv);
	p = point(0, -1 ,0);
	uv = spherical_map(p);
	print_uv_points(uv);
	p = point(sqrt(2) / 2, sqrt(2) / 2 ,0);
	uv = spherical_map(p);
	print_uv_points(uv);
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
	printf("--------- TESTING PATTERNS FINISHED ---------\n");
	printf("\n");
}

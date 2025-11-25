/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tuples.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:37:36 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/24 18:23:31 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	test1(void)
{
	t_tuple		tuple1;
	t_tuple		tuple2;
	t_tuple		tuple3;

	printf("TEST 1:\n");
	printf("Scenario: Adding two tuples\n\
Given a1 ← tuple(3, -2, 5, 1)\n \
And a2 ← tuple(-2, 3, 1, 0)\n \
Then a1 + a2 = tuple(1, 1, 6, 1)\n");
	tuple1 = init_point(3, -2, 5);
	tuple2 = init_vector(-2, 3, 1);
	tuple3 = tuple_sum(tuple1, tuple2);
	print_tuple(tuple1);
	print_tuple(tuple2);
	print_tuple(tuple3);
}

static void	test2(void)
{
	t_tuple		tuple1;
	t_tuple		tuple2;
	t_tuple		tuple3;

	printf("TEST 2:\n");
	printf("Scenario: Subtracting two points\n\
Given p1 ← point(3, 2, 1)\n\
And p2 ← point(5, 6, 7)\n\
Then p1 - p2 = vector(-2, -4, -6)\n");
	tuple1 = init_point(3, 2, 1);
	tuple2 = init_point(5, 6, 7);
	tuple3 = tuple_subtract(tuple1, tuple2);
	print_tuple(tuple1);
	print_tuple(tuple2);
	print_tuple(tuple3);
}

static void	test3(void)
{
	t_tuple		tuple1;
	t_tuple		tuple2;
	t_tuple		tuple3;

	printf("TEST 3:\n");
	printf("Scenario: Subtracting two points\n\
Given p1 ← point(3, 2, 1)\n\
And p2 ← point(5, 6, 7)\n\
Then p1 - p2 = vector(-2, -4, -6)\n");
	tuple1 = init_point(3, 2, 1);
	tuple2 = init_point(5, 6, 7);
	tuple3 = tuple_subtract(tuple1, tuple2);
	print_tuple(tuple1);
	print_tuple(tuple2);
	print_tuple(tuple3);
}

static void	test4(void)
{
	t_tuple		tuple1;
	t_tuple		tuple2;
	t_tuple		tuple3;

	printf("TEST 4:\n");
	printf("Scenario: Subtracting two vectors\n\
Given v1 ← vector(3, 2, 1)\n\
And v2 ← vector(5, 6, 7)\n\
Then v1 - v2 = vector(-2, -4, -6)\n");
	tuple1 = init_vector(3, 2, 1);
	tuple2 = init_vector(5, 6, 7);
	tuple3 = tuple_subtract(tuple1, tuple2);
	print_tuple(tuple1);
	print_tuple(tuple2);
	print_tuple(tuple3);
}

static void	test5(void)
{
	t_tuple		tuple1;
	t_tuple		tuple2;

	printf("TEST 5:\n");
	printf("Scenario: Negating a tuple\n\
Given a ← tuple(1, -2, 3, -4)\n\
Then -a = tuple(-1, 2, -3, 4)\n");
	tuple1 = init_tuple(1, -2, 3, -4);
	tuple2 = tuple_negate(tuple1);
	print_tuple(tuple1);
	print_tuple(tuple2);
}

static void	test6(void)
{
	t_tuple		tuple1;
	t_tuple		tuple2;

	printf("TEST 6:\n");
	printf("Scenario: Multiplying a tuple by a fraction\n\
Given a ← tuple(1, -2, 3, -4)\n\
Then a * 0.5 = tuple(0.5, -1, 1.5, -2)\n");
	tuple1 = init_tuple(1, -2, 3, -4);
	tuple2 = tuple_scale_multiply(tuple1, 0.5);
	print_tuple(tuple1);
	print_tuple(tuple2);
}

static void	test7(void)
{
	t_tuple		tuple1;
	t_tuple		tuple2;

	printf("TEST 7:\n");
	printf("Scenario: Dividing a tuple by a scalar\n\
Given a ← tuple(1, -2, 3, -4)\n\
Then a / 2 = tuple(0.5, -1, 1.5, -2)\n");
	tuple1 = init_tuple(1, -2, 3, -4);
	tuple2 = tuple_scale_divide(tuple1, 2);
	print_tuple(tuple1);
	print_tuple(tuple2);
}

static void	test8(void)
{
	t_tuple		tuple1;

	printf("TEST 8:\n");
	printf("Scenario: Computing the magnitude of vector(1, 2, 3)\n\
Given v ← vector(1, 2, 3)\n\
Then magnitude(v) = %f\n", sqrtf(14));
	tuple1 = init_vector(1, 2, 3);
	print_tuple(tuple1);
}

static void	test9(void)
{
	t_tuple		tuple1;
	t_tuple		tuple2;

	printf("TEST 9:\n");
	printf("Scenario: Normalizing vector(4, 0, 0) gives (1, 0, 0)\n\
Given v ← vector(4, 0, 0)\n\
Then normalize(v) = vector(1, 0, 0)\n\
Then magnitude(norm) = 1\n");
	tuple1 = init_vector(4, 0, 0);
	tuple2 = vector_normalize(tuple1);
	print_tuple(tuple1);
	print_tuple(tuple2);
}

static void	test10(void)
{
	t_tuple		tuple1;
	t_tuple		tuple2;

	printf("TEST 10:\n");
	printf("Scenario: The dot product of two tuples\n\
Given a ← vector(1, 2, 3)\n\
And b ← vector(2, 3, 4)\n\
Then dot(a, b) = 20\n");
	tuple1 = init_vector(1, 2, 3);
	tuple2 = init_vector(2, 3, 4);
	print_tuple(tuple1);
	print_tuple(tuple2);
	printf("Dot product = %f\n", vector_dot_product(tuple1, tuple2));
}

static void	test11(void)
{
	t_tuple		tuple1;
	t_tuple		tuple2;
	t_tuple		tuple3;

	printf("TEST 11:\n");
	printf("Scenario: The cross product of two vectors\n\
Given a ← vector(1, 2, 3)\n\
And b ← vector(2, 3, 4)\n\
Then cross(a, b) = vector(-1, 2, -1)\n\
And cross(b, a) = vector(1, -2, 1)\n");
	tuple1 = init_vector(1, 2, 3);
	tuple2 = init_vector(2, 3, 4);
	print_tuple(tuple1);
	print_tuple(tuple2);
	tuple3 = vector_cross_product(tuple1, tuple2);
	print_tuple(tuple3);
	tuple3 = vector_cross_product(tuple2, tuple1);
	print_tuple(tuple3);
}

void	test_tuples(void)
{
	printf("\n");
	printf("--------------- TESTING TUPLES --------------\n");
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
	test10();
	printf("_____________________________________________\n");
	test11();
	printf("_____________________________________________\n");
	printf("---------- TESTING TUPLES FINISHED ----------\n");
	printf("\n");
}

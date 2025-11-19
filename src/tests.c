/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:37:36 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/19 16:01:55 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	test1(void)
{
	t_tuple		*tuple1;
	t_tuple		*tuple2;
	t_tuple		*tuple3;

	printf("TEST 1:\n");
	printf("Scenario: Adding two tuples\n\
Given a1 ← tuple(3, -2, 5, 1)\n \
And a2 ← tuple(-2, 3, 1, 0)\n \
Then a1 + a2 = tuple(1, 1, 6, 1)\n");
	tuple1 = new_vector(3, -2, 5);
	tuple2 = new_point(-2, 3, 1);
	tuple3 = tuple_sum(tuple1, tuple2);
	print_tuple(tuple1);
	print_tuple(tuple2);
	print_tuple(tuple3);
	free(tuple1);
	free(tuple2);
	free(tuple3);
}

void	test2(void)
{
	t_tuple		*tuple1;
	t_tuple		*tuple2;
	t_tuple		*tuple3;

	printf("TEST 2:\n");
	printf("Scenario: Subtracting two points\n\
Given p1 ← point(3, 2, 1)\n\
And p2 ← point(5, 6, 7)\n\
Then p1 - p2 = vector(-2, -4, -6)\n");
	tuple1 = new_point(3, 2, 1);
	tuple2 = new_point(5, 6, 7);
	tuple3 = tuple_subtract(tuple1, tuple2);
	print_tuple(tuple1);
	print_tuple(tuple2);
	print_tuple(tuple3);
	free(tuple1);
	free(tuple2);
	free(tuple3);
}

void	test3(void)
{
	t_tuple		*tuple1;
	t_tuple		*tuple2;
	t_tuple		*tuple3;

	printf("TEST 3:\n");
	printf("Scenario: Subtracting two points\n\
Given p1 ← point(3, 2, 1)\n\
And p2 ← point(5, 6, 7)\n\
Then p1 - p2 = vector(-2, -4, -6)\n");
	tuple1 = new_point(3, 2, 1);
	tuple2 = new_vector(5, 6, 7);
	tuple3 = tuple_subtract(tuple1, tuple2);
	print_tuple(tuple1);
	print_tuple(tuple2);
	print_tuple(tuple3);
	free(tuple1);
	free(tuple2);
	free(tuple3);
}

void	test4(void)
{
	t_tuple		*tuple1;
	t_tuple		*tuple2;
	t_tuple		*tuple3;

	printf("TEST 4:\n");
	printf("Scenario: Subtracting two vectors\n\
Given v1 ← vector(3, 2, 1)\n\
And v2 ← vector(5, 6, 7)\n\
Then v1 - v2 = vector(-2, -4, -6)\n");
	tuple1 = new_vector(3, 2, 1);
	tuple2 = new_vector(5, 6, 7);
	tuple3 = tuple_subtract(tuple1, tuple2);
	print_tuple(tuple1);
	print_tuple(tuple2);
	print_tuple(tuple3);
	free(tuple1);
	free(tuple2);
	free(tuple3);
}

void	test_tuples(void)
{
	test1();
	printf("\n");
	test2();
	printf("\n");
	test3();
	printf("\n");
	test4();
	printf("\n");
}

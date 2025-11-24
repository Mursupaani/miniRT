/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_transformation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:02:03 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/24 12:40:46 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	test1(void)
{
	t_point	*point;
	t_point	*result;
	float	(*transform)[4];

	printf("TEST 1:\n");
	printf("Scenario: Multiplying by a translation matrix\n\
Given transform ← translation(5, -3, 2)\n\
And p ← point(-3, 4, 5)\n\
Then transform * p = point(2, 1, 7)\n");
	point = new_point(-3, 4, 5);
	print_tuple(point);
	transform = new_translation_matrix4(5, -3, 2);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, point);
	print_tuple(result);
	free(point);
	free(result);
	free(transform);
}

static void	test2(void)
{
	t_point	*point;
	t_point	*result;
	float	(*transform)[4];
	float	(*invert)[4];

	printf("TEST 2:\n");
	printf("Scenario: Multiplying by the inverse of a translation matrix\n\
Given transform ← translation(5, -3, 2)\n\
And inv ← inverse(transform)\n\
And p ← point(-3, 4, 5)\n\
Then inv * p = point(-8, 7, 3)\n");
	point = new_point(-3, 4, 5);
	print_tuple(point);
	transform = new_translation_matrix4(5, -3, 2);
	print_matrix4(transform);
	invert = matrix4_invert(transform);
	result = matrix4_and_tuple_multiply(invert, point);
	print_tuple(result);
	free(point);
	free(result);
	free(transform);
	free(invert);
}

static void	test3(void)
{
	t_point	*vector;
	t_point	*result;
	float	(*transform)[4];

	printf("TEST 3:\n");
	printf("Scenario: Translation does not affect vectors\n\
Given transform ← translation(5, -3, 2)\n\
And v ← vector(-3, 4, 5)\n\
Then transform * v = v\n");
	vector = new_vector(5, -3, 2);
	print_tuple(vector);
	transform = new_translation_matrix4(-3, 4, 5);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, vector);
	print_tuple(result);
	free(vector);
	free(result);
	free(transform);
}

static void	test4(void)
{
	t_point	*point;
	t_point	*result;
	float	(*transform)[4];

	printf("TEST 4:\n");
	printf("Scenario: A scaling matrix applied to a point\n\
Given transform ← scaling(2, 3, 4)\n\
And p ← point(-4, 6, 8)\n\
Then transform * p = point(-8, 18, 32)\n");
	point = new_point(-4, 6, 8);
	print_tuple(point);
	transform = new_scaling_matrix4(2, 3, 4);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, point);
	print_tuple(result);
	free(point);
	free(result);
	free(transform);
}

static void	test5(void)
{
	t_vector	*vector;
	t_point		*result;
	float		(*transform)[4];

	printf("TEST 5:\n");
	printf("Scenario: A scaling matrix applied to a vector\n\
Given transform ← scaling(2, 3, 4)\n\
And v ← vector(-4, 6, 8)\n\
Then transform * v = vector(-8, 18, 32)\n");
	vector = new_vector(-4, 6, 8);
	print_tuple(vector);
	transform = new_scaling_matrix4(2, 3, 4);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, vector);
	print_tuple(result);
	free(vector);
	free(result);
	free(transform);
}

static void	test6(void)
{
	t_vector	*vector;
	t_point		*result;
	float		(*transform)[4];
	float		(*inverse)[4];

	printf("TEST 6:\n");
	printf("Scenario: Multiplying by the inverse of a scaling matrix\n\
Given transform ← scaling(2, 3, 4)\n\
And inv ← inverse(transform)\n\
And v ← vector(-4, 6, 8)\n\
Then inv * v = vector(-2, 2, 2)\n");
	vector = new_vector(-4, 6, 8);
	print_tuple(vector);
	transform = new_scaling_matrix4(2, 3, 4);
	print_matrix4(transform);
	inverse = matrix4_invert(transform);
	print_matrix4(inverse);
	result = matrix4_and_tuple_multiply(inverse, vector);
	print_tuple(result);
	free(vector);
	free(result);
	free(transform);
	free(inverse);
}

static void	test7(void)
{
	t_vector	*point;
	t_point		*result;
	float		(*transform)[4];

	printf("TEST 7:\n");
	printf("Scenario: Reflection is scaling by a negative value\n\
Given transform ← scaling(-1, 1, 1)\n\
And p ← point(2, 3, 4)\n\
Then transform * p = point(-2, 3, 4)\n");
	point = new_point(2, 3, 4);
	print_tuple(point);
	transform = new_scaling_matrix4(-1, 1, 1);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, point);
	print_tuple(result);
	free(point);
	free(result);
	free(transform);
}

static void	test8(void)
{
	t_vector	*point;
	t_point		*result;
	float		(*transform)[4];

	printf("TEST 8:\n");
	printf("Scenario: Rotating a point around the x axis\n\
Given p ← point(0, 1, 0)\n\
And half_quarter← rotation_x(π / 4)\n\
And full_quarter← rotation_x(π / 2)\n\
Then half_quarter * p = point(0, √2/2, √2/2)\n\
And full_quarter * p = point(0, 0, 1)\n");
	point = new_point(0, 1, 0);
	print_tuple(point);
	transform = new_x_rotation_matrix4(M_PI / 4);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, point);
	print_tuple(result);
	free(result);
	free(transform);
	transform = new_x_rotation_matrix4(M_PI / 2);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, point);
	print_tuple(result);
	free(point);
	free(result);
	free(transform);
}

static void	test9(void)
{
	t_vector	*point;
	t_point		*result;
	float		(*transform)[4];
	float		(*inverse)[4];

	printf("TEST 9:\n");
	printf("Scenario: The inverse of an x-rotation rotates in the opposite direction\n\
Given p ← point(0, 1, 0)\n\
And half_quarter← rotation_x(π / 4)\n\
And inv ← inverse(half_quarter)\n\
Then inv * p = point(0, √2/2, -√2/2)\n");
	point = new_point(0, 1, 0);
	print_tuple(point);
	transform = new_x_rotation_matrix4(M_PI / 4);
	print_matrix4(transform);
	inverse = matrix4_invert(transform);
	print_matrix4(inverse);
	result = matrix4_and_tuple_multiply(inverse, point);
	print_tuple(result);
	free(point);
	free(result);
	free(transform);
	free(inverse);
}


static void	test10(void)
{
	t_vector	*point;
	t_point		*result;
	float		(*transform)[4];

	printf("TEST 10:\n");
	printf("Scenario: Rotating a point around the y axis\n\
Given p ← point(0, 0, 1)\n\
And half_quarter← rotation_y(π / 4)\n\
And full_quarter← rotation_y(π / 2)\n\
Then half_quarter * p = point(√2/2, 0, √2/2)\n\
And full_quarter * p = point(1, 0, 0)\n");
	point = new_point(0, 0, 1);
	print_tuple(point);
	transform = new_y_rotation_matrix4(M_PI / 4);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, point);
	print_tuple(result);
	free(result);
	free(transform);
	transform = new_y_rotation_matrix4(M_PI / 2);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, point);
	print_tuple(result);
	free(point);
	free(result);
	free(transform);
}

static void	test11(void)
{
	t_vector	*point;
	t_point		*result;
	float		(*transform)[4];

	printf("TEST 11:\n");
	printf("Scenario: Rotating a point around the z axis\n\
Given p ← point(0, 1, 0)\n\
And half_quarter← rotation_z(π / 4)\n\
And full_quarter← rotation_z(π / 2)\n\
Then half_quarter * p = point(-√2/2, √2/2, 0)\n\
And full_quarter * p = point(-1, 0, 0)\n");
	point = new_point(0, 1, 0);
	print_tuple(point);
	transform = new_z_rotation_matrix4(M_PI / 4);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, point);
	print_tuple(result);
	free(result);
	free(transform);
	transform = new_z_rotation_matrix4(M_PI / 2);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, point);
	print_tuple(result);
	free(point);
	free(result);
	free(transform);
}

void	test_transformation(void)
{
	printf("\n");
	printf("------------- TESTING MATRICES --------------\n");
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
	printf("---------- TESTING MATRICES FINISHED --------\n");
	printf("\n");
}

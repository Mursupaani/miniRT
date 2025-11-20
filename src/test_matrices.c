/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_matrices.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:49:23 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/20 16:21:55 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

	float	identity[4][4];
	float	m1[4][4];
	float	m2[4][4];
	float	m3[4][4];
	float	m4[4][4];
	float	m5[4][4];
	float	m6[4][4];

static void	init_matrices(void);

static void	test1(void)
{
	printf("TEST 1:\n");
	printf("Scenario: Matrix equality with identical matrices\n\
Given the following matrix A:\n\
| 1 | 2 | 3 | 4 |\n\
| 5 | 6 | 7 | 8 |\n\
| 9 | 8 | 7 | 6 |\n\
| 5 | 4 | 3 | 2 |\n\
And the following matrix B:\n\
| 1 | 2 | 3 | 4 |\n\
| 5 | 6 | 7 | 8 |\n\
| 9 | 8 | 7 | 6 |\n\
| 5 | 4 | 3 | 2 |\n\
Then A = B\n");
	print_matrix4(m1);
	print_matrix4(m2);
	printf("Matrices are equal = %s\n", matrix4s_are_equal(m1, m2) ? "true" : "false");
}

static void	test2(void)
{
	printf("TEST 2:\n");
	printf("Scenario: Matrix equality with different matrices\n\
Given the following matrix A:\n\
| 1 | 2 | 3 | 4 |\n\
| 5 | 6 | 7 | 8 |\n\
| 9 | 8 | 7 | 6 |\n\
| 5 | 4 | 3 | 2 |\n\
And the following matrix B:\n\
| 2 | 3 | 4 | 5 |\n\
| 6 | 7 | 8 | 9 |\n\
| 8 | 7 | 6 | 5 |\n\
| 4 | 3 | 2 | 1 |\n\
Then A != B\n");
	print_matrix4(m1);
	print_matrix4(m3);
	printf("Matrices are equal = %s\n", matrix4s_are_equal(m1, m3) ? "true" : "false");
}

static void	test3(void)
{
	float (*result)[4];

	printf("TEST 3:\n");
	printf("Scenario: Multiplying two matrices\n\
Given the following matrix A:\n\
| 1 | 2 | 3 | 4 |\n\
| 5 | 6 | 7 | 8 |\n\
| 9 | 8 | 7 | 6 |\n\
| 5 | 4 | 3 | 2 |\n\
And the following matrix B:\n\
| -2 | 1 | 2 | 3 |\n\
| 3 | 2 | 1 | -1 |\n\
| 4 | 3 | 6 | 5 |\n\
| 1 | 2 | 7 | 8 |\n\
Then A * B is the following 4x4 matrix:\n\
| 20| 22 | 50 | 48 |\n\
| 44| 54 | 114 | 108 |\n\
| 40| 58 | 110 | 102 |\n\
| 16| 26 | 46 | 42 |\n");
	print_matrix4(m1);
	print_matrix4(m3);
	result = matrix4_multiply(m1, m4);
	print_matrix4(result);
	free(result);
}

static void	test4(void)
{
	t_tuple	*tuple;
	t_tuple	*result;

	printf("TEST 4:\n");
	printf("Scenario: A matrix multiplied by a tuple\n\
Given the following matrix A:\n\
| 1 | 2 | 3 | 4 |\n\
| 2 | 4 | 4 | 2 |\n\
| 8 | 6 | 4 | 1 |\n\
| 0 | 0 | 0 | 1 |\n\
And b ← tuple(1, 2, 3, 1)\n\
Then A * b = tuple(18, 24, 33, 1)\n");
	tuple = new_tuple(1, 2, 3, 1);
	result = matrix4_and_tuple_multiply(m5, tuple);
	print_matrix4(m1);
	print_tuple(tuple);
	print_tuple(result);
	free(tuple);
	free(result);
}

static void	test5(void)
{
	float (*result)[4];

	printf("TEST 5:\n");
	printf("Scenario: Multiplying a matrix by the identity matrix\n\
Given the following matrix A:\n\
| 0 | 1 | 2 | 4 |\n\
| 1 | 2 | 4 | 8 |\n\
| 2 | 4 | 8 | 16 |\n\
| 4 | 8 | 16 | 32 |\n\
Then A * identity_matrix = A\n\
Scenario: Multiplying the identity matrix by a tuple\n\
Given a ← tuple(1, 2, 3, 4)\n\
Then identity_matrix * a = a\n");
	print_matrix4(m1);
	print_matrix4(identity);
	result = matrix4_multiply(m1, identity);
	print_matrix4(result);
	free(result);
}

static void	test6(void)
{
	float (*result)[4];

	printf("TEST 6:\n");
	printf("Scenario: Transposing a matrix\n\
Given the following matrix A:\n\
| 0 | 9 | 3 | 0 |\n\
| 9 | 8 | 0 | 8 |\n\
| 1 | 8 | 5 | 3 |\n\
| 0 | 0 | 5 | 8 |\n\
Then transpose(A) is the following matrix:\n\
| 0 | 9 | 1 | 0 |\n\
| 9 | 8 | 8 | 0 |\n\
| 3 | 0 | 5 | 5 |\n\
| 0 | 8 | 3 | 8 |\n");
	print_matrix4(m6);
	result = matrix4_transpose(m6);
	print_matrix4(result);
	free(result);
}

void	test_matrices(void)
{
	init_matrices();
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
	printf("---------- TESTING MATRICES FINISHED --------\n");
	printf("\n");
}

static void	init_matrices(void)
{
	identity[0][0] = 1;
	identity[0][1] = 0;
	identity[0][2] = 0;
	identity[0][3] = 0;
	identity[1][0] = 0;
	identity[1][1] = 1;
	identity[1][2] = 0;
	identity[1][3] = 0;
	identity[2][0] = 0;
	identity[2][1] = 0;
	identity[2][2] = 1;
	identity[2][3] = 0;
	identity[3][0] = 0;
	identity[3][1] = 0;
	identity[3][2] = 0;
	identity[3][3] = 1;

	m1[0][0] = 1;
	m1[0][1] = 2;
	m1[0][2] = 3;
	m1[0][3] = 4;
	m1[1][0] = 5;
	m1[1][1] = 6;
	m1[1][2] = 7;
	m1[1][3] = 8;
	m1[2][0] = 9;
	m1[2][1] = 8;
	m1[2][2] = 7;
	m1[2][3] = 6;
	m1[3][0] = 5;
	m1[3][1] = 4;
	m1[3][2] = 3;
	m1[3][3] = 2;

	m2[0][0] = 1;
	m2[0][1] = 2;
	m2[0][2] = 3;
	m2[0][3] = 4;
	m2[1][0] = 5;
	m2[1][1] = 6;
	m2[1][2] = 7;
	m2[1][3] = 8;
	m2[2][0] = 9;
	m2[2][1] = 8;
	m2[2][2] = 7;
	m2[2][3] = 6;
	m2[3][0] = 5;
	m2[3][1] = 4;
	m2[3][2] = 3;
	m2[3][3] = 2;

	m3[0][0] = 2;
	m3[0][1] = 3;
	m3[0][2] = 4;
	m3[0][3] = 5;
	m3[1][0] = 6;
	m3[1][1] = 7;
	m3[1][2] = 8;
	m3[1][3] = 9;
	m3[2][0] = 8;
	m3[2][1] = 7;
	m3[2][2] = 6;
	m3[2][3] = 5;
	m3[3][0] = 4;
	m3[3][1] = 3;
	m3[3][2] = 2;
	m3[3][3] = 1;

	m4[0][0] = -2;
	m4[0][1] = 1;
	m4[0][2] = 2;
	m4[0][3] = 3;
	m4[1][0] = 3;
	m4[1][1] = 2;
	m4[1][2] = 1;
	m4[1][3] = -1;
	m4[2][0] = 4;
	m4[2][1] = 3;
	m4[2][2] = 6;
	m4[2][3] = 5;
	m4[3][0] = 1;
	m4[3][1] = 2;
	m4[3][2] = 7;
	m4[3][3] = 8;

	m5[0][0] = 1;
	m5[0][1] = 2;
	m5[0][2] = 3;
	m5[0][3] = 4;
	m5[1][0] = 2;
	m5[1][1] = 4;
	m5[1][2] = 4;
	m5[1][3] = 2;
	m5[2][0] = 8;
	m5[2][1] = 6;
	m5[2][2] = 4;
	m5[2][3] = 1;
	m5[3][0] = 0;
	m5[3][1] = 0;
	m5[3][2] = 0;
	m5[3][3] = 1;

	m6[0][0] = 0;
	m6[0][1] = 9;
	m6[0][2] = 3;
	m6[0][3] = 0;
	m6[1][0] = 9;
	m6[1][1] = 8;
	m6[1][2] = 0;
	m6[1][3] = 8;
	m6[2][0] = 1;
	m6[2][1] = 8;
	m6[2][2] = 5;
	m6[2][3] = 3;
	m6[3][0] = 0;
	m6[3][1] = 0;
	m6[3][2] = 5;
	m6[3][3] = 8;
}

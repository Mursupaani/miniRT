/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_matrices.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:49:23 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/20 19:10:24 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

	t_matrix4	identity;
	t_matrix4	m1;
	t_matrix4	m2;
	t_matrix4	m3;
	t_matrix4	m4;
	t_matrix4	m5;
	t_matrix4	m6;
	t_matrix4	m7;
	t_matrix4	m8;
	t_matrix4	m9;
	t_matrix4	m10;
	t_matrix4	m11;
	t_matrix4	m12;
	t_matrix4	m13;
	t_matrix2	m2by2;
	t_matrix3	m3by3;
	t_matrix3	m3by3_2;
	t_matrix3	m3by3_3;

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
	t_matrix4 result;

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
}

static void	test4(void)
{
	t_tuple	tuple;
	t_tuple	result;

	printf("TEST 4:\n");
	printf("Scenario: A matrix multiplied by a tuple\n\
Given the following matrix A:\n\
| 1 | 2 | 3 | 4 |\n\
| 2 | 4 | 4 | 2 |\n\
| 8 | 6 | 4 | 1 |\n\
| 0 | 0 | 0 | 1 |\n\
And b ← tuple(1, 2, 3, 1)\n\
Then A * b = tuple(18, 24, 33, 1)\n");
	tuple = init_tuple(1, 2, 3, 1);
	result = matrix4_and_tuple_multiply(m5, tuple);
	print_matrix4(m1);
	print_tuple(tuple);
	print_tuple(result);
}

static void	test5(void)
{
	t_matrix4 result;

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
}

static void	test6(void)
{
	t_matrix4 result;

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
}

static void	test7(void)
{
	printf("TEST 7:\n");
	printf("Scenario: Calculating the determinant of a 2x2 matrix\n\
Given the following 2x2 matrix A:\n\
| 1 | 5 |\n\
| -3 | 2 |\n\
Then determinant(A) = 17\n");
	print_matrix2(m2by2);
	printf("Determinant = %f\n", matrix2_determinant(m2by2));
}

static void	test8(void)
{
	t_matrix2 result;

	printf("TEST 8:\n");
	printf("Scenario: A submatrix of a 3x3 matrix is a 2x2 matrix\n\
Given the following 3x3 matrix A:\n\
| 1 | 5 | 0 |\n\
| -3 | 2 | 7 |\n\
| 0 | 6 | -3 |\n\
Then submatrix(A, 0, 2) is the following 2x2 matrix:\n\
| -3 | 2 |\n\
| 0 | 6 |");
	print_matrix3(m3by3);
	result = matrix3_submatrix(m3by3, 0, 2);
	print_matrix2(result);
}

static void	test9(void)
{
	t_matrix3 result;

	printf("TEST 9:\n");
	printf("Scenario: A submatrix of a 4x4 matrix is a 3x3 matrix\n\
Given the following 4x4 matrix A:\n\
| -6 | 1 | 1 | 6 |\n\
| -8 | 5 | 8 | 6 |\n\
| -1 | 0 | 8 | 2 |\n\
| -7 | 1 | -1 | 1 |\n\
Then submatrix(A, 2, 1) is the following 3x3 matrix:\n\
| -6 | 1 | 6 |\n\
| -8 | 8 | 6 |\n\
| -7 | -1 | 1 |\n");
	print_matrix4(m7);
	result = matrix4_submatrix(m7, 2, 1);
	print_matrix3(result);
}

static void	test10(void)
{
	printf("TEST 10:\n");
	printf("Scenario: Calculating a cofactor of a 3x3 matrix\n\
Given the following 3x3 matrix A:\n\
| 3 | 5 | 0 |\n\
| 2 | -1 | -7 |\n\
| 6 | -1 | 5 |\n\
Then minor(A, 0, 0) = -12\n\
And cofactor(A, 0, 0) = -12\n\
And minor(A, 1, 0) = 25\n\
And cofactor(A, 1, 0) = -25\n");
	print_matrix3(m3by3_2);
	printf("Minor [0, 0]\t= %f\n", matrix3_minor(m3by3_2, 0, 0));
	printf("Cofactor [0, 0]\t= %f\n", matrix3_cofactor(m3by3_2, 0, 0));
	printf("Minor [1, 0]\t= %f\n", matrix3_minor(m3by3_2, 1, 0));
	printf("Cofactor [1, 0]\t= %f\n", matrix3_cofactor(m3by3_2, 1, 0));
}

static void	test11(void)
{
	printf("TEST 11:\n");
	printf("Scenario: Calculating the determinant of a 3x3 matrix\n\
Given the following 3x3 matrix A:\n\
| 1 | 2 | 6 |\n\
| -5 | 8 | -4 |\n\
| 2 | 6 | 4 |\n\
Then cofactor(A, 0, 0) = 56\n\
And cofactor(A, 0, 1) = 12\n\
And cofactor(A, 0, 2) = -46\n\
And determinant(A) = -196\n");
	print_matrix3(m3by3_3);
	printf("Cofactor [0, 0]\t= %f\n", matrix3_cofactor(m3by3_3, 0, 0));
	printf("Cofactor [0, 1]\t= %f\n", matrix3_cofactor(m3by3_3, 0, 1));
	printf("Cofactor [0, 2]\t= %f\n", matrix3_cofactor(m3by3_3, 0, 2));
	printf("Determinant\t= %f\n", matrix3_determinant(m3by3_3));
}

static void	test12(void)
{
	printf("TEST 12:\n");
	printf("Scenario: Calculating the determinant of a 4x4 matrix\n\
Given the following 4x4 matrix A:\n\
| -2 | -8 | 3 | 5 |\n\
| -3 | 1 | 7 | 3 |\n\
| 1 | 2 | -9 | 6 |\n\
| -6 | 7 | 7 | -9 |\n\
Then cofactor(A, 0, 0) = 690\n\
And cofactor(A, 0, 1) = 447\n\
And cofactor(A, 0, 2) = 210\n\
And cofactor(A, 0, 3) = 51\n\
And determinant(A) = -4071\n");
	print_matrix4(m8);
	printf("Cofactor [0, 0]\t= %f\n", matrix4_cofactor(m8, 0, 0));
	printf("Cofactor [0, 1]\t= %f\n", matrix4_cofactor(m8, 0, 1));
	printf("Cofactor [0, 2]\t= %f\n", matrix4_cofactor(m8, 0, 2));
	printf("Cofactor [0, 3]\t= %f\n", matrix4_cofactor(m8, 0, 3));
	printf("Determinant\t= %f\n", matrix4_determinant(m8));
}

static void	test13(void)
{
	t_matrix4	invert;

	printf("TEST 13:\n");
	printf("Scenario: Calculating the inverse of a matrix\n\
Given the following 4x4 matrix A:\n\
| -5 | 2 | 6 | -8 |\n\
| 1 | -5 | 1 | 8 |\n\
| 7 | 7 | -6 | -7 |\n\
| 1 | -3 | 7 | 4 |\n\
And B ← inverse(A)\n\
Then determinant(A) = 532\n\
And cofactor(A, 2, 3) = -160\n\
And B[3,2] = -160/532\n\
And cofactor(A, 3, 2) = 105\n\
And B[2,3] = 105/532\n\
And B is the following 4x4 matrix:\n\
| 0.21805 | 0.45113 | 0.24060 | -0.04511 |\n\
| -0.80827 | -1.45677 | -0.44361 | 0.52068 |\n\
| -0.07895 | -0.22368 | -0.05263 | 0.19737 |\n\
| -0.52256 | -0.81391 | -0.30075 | 0.30639 |\n");
	print_matrix4(m9);
	invert = matrix4_invert(m9);
	print_matrix4(invert);
}

static void	test14(void)
{
	t_matrix4	invert;

	printf("TEST 14:\n");
	printf("Scenario: Calculating the inverse of another matrix\n\
Given the following 4x4 matrix A:\n\
| 8 | -5 | 9 | 2 |\n\
| 7 | 5 | 6 | 1 |\n\
| -6 | 0 | 9 | 6 |\n\
| -3 | 0 | -9 | -4 |\n\
Then inverse(A) is the following 4x4 matrix:\n\
| -0.15385 | -0.15385 | -0.28205 | -0.53846 |\n\
| -0.07692 | 0.12308 | 0.02564 | 0.03077 |\n\
| 0.35897 | 0.35897 | 0.43590 | 0.92308 |\n\
| -0.69231 | -0.69231 | -0.76923 | -1.92308 |\n\
Scenario: Calculating the inverse of a third matrix\n\
Given the following 4x4 matrix A:\n\
| 9 | 3 | 0 | 9 |\n\
| -5 | -2 | -6 | -3 |\n\
| -4 | 9 | 6 | 4 |\n\
| -7 | 6 | 6 | 2 |\n\
Then inverse(A) is the following 4x4 matrix:\n\
| -0.04074 | -0.07778 | 0.14444 | -0.22222 |\n\
| -0.07778 | 0.03333 | 0.36667 | -0.33333 |\n\
| -0.02901 | -0.14630 | -0.10926 | 0.12963 |\n\
| 0.17778 | 0.06667 | -0.26667 | 0.33333 |\n");
	print_matrix4(m10);
	invert = matrix4_invert(m10);
	print_matrix4(invert);
	print_matrix4(m11);
	invert = matrix4_invert(m11);
	print_matrix4(invert);
}

static void	test15(void)
{
	t_matrix4	multiply;
	t_matrix4	invert;
	t_matrix4	result;

	printf("TEST 15:\n");
	printf("Scenario: Multiplying a product by its inverse\n\
Given the following 4x4 matrix A:\n\
| 3 | -9 | 7 | 3 |\n\
| 3 | -8 | 2 | -9 |\n\
| -4 | 4 | 4 | 1 |\n\
| -6 | 5 | -1 | 1 |\n\
And the following 4x4 matrix B:\n\
| 8 | 2 | 2 | 2 |\n\
| 3 | -1 | 7 | 0 |\n\
| 7 | 0 | 5 | 4 |\n\
| 6 | -2 | 0 | 5 |\n\
And C ← A * B\n\
Then C * inverse(B) = A\n");
	print_matrix4(m12);
	print_matrix4(m13);
	multiply = matrix4_multiply(m12, m13);
	printf("Multiplification result:\n");
	print_matrix4(multiply);
	invert = matrix4_invert(m13);
	printf("Inversion result:\n");
	print_matrix4(invert);
	result = matrix4_multiply(multiply, invert);
	printf("Final result:\n");
	print_matrix4(result);
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
	test12();
	printf("_____________________________________________\n");
	test13();
	printf("_____________________________________________\n");
	test14();
	printf("_____________________________________________\n");
	test15();
	printf("_____________________________________________\n");
	printf("---------- TESTING MATRICES FINISHED --------\n");
	printf("\n");
}

static void	init_matrices(void)
{
	identity.data[0][0] = 1;
	identity.data[0][1] = 0;
	identity.data[0][2] = 0;
	identity.data[0][3] = 0;
	identity.data[1][0] = 0;
	identity.data[1][1] = 1;
	identity.data[1][2] = 0;
	identity.data[1][3] = 0;
	identity.data[2][0] = 0;
	identity.data[2][1] = 0;
	identity.data[2][2] = 1;
	identity.data[2][3] = 0;
	identity.data[3][0] = 0;
	identity.data[3][1] = 0;
	identity.data[3][2] = 0;
	identity.data[3][3] = 1;

	m1.data[0][0] = 1;
	m1.data[0][1] = 2;
	m1.data[0][2] = 3;
	m1.data[0][3] = 4;
	m1.data[1][0] = 5;
	m1.data[1][1] = 6;
	m1.data[1][2] = 7;
	m1.data[1][3] = 8;
	m1.data[2][0] = 9;
	m1.data[2][1] = 8;
	m1.data[2][2] = 7;
	m1.data[2][3] = 6;
	m1.data[3][0] = 5;
	m1.data[3][1] = 4;
	m1.data[3][2] = 3;
	m1.data[3][3] = 2;

	m2.data[0][0] = 1;
	m2.data[0][1] = 2;
	m2.data[0][2] = 3;
	m2.data[0][3] = 4;
	m2.data[1][0] = 5;
	m2.data[1][1] = 6;
	m2.data[1][2] = 7;
	m2.data[1][3] = 8;
	m2.data[2][0] = 9;
	m2.data[2][1] = 8;
	m2.data[2][2] = 7;
	m2.data[2][3] = 6;
	m2.data[3][0] = 5;
	m2.data[3][1] = 4;
	m2.data[3][2] = 3;
	m2.data[3][3] = 2;

	m3.data[0][0] = 2;
	m3.data[0][1] = 3;
	m3.data[0][2] = 4;
	m3.data[0][3] = 5;
	m3.data[1][0] = 6;
	m3.data[1][1] = 7;
	m3.data[1][2] = 8;
	m3.data[1][3] = 9;
	m3.data[2][0] = 8;
	m3.data[2][1] = 7;
	m3.data[2][2] = 6;
	m3.data[2][3] = 5;
	m3.data[3][0] = 4;
	m3.data[3][1] = 3;
	m3.data[3][2] = 2;
	m3.data[3][3] = 1;

	m4.data[0][0] = -2;
	m4.data[0][1] = 1;
	m4.data[0][2] = 2;
	m4.data[0][3] = 3;
	m4.data[1][0] = 3;
	m4.data[1][1] = 2;
	m4.data[1][2] = 1;
	m4.data[1][3] = -1;
	m4.data[2][0] = 4;
	m4.data[2][1] = 3;
	m4.data[2][2] = 6;
	m4.data[2][3] = 5;
	m4.data[3][0] = 1;
	m4.data[3][1] = 2;
	m4.data[3][2] = 7;
	m4.data[3][3] = 8;

	m5.data[0][0] = 1;
	m5.data[0][1] = 2;
	m5.data[0][2] = 3;
	m5.data[0][3] = 4;
	m5.data[1][0] = 2;
	m5.data[1][1] = 4;
	m5.data[1][2] = 4;
	m5.data[1][3] = 2;
	m5.data[2][0] = 8;
	m5.data[2][1] = 6;
	m5.data[2][2] = 4;
	m5.data[2][3] = 1;
	m5.data[3][0] = 0;
	m5.data[3][1] = 0;
	m5.data[3][2] = 0;
	m5.data[3][3] = 1;

	m6.data[0][0] = 0;
	m6.data[0][1] = 9;
	m6.data[0][2] = 3;
	m6.data[0][3] = 0;
	m6.data[1][0] = 9;
	m6.data[1][1] = 8;
	m6.data[1][2] = 0;
	m6.data[1][3] = 8;
	m6.data[2][0] = 1;
	m6.data[2][1] = 8;
	m6.data[2][2] = 5;
	m6.data[2][3] = 3;
	m6.data[3][0] = 0;
	m6.data[3][1] = 0;
	m6.data[3][2] = 5;
	m6.data[3][3] = 8;

	m7.data[0][0] = -6;
	m7.data[0][1] = 1;
	m7.data[0][2] = 1;
	m7.data[0][3] = 6;
	m7.data[1][0] = -8;
	m7.data[1][1] = 5;
	m7.data[1][2] = 8;
	m7.data[1][3] = 6;
	m7.data[2][0] = -1;
	m7.data[2][1] = 0;
	m7.data[2][2] = 8;
	m7.data[2][3] = 2;
	m7.data[3][0] = -7;
	m7.data[3][1] = 1;
	m7.data[3][2] = -1;
	m7.data[3][3] = 1;

	m8.data[0][0] = -2;
	m8.data[0][1] = -8;
	m8.data[0][2] = 3;
	m8.data[0][3] = 5;
	m8.data[1][0] = -3;
	m8.data[1][1] = 1;
	m8.data[1][2] = 7;
	m8.data[1][3] = 3;
	m8.data[2][0] = 1;
	m8.data[2][1] = 2;
	m8.data[2][2] = -9;
	m8.data[2][3] = 6;
	m8.data[3][0] = -6;
	m8.data[3][1] = 7;
	m8.data[3][2] = 7;
	m8.data[3][3] = -9;

	m9.data[0][0] = -5;
	m9.data[0][1] = 2;
	m9.data[0][2] = 6;
	m9.data[0][3] = -8;
	m9.data[1][0] = 1;
	m9.data[1][1] = -5;
	m9.data[1][2] = 1;
	m9.data[1][3] = 8;
	m9.data[2][0] = 7;
	m9.data[2][1] = 7;
	m9.data[2][2] = -6;
	m9.data[2][3] = -7;
	m9.data[3][0] = 1;
	m9.data[3][1] = -3;
	m9.data[3][2] = 7;
	m9.data[3][3] = 4;

	m10.data[0][0] = 8;
	m10.data[0][1] = -5;
	m10.data[0][2] = 9;
	m10.data[0][3] = 2;
	m10.data[1][0] = 7;
	m10.data[1][1] = 5;
	m10.data[1][2] = 6;
	m10.data[1][3] = 1;
	m10.data[2][0] = -6;
	m10.data[2][1] = 0;
	m10.data[2][2] = 9;
	m10.data[2][3] = 6;
	m10.data[3][0] = -3;
	m10.data[3][1] = 0;
	m10.data[3][2] = -9;
	m10.data[3][3] = -4;

	m11.data[0][0] = 9;
	m11.data[0][1] = 3;
	m11.data[0][2] = 0;
	m11.data[0][3] = 9;
	m11.data[1][0] = -5;
	m11.data[1][1] = -2;
	m11.data[1][2] = -6;
	m11.data[1][3] = -3;
	m11.data[2][0] = -4;
	m11.data[2][1] = 9;
	m11.data[2][2] = 6;
	m11.data[2][3] = 4;
	m11.data[3][0] = -7;
	m11.data[3][1] = 6;
	m11.data[3][2] = 6;
	m11.data[3][3] = 2;

	m12.data[0][0] = 3;
	m12.data[0][1] = -9;
	m12.data[0][2] = 7;
	m12.data[0][3] = 3;
	m12.data[1][0] = 3;
	m12.data[1][1] = -8;
	m12.data[1][2] = 2;
	m12.data[1][3] = -9;
	m12.data[2][0] = -4;
	m12.data[2][1] = 4;
	m12.data[2][2] = 4;
	m12.data[2][3] = 1;
	m12.data[3][0] = -6;
	m12.data[3][1] = 5;
	m12.data[3][2] = -1;
	m12.data[3][3] = 1;

	m13.data[0][0] = 8;
	m13.data[0][1] = 2;
	m13.data[0][2] = 2;
	m13.data[0][3] = 2;
	m13.data[1][0] = 3;
	m13.data[1][1] = -1;
	m13.data[1][2] = 7;
	m13.data[1][3] = 0;
	m13.data[2][0] = 7;
	m13.data[2][1] = 0;
	m13.data[2][2] = 5;
	m13.data[2][3] = 4;
	m13.data[3][0] = 6;
	m13.data[3][1] = -2;
	m13.data[3][2] = 0;
	m13.data[3][3] = 5;

	m2by2.data[0][0] = 1;
	m2by2.data[0][1] = 5;

	m2by2.data[0][0] = 1;
	m2by2.data[0][1] = 5;

	m2by2.data[0][0] = 1;
	m2by2.data[0][1] = 5;
	m2by2.data[1][0] = -3;
	m2by2.data[1][1] = 2;

	m3by3.data[0][0] = 1;
	m3by3.data[0][1] = 5;
	m3by3.data[0][2] = 0;
	m3by3.data[1][0] = -3;
	m3by3.data[1][1] = 2;
	m3by3.data[1][2] = 7;
	m3by3.data[2][0] = 0;
	m3by3.data[2][1] = 6;
	m3by3.data[2][2] = -3;

	m3by3_2.data[0][0] = 3;
	m3by3_2.data[0][1] = 5;
	m3by3_2.data[0][2] = 0;
	m3by3_2.data[1][0] = 2;
	m3by3_2.data[1][1] = -1;
	m3by3_2.data[1][2] = -7;
	m3by3_2.data[2][0] = 6;
	m3by3_2.data[2][1] = -1;
	m3by3_2.data[2][2] = 5;

	m3by3_3.data[0][0] = 1;
	m3by3_3.data[0][1] = 2;
	m3by3_3.data[0][2] = 6;
	m3by3_3.data[1][0] = -5;
	m3by3_3.data[1][1] = 8;
	m3by3_3.data[1][2] = -4;
	m3by3_3.data[2][0] = 2;
	m3by3_3.data[2][1] = 6;
	m3by3_3.data[2][2] = 4;
}

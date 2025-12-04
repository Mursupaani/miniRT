
#include "minirt.h"

static void	test1(void)
{
	t_point	p;
	t_point	result;
	t_matrix4	(transform);

	printf("TEST 1:\n");
	printf("Scenario: Multiplying by a translation matrix\n\
Given transform ← translation(5, -3, 2)\n\
And p ← point(-3, 4, 5)\n\
Then transform * p = point(2, 1, 7)\n");
	p = point(-3, 4, 5);
	print_tuple(p);
	transform = translation_matrix4(5, -3, 2);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, p);
	print_tuple(result);
}

static void	test2(void)
{
	t_point	p;
	t_point	result;
	t_matrix4	(transform);
	t_matrix4	(invert);

	printf("TEST 2:\n");
	printf("Scenario: Multiplying by the inverse of a translation matrix\n\
Given transform ← translation(5, -3, 2)\n\
And inv ← inverse(transform)\n\
And p ← point(-3, 4, 5)\n\
Then inv * p = point(-8, 7, 3)\n");
	p = point(-3, 4, 5);
	print_tuple(p);
	transform = translation_matrix4(5, -3, 2);
	print_matrix4(transform);
	invert = matrix4_invert(transform);
	result = matrix4_and_tuple_multiply(invert, p);
	print_tuple(result);
}

static void	test3(void)
{
	t_point	v;
	t_point	result;
	t_matrix4	(transform);

	printf("TEST 3:\n");
	printf("Scenario: Translation does not affect vectors\n\
Given transform ← translation(5, -3, 2)\n\
And v ← vector(-3, 4, 5)\n\
Then transform * v = v\n");
	v = vector(5, -3, 2);
	print_tuple(v);
	transform = translation_matrix4(-3, 4, 5);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, v);
	print_tuple(result);
}

static void	test4(void)
{
	t_point	p;
	t_point	result;
	t_matrix4	(transform);

	printf("TEST 4:\n");
	printf("Scenario: A scaling matrix applied to a point\n\
Given transform ← scaling(2, 3, 4)\n\
And p ← point(-4, 6, 8)\n\
Then transform * p = point(-8, 18, 32)\n");
	p = point(-4, 6, 8);
	print_tuple(p);
	transform = scaling_matrix4(2, 3, 4);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, p);
	print_tuple(result);
}

static void	test5(void)
{
	t_vector	v;
	t_point		result;
	t_matrix4		(transform);

	printf("TEST 5:\n");
	printf("Scenario: A scaling matrix applied to a vector\n\
Given transform ← scaling(2, 3, 4)\n\
And v ← vector(-4, 6, 8)\n\
Then transform * v = vector(-8, 18, 32)\n");
	v = vector(-4, 6, 8);
	print_tuple(v);
	transform = scaling_matrix4(2, 3, 4);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, v);
	print_tuple(result);
}

static void	test6(void)
{
	t_vector	v;
	t_point		result;
	t_matrix4		(transform);
	t_matrix4		(inverse);

	printf("TEST 6:\n");
	printf("Scenario: Multiplying by the inverse of a scaling matrix\n\
Given transform ← scaling(2, 3, 4)\n\
And inv ← inverse(transform)\n\
And v ← vector(-4, 6, 8)\n\
Then inv * v = vector(-2, 2, 2)\n");
	v = vector(-4, 6, 8);
	print_tuple(v);
	transform = scaling_matrix4(2, 3, 4);
	print_matrix4(transform);
	inverse = matrix4_invert(transform);
	print_matrix4(inverse);
	result = matrix4_and_tuple_multiply(inverse, v);
	print_tuple(result);
}

static void	test7(void)
{
	t_vector	p;
	t_point		result;
	t_matrix4		(transform);

	printf("TEST 7:\n");
	printf("Scenario: Reflection is scaling by a negative value\n\
Given transform ← scaling(-1, 1, 1)\n\
And p ← point(2, 3, 4)\n\
Then transform * p = point(-2, 3, 4)\n");
	p = point(2, 3, 4);
	print_tuple(p);
	transform = scaling_matrix4(-1, 1, 1);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, p);
	print_tuple(result);
}

static void	test8(void)
{
	t_vector	p;
	t_point		result;
	t_matrix4		(transform);

	printf("TEST 8:\n");
	printf("Scenario: Rotating a point around the x axis\n\
Given p ← point(0, 1, 0)\n\
And half_quarter← rotation_x(π / 4)\n\
And full_quarter← rotation_x(π / 2)\n\
Then half_quarter * p = point(0, √2/2, √2/2)\n\
And full_quarter * p = point(0, 0, 1)\n");
	p = point(0, 1, 0);
	print_tuple(p);
	transform = x_rotation(M_PI / 4);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, p);
	print_tuple(result);
	transform = x_rotation(M_PI / 2);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, p);
	print_tuple(result);
}

static void	test9(void)
{
	t_vector	p;
	t_point		result;
	t_matrix4		(transform);
	t_matrix4		(inverse);

	printf("TEST 9:\n");
	printf("Scenario: The inverse of an x-rotation rotates in the opposite direction\n\
Given p ← point(0, 1, 0)\n\
And half_quarter← rotation_x(π / 4)\n\
And inv ← inverse(half_quarter)\n\
Then inv * p = point(0, √2/2, -√2/2)\n");
	p = point(0, 1, 0);
	print_tuple(p);
	transform = x_rotation(M_PI / 4);
	print_matrix4(transform);
	inverse = matrix4_invert(transform);
	print_matrix4(inverse);
	result = matrix4_and_tuple_multiply(inverse, p);
	print_tuple(result);
}


static void	test10(void)
{
	t_vector	p;
	t_point		result;
	t_matrix4		(transform);

	printf("TEST 10:\n");
	printf("Scenario: Rotating a point around the y axis\n\
Given p ← point(0, 0, 1)\n\
And half_quarter← rotation_y(π / 4)\n\
And full_quarter← rotation_y(π / 2)\n\
Then half_quarter * p = point(√2/2, 0, √2/2)\n\
And full_quarter * p = point(1, 0, 0)\n");
	p = point(0, 0, 1);
	print_tuple(p);
	transform = y_rotation(M_PI / 4);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, p);
	print_tuple(result);
	transform = y_rotation(M_PI / 2);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, p);
	print_tuple(result);
}

static void	test11(void)
{
	t_vector	p;
	t_point		result;
	t_matrix4		(transform);

	printf("TEST 11:\n");
	printf("Scenario: Rotating a point around the z axis\n\
Given p ← point(0, 1, 0)\n\
And half_quarter← rotation_z(π / 4)\n\
And full_quarter← rotation_z(π / 2)\n\
Then half_quarter * p = point(-√2/2, √2/2, 0)\n\
And full_quarter * p = point(-1, 0, 0)\n");
	p = point(0, 1, 0);
	print_tuple(p);
	transform = z_rotation(M_PI / 4);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, p);
	print_tuple(result);
	transform = z_rotation(M_PI / 2);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, p);
	print_tuple(result);
}

static void	test12(void)
{
	t_vector	p;
	t_point		result;
	t_shear		shear;
	t_matrix4		(transform);

	printf("TEST 12:\n");
	printf("Scenario: A shearing transformation moves x in proportion to y\n\
Given transform ← shearing(1, 0, 0, 0, 0, 0)\n\
And p ← point(2, 3, 4)\n\
Then transform * p = point(5, 3, 4)\n");
	ft_bzero(&shear, sizeof(t_shear));
	shear.xy = 1;
	p = point(2, 3, 4);
	print_tuple(p);
	transform = shearing(shear);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, p);
	print_tuple(result);
}

static void	test13(void)
{
	t_vector	p;
	t_point		result;
	t_shear		shear;
	t_matrix4		(transform);

	printf("TEST 13:\n");
	printf("Scenario: A shearing transformation moves x in proportion to z\n\
Given transform ← shearing(0, 1, 0, 0, 0, 0)\n\
And p ← point(2, 3, 4)\n\
Then transform * p = point(6, 3, 4)\n");
	ft_bzero(&shear, sizeof(t_shear));
	shear.xz = 1;
	p = point(2, 3, 4);
	print_tuple(p);
	transform = shearing(shear);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, p);
	print_tuple(result);
}

static void	test14(void)
{
	t_vector	p;
	t_point		result;
	t_shear		shear;
	t_matrix4		(transform);

	printf("TEST 14:\n");
	printf("Scenario: A shearing transformation moves y in proportion to x\n\
Given transform ← shearing(0, 0, 1, 0, 0, 0)\n\
And p ← point(2, 3, 4)\n\
Then transform * p = point(2, 5, 4)\n");
	ft_bzero(&shear, sizeof(t_shear));
	shear.yx = 1;
	p = point(2, 3, 4);
	print_tuple(p);
	transform = shearing(shear);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, p);
	print_tuple(result);
}

static void	test15(void)
{
	t_vector	p;
	t_point		result;
	t_shear		shear;
	t_matrix4		(transform);

	printf("TEST 15:\n");
	printf("Scenario: A shearing transformation moves y in proportion to z\n\
Given transform ← shearing(0, 0, 0, 1, 0, 0)\n\
And p ← point(2, 3, 4)\n\
Then transform * p = point(2, 7, 4)\n");
	ft_bzero(&shear, sizeof(t_shear));
	shear.yz = 1;
	p = point(2, 3, 4);
	print_tuple(p);
	transform = shearing(shear);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, p);
	print_tuple(result);
}

static void	test16(void)
{
	t_vector	p;
	t_point		result;
	t_shear		shear;
	t_matrix4	(transform);

	printf("TEST 16:\n");
	printf("Scenario: A shearing transformation moves z in proportion to x\n\
Given transform ← shearing(0, 0, 0, 0, 1, 0)\n\
And p ← point(2, 3, 4)\n\
Then transform * p = point(2, 3, 6)\n");
	ft_bzero(&shear, sizeof(t_shear));
	shear.zx = 1;
	p = point(2, 3, 4);
	print_tuple(p);
	transform = shearing(shear);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, p);
	print_tuple(result);
}

static void	test17(void)
{
	t_vector	p;
	t_point		result;
	t_shear		shear;
	t_matrix4	transform;

	printf("TEST 17:\n");
	printf("Scenario: A shearing transformation moves z in proportion to y\n\
Given transform ← shearing(0, 0, 0, 0, 0, 1)\n\
And p ← point(2, 3, 4)\n\
Then transform * p = point(2, 3, 7)\n");
	ft_bzero(&shear, sizeof(t_shear));
	shear.zy = 1;
	p = point(2, 3, 4);
	print_tuple(p);
	transform = shearing(shear);
	print_matrix4(transform);
	result = matrix4_and_tuple_multiply(transform, p);
	print_tuple(result);
}

void	test_transformation(void)
{
	printf("\n");
	printf("------------- TESTING MATRICES --------------\n");
	printf("------------- TESTING TRANSFORM -------------\n");
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
	test16();
	printf("_____________________________________________\n");
	test17();
	printf("_____________________________________________\n");
	printf("--------- TESTING TRANSFORM FINISHED --------\n");
	printf("\n");
}

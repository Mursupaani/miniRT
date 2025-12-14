#include "minirt.h"

static void	test1()
{
	bool	ret;

	printf("Test 1: Scenario: There is no shadow when nothing is collinear with point and light.\n");
	ret = is_shadowed(default_world(), point(0, 10, 0));
	if (ret == true)
		printf("\033[0;31mfail\n\033[0m");
	else
		printf("\033[0;32mpass\n\033[0m");
}

static void	test2()
{
	bool	ret;

	printf("Test 2: Scenario: The shadow when an object is between the point and the light\n");
	ret = is_shadowed(default_world(), point(10, -10, 10));
	if (ret == true)
		printf("\033[0;32mpass\n\033[0m");
	else
		printf("\033[0;31mfail\n\033[0m");
}

static void	test3()
{
	bool	ret;

	printf("Test 3: Scenario: There is no shadow when an object is behind the light\n");
	ret = is_shadowed(default_world(), point(-20, 20, -20));
	if (ret == true)
		printf("\033[0;31mfail\n\033[0m");
	else
		printf("\033[0;32mpass\n\033[0m");
}

static void	test4()
{
	bool	ret;

	printf("Test 4: Scenario: There is no shadow when an object is behind the point.\n");
	ret = is_shadowed(default_world(), point(-2, 2, -2));
	if (ret == true)
		printf("\033[0;31mfail\n\033[0m");
	else
		printf("\033[0;32mpass\n\033[0m");
}

static void	test5()
{
	printf("Test 5:");
	printf("Scenario: The hit should offset the point\n\
Given r ← ray(point(0, 0, -5), vector(0, 0, 1))\n\
And shape ← sphere() with:\n\
| transform | translation(0, 0, 1) |\n\
And i ← intersection(5, shape)\n\
When comps ← prepare_computations(i, r)\n\
Then comps.over_point.z < -EPSILON/2\n\
And comps.point.z > comps.over_point.z\n");
	t_ray		r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_object	*shape = sphere_new();
	t_matrix4	translation = translation_matrix4(0, 0, 1);
	set_transform(shape, translation);
	t_intersection	i = intersection(5, shape);
	t_computations	comps = prepare_computations(i, r);
	print_computations(comps);
	printf("over_point.z < -EPSILON / 2: ");
	if (comps.over_point.z < -EPSILON / 2)
		printf("true\n");
	else
		printf("false\n");
	free_object(shape);
}


void	test_shadows()
{
	printf("\n");
	printf("--------------- TESTING SHADOWS ---------------\n");
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
	printf("---------- TESTING SHADOWS FINISHED -----------\n");
	printf("\n");
	return;
}

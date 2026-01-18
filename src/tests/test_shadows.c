#include "minirt.h"

static void	test1()
{
	bool	ret;

	printf("Test 1: Scenario: There is no shadow when nothing is collinear with point and light.\n");
	ret = is_shadowed(default_world(), point(0, 10, 0), NULL);
	if (ret == true)
		printf("\033[0;31mfail\n\033[0m");
	else
		printf("\033[0;32mpass\n\033[0m");
}

static void	test2()
{
	bool	ret;

	printf("Test 2: Scenario: The shadow when an object is between the point and the light\n");
	ret = is_shadowed(default_world(), point(10, -10, 10), NULL);
	if (ret == true)
		printf("\033[0;32mpass\n\033[0m");
	else
		printf("\033[0;31mfail\n\033[0m");
}

static void	test3()
{
	bool	ret;

	printf("Test 3: Scenario: There is no shadow when an object is behind the light\n");
	ret = is_shadowed(default_world(), point(-20, 20, -20), NULL);
	if (ret == true)
		printf("\033[0;31mfail\n\033[0m");
	else
		printf("\033[0;32mpass\n\033[0m");
}

static void	test4()
{
	bool	ret;

	printf("Test 4: Scenario: There is no shadow when an object is behind the point.\n");
	ret = is_shadowed(default_world(), point(-2, 2, -2), NULL);
	if (ret == true)
		printf("\033[0;31mfail\n\033[0m");
	else
		printf("\033[0;32mpass\n\033[0m");
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
	printf("---------- TESTING SHADOWS FINISHED -----------\n");
	printf("\n");
	return;
}

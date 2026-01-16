/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:37:30 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/11 14:54:06 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	test1()
{
	t_camera	*c;

	printf("TEST 1:\n");
	printf("Scenario: Constructing a camera\n\
Given hsize ← 160\n\
And vsize ← 120\n\
And field_of_view ← π/2\n\
When c ← camera(hsize, vsize, field_of_view)\n\
Then c.hsize = 160\n\
And c.vsize = 120\n\
And c.field_of_view = π/2\n\
And c.transform = identity_matrix\n");
	c = camera(160, 120, M_PI / 2);
	print_camera(c);
	free(c);
}

static void	test2()
{
	t_camera	*c;

	printf("TEST 2:\n");
	printf("Scenario: Constructing a camera\n\
Given hsize ← 160\n\
And vsize ← 120\n\
And field_of_view ← π/2\n\
When c ← camera(hsize, vsize, field_of_view)\n\
Then c.hsize = 160\n\
And c.vsize = 120\n\
And c.field_of_view = π/2\n\
And c.transform = identity_matrix\n");
	c = camera(160, 120, M_PI / 2);
	print_camera(c);
	free(c);
}

static void	test3()
{
	t_camera	*c;
	t_ray		r;

	printf("TEST 3:\n");
	printf("Scenario: Constructing a ray through the center of the canvas\n\
Given c ← camera(201, 101, π/2)\n\
When r ← ray_for_pixel(c, 100, 50)\n\
Then r.origin = point(0, 0, 0)\n\
And r.direction = vector(0, 0, -1)\n");
	c = camera(201, 101, M_PI / 2);
	r = ray_for_pixel(c, 100, 50);
	print_ray(r);
	free(c);
}

static void	test4()
{
	t_camera	*c;
	t_ray		r;

	printf("TEST 4:\n");
	printf("Scenario: Constructing a ray through a corner of the canvas\n\
Given c ← camera(201, 101, π/2)\n\
When r ← ray_for_pixel(c, 0, 0)\n\
Then r.origin = point(0, 0, 0)\n\
And r.direction = vector(0.66519, 0.33259, -0.66851)\n");
	c = camera(201, 101, M_PI / 2);
	r = ray_for_pixel(c, 0, 0);
	print_ray(r);
	free(c);
}

static void	test5()
{
	t_camera	*c;
	t_ray		r;

	printf("TEST 5:\n");
	printf("Scenario: Constructing a ray when the camera is transformed\n\
Given c ← camera(201, 101, π/2)\n\
When c.transform ← rotation_y(π/4) * translation(0, -2, 5)\n\
And r ← ray_for_pixel(c, 100, 50)\n\
Then r.origin = point(0, 2, -5)\n\
And r.direction = vector(√2/2, 0, -√2/2)\n");
	c = camera(201, 101, M_PI / 2);
	c->transform = matrix4_multiply(rotation_y(M_PI / 4), translation_matrix4(0, -2, 5));
	r = ray_for_pixel(c, 100, 50);
	print_ray(r);
	free(c);
}

void	test_camera()
{
	printf("\n");
	printf("--------------- TESTING CAMERA --------------\n");
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
	printf("---------- TESTING CAMERA FINISHED ----------\n");
	printf("\n");
	return;
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:38:13 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/09 17:57:14 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	void test1()
{
	t_world	*w;

	printf("TEST 1:\n");
	printf("Scenario: The default world\n\
Given light ← point_light(point(-10, 10, -10), color(1, 1, 1))\n\
And s1 ← sphere() with:\n\
| material.color\n\
| (0.8, 1.0, 0.6)\n\
| material.diffuse\n\
| 0.7\n\
| material.specular | 0.2\n\
And s2 ← sphere() with:\n\
| transform | scaling(0.5, 0.5, 0.5) |\n\
When w ← default_world()\n\
Then w.light = light\n\
And w contains s1\n\
And w contains s2\n");
	w = default_world();
	print_world(w);
	free_world(w);
}

static	void test2()
{
	t_world			*w;
	t_ray			r;
	t_intersections	*xs;

	printf("TEST 2:\n");
	printf("Scenario: Intersect a world with a ray\n\
Given w ← default_world()\n\
And r ← ray(point(0, 0, -5), vector(0, 0, 1))\n\
When xs ← intersect_world(w, r)Building a World • 93\n\
Then xs.count = 4\n\
And xs[0].t = 4\n\
And xs[1].t = 4.5\n\
And xs[2].t = 5.5\n\
And xs[3].t = 6\n");
	w = default_world();
	r = ray(point(0, 0, -5), vector(0, 0, 1));
	xs = intersect_world(w, r);
	print_world(w);
	print_intersections(xs);
	free_intersections(xs);
	free_world(w);
}

void	test_world()
{
	printf("\n");
	printf("--------------- TESTING WORLD ---------------\n");
	printf("_____________________________________________\n");
	test1();
	printf("_____________________________________________\n");
	test2();
	printf("_____________________________________________\n");
	printf("---------- TESTING WORLD FINISHED -----------\n");
	printf("\n");
}

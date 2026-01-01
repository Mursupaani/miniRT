/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bump_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 17:08:04 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/01 17:16:00 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	test1()
{
	t_object *sphere = sphere_new();
	mlx_texture_t *bump	 = mlx_load_png("./Textures/bump.png");
	t_vector normal = vector(1, 0, 0);
	t_point p;
	p = point(1, 0, 0);
	sphere->bump_map.bump_map = bump;
	sphere->bump_map.uv_map = spherical_map;
	print_tuple(normal);
	apply_bump_map_on_normal(sphere, &normal, p);
	print_tuple(normal);
}

void	test_bump_maps(void)
{
	printf("\n");
	printf("------------- TESTING BUMP MAP --------------\n");
	printf("_____________________________________________\n");
	test1();
	printf("_____________________________________________\n");
	printf("--------- TESTING BUMP MAP FINISHED ---------\n");
	printf("\n");
}

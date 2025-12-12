/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_render_chapter7.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 13:56:21 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/12 14:23:42 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_chapter_7(t_app *app)
{
	t_camera	*c;
	t_world		*w;
	int			x;
	int			y;

	c = camera(100, 50, M_PI / 3);
	c->transform = view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0));
	w = default_world();
	t_object *floor = sphere_new();
	floor->transform =scaling_matrix4(10, 0.01, 10);
	floor->material.color = color(1, 0.9, 0.9);
	floor->material.specular = 0;
	world_add_object(w, floor);

	// t_object *left_wall = sphere_new();
	// left_wall->transform = scaling_matrix4(10, 0.01, 10);
	// left_wall->transform = matrix4_multiply(left_wall->transform, rotation_y(M_PI / 2));
	// left_wall->transform = matrix4_multiply(left_wall->transform, rotation_x(-M_PI / 4));
	// left_wall->transform = matrix4_multiply(left_wall->transform, translation_matrix4(0, 0, 5));
	// left_wall->material = floor->material;
	// world_add_object(w, left_wall);
	//
	// t_object *right_wall = sphere_new();
	// right_wall->transform = scaling_matrix4(10, 0.01, 10);
	// right_wall->transform = matrix4_multiply(left_wall->transform, rotation_y(M_PI / 2));
	// right_wall->transform = matrix4_multiply(left_wall->transform, rotation_x(M_PI / 4));
	// right_wall->transform = matrix4_multiply(left_wall->transform, translation_matrix4(0, 0, 5));
	// right_wall->material = floor->material;
	// world_add_object(w, right_wall);
	//
	// t_object *middle = sphere_new();
	// middle->transform = translation_matrix4(-0.5, 1, 0.5);
	// middle->material.color = color(0.1, 1, 0.5);
	// middle->material.diffuse = 0.7;
	// middle->material.specular = 0.3;
	// world_add_object(w, middle);
	//
	y = -1;
	while (++y < c->vsize)
	{
		x = -1;
		while (++x < c->hsize)
		{
			t_ray	r = ray_for_pixel(c, x, y);
			t_color	c = color_at(w, r);
			if (pixel_fits_image(x, y, app))
				mlx_put_pixel(app->img, x, y, color_hex_from_color(c));
		}
	}
}

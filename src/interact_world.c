/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_world.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:41:46 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/09 16:36:52 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*select_object_from_screen(t_app *app)
{
	t_intersections	*xs;
	int				x;
	int				y;
	t_ray			r;

	mlx_get_mouse_pos(app->mlx, &x, &y);
	r = ray_for_pixel(app->scene->camera, x, y);
	xs = intersect_world(app->scene, r);
	if (!xs || xs->count == 0)
		return (NULL);
	return (hit(xs).object);
}

void	move_in_space(t_app *app, keys_t key)
{
	t_camera *c;

	app->moving = true;
	c = app->scene->camera;
	if (key == MLX_KEY_UP)
	{
		c->from = tuple_sum(c->from, point(0, 0, MOVEMENT_SPEED));
		c->to = tuple_sum(c->to, point(0, 0, MOVEMENT_SPEED));
	}
	else if (key == MLX_KEY_DOWN)
	{
		c->from = tuple_sum(c->from, point(0, 0, -MOVEMENT_SPEED));
		c->to = tuple_sum(c->to, point(0, 0, -MOVEMENT_SPEED));
	}
	else if (key == MLX_KEY_LEFT)
	{
		c->from = tuple_sum(c->from, point(-MOVEMENT_SPEED, 0, 0));
		c->to = tuple_sum(c->to, point(-MOVEMENT_SPEED, 0, 0));
	}
	else if (key == MLX_KEY_RIGHT)
	{
		c->from = tuple_sum(c->from, point(MOVEMENT_SPEED, 0, 0));
		c->to = tuple_sum(c->to, point(MOVEMENT_SPEED, 0, 0));
	}
	set_camera_transform(c, view_transform(c->from, c->to, c->up, c));
	restart_render(app);
}

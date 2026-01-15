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

static t_vector	get_selected_object_offest(t_app *app, t_ray r, t_intersection hit)
{
	t_point	hit_point;
	t_point	obj_origin;
	t_camera	*c;

	c = app->scene->camera;
	hit_point.x = c->from.x + (r.direction.x * hit.t);
	hit_point.y = c->from.y + (r.direction.y * hit.t);
	hit_point.z = c->from.z + (r.direction.z * hit.t);
	hit_point.w = 1;
	obj_origin.x = hit.object->transform.data[0][3];
	obj_origin.y = hit.object->transform.data[1][3];
	obj_origin.z = hit.object->transform.data[2][3];
	obj_origin.w = 1;
	return (tuple_subtract(obj_origin, hit_point));
}

void	move_oject_on_screen(t_app *app)
{
	int			x;
	int			y;
	t_ray		r;
	t_vector	new_pos;
	t_camera	*c;

	if (!app->selected_object)
		return ;
	c = app->scene->camera;
	mlx_get_mouse_pos(app->mlx, &x, &y);
	if (doubles_are_equal(app->prev_mouse_x, x) && doubles_are_equal(app->prev_mouse_y, y))
		return ;
	r = ray_for_pixel(app->scene->camera, x, y);
	new_pos.x = c->from.x + (r.direction.x * app->selected_object_t);
	new_pos.y = c->from.y + (r.direction.y * app->selected_object_t);
	new_pos.z = c->from.z + (r.direction.z * app->selected_object_t);
	app->selected_object->transform.data[0][3] = new_pos.x + app->selected_object_offset.x;
	app->selected_object->transform.data[1][3] = new_pos.y + app->selected_object_offset.y;
	app->selected_object->transform.data[2][3] = new_pos.z + app->selected_object_offset.z;
	set_transform(app->selected_object, app->selected_object->transform);
	app->data_changed = true;
}

void	select_object_from_screen(t_app *app)
{
	t_intersections	*xs;
	t_intersection	ray_hit;
	int				x;
	int				y;
	t_ray			r;

	mlx_get_mouse_pos(app->mlx, &x, &y);
	r = ray_for_pixel(app->scene->camera, x, y);
	xs = intersect_world(app->scene, r);
	if (!xs || xs->count == 0)
		return ;
	ray_hit = hit(xs);
	app->selected_object = ray_hit.object;
	app->selected_object_t = ray_hit.t;
	app->selected_object_offset = get_selected_object_offest(app, r, ray_hit);
}

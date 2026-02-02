/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_and_move_object.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:41:46 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/17 19:36:04 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	move_object_in_depth(t_app *app, t_camera *c, t_look look)
{
	t_vector	new_pos;

	look.dy = app->prev_mouse_y - look.y;
	app->prev_mouse_y = look.y;
	if (look.dy == 0)
		return ;
	new_pos.x = app->selected_object->transform.data[0][3]
		+ (c->forward.x * (look.dy * 0.005));
	new_pos.y = app->selected_object->transform.data[1][3]
		+ (c->forward.y * (look.dy * 0.005));
	new_pos.z = app->selected_object->transform.data[2][3]
		+ (c->forward.z * (look.dy * 0.005));
	app->selected_object->transform.data[0][3] = new_pos.x;
	app->selected_object->transform.data[1][3] = new_pos.y;
	app->selected_object->transform.data[2][3] = new_pos.z;
	set_transform(app->selected_object, app->selected_object->transform);
}

static void	move_object_in_x_y(t_app *app, t_camera *c, t_ray r)
{
	t_vector	new_pos;

	new_pos.x = c->from.x + (r.direction.x * app->selected_object_t);
	new_pos.y = c->from.y + (r.direction.y * app->selected_object_t);
	new_pos.z = c->from.z + (r.direction.z * app->selected_object_t);
	app->selected_object->transform.data[0][3] = new_pos.x
		+ app->selected_object_offset.x;
	app->selected_object->transform.data[1][3] = new_pos.y
		+ app->selected_object_offset.y;
	app->selected_object->transform.data[2][3] = new_pos.z
		+ app->selected_object_offset.z;
	set_transform(app->selected_object, app->selected_object->transform);
}

static t_vector	get_selected_object_offest(
		t_app *app, t_ray r, t_intersection hit)
{
	t_point		hit_point;
	t_point		obj_origin;
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
	t_look		look;
	t_ray		r;
	t_camera	*c;

	if (!app->selected_object)
		return ;
	mlx_get_mouse_pos(app->mlx, &look.x, &look.y);
	if (mouse_not_moved(app, look))
		return ;
	app->prev_mouse_x = look.x;
	app->prev_mouse_y = look.y;
	c = app->scene->camera;
	app->moving = true;
	if (mlx_is_key_down(app->mlx, MLX_KEY_LEFT_ALT))
		move_object_in_depth(app, c, look);
	else
	{
		r = ray_for_pixel(c, look.x, look.y);
		move_object_in_x_y(app, c, r);
	}
	app->data_changed = true;
}

void	select_object_from_screen(t_app *app, atomic_int *err)
{
	t_intersections	*xs;
	t_intersection	ray_hit;
	int				x;
	int				y;
	t_ray			r;

	mlx_get_mouse_pos(app->mlx, &x, &y);
	r = ray_for_pixel(app->scene->camera, x, y);
	xs = intersect_world(app->scene, r, err);
	if (!xs || xs->count == 0)
		return ;
	ray_hit = hit(xs);
	if (!ray_hit.object)
		return ;
	app->selected_object = ray_hit.object;
	app->selected_object_t = ray_hit.t;
	app->selected_object_offset = get_selected_object_offest(app, r, ray_hit);
}

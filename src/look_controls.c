/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:48:31 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/17 19:29:10 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	change_camera_fov(t_app *app, double ydelta)
{
	double	fov_change;

	fov_change = ydelta * FOV_CHANGE * (M_PI / 180);
	app->scene->camera->fov -= fov_change;
	if (app->scene->camera->fov < 0)
		app->scene->camera->fov = 0;
	else if (app->scene->camera->fov > M_PI)
		app->scene->camera->fov = M_PI;
	app->scene->camera->pixel_size = pixel_size(app->scene->camera);
	app->moving = true;
	app->data_changed = true;
}

t_vector	get_direction_from_angles(double yaw, double pitch)
{
	t_vector	direction;
	double		rad_yaw;
	double		rad_pitch;

	rad_yaw = yaw * (M_PI / 180.0);
	rad_pitch = pitch * (M_PI / 180.0);
	direction.x = cos(rad_yaw) * cos(rad_pitch);
	direction.y = sin(rad_pitch);
	direction.z = sin(rad_yaw) * cos(rad_pitch);
	direction.w = 0.0f;
	return (normalize(direction));
}

bool	mouse_not_moved(t_app *app, t_look look)
{
	return (doubles_are_equal(look.x, app->prev_mouse_x)
		&& doubles_are_equal(look.y, app->prev_mouse_y));
}

static void	update_pitch_and_yaw(t_look look, t_camera *c)
{
	c->yaw -= (look.dx * MOUSE_SPEED);
	c->pitch -= (look.dy * MOUSE_SPEED);
	if (c->pitch > 89.9)
		c->pitch = 89.9;
	else if (c->pitch < -89.9)
		c->pitch = -89.9;
	if (c->yaw > 360)
		c->yaw -= 360;
	else if (c->yaw < 0)
		c->yaw += 360;
}

void	handle_looking_around(t_app *app)
{
	t_look		look;
	t_camera	*c;
	t_matrix4	view;

	c = app->scene->camera;
	mlx_set_cursor_mode(app->mlx, MLX_MOUSE_DISABLED);
	mlx_get_mouse_pos(app->mlx, &look.x, &look.y);
	if (mouse_not_moved(app, look))
		return ;
	app->moving = true;
	look.dx = look.x - app->prev_mouse_x;
	look.dy = look.y - app->prev_mouse_y;
	app->prev_mouse_x = look.x;
	app->prev_mouse_y = look.y;
	update_pitch_and_yaw(look, c);
	c->forward = get_direction_from_angles(c->yaw, c->pitch);
	c->left = cross(c->world_up, c->forward);
	c->up = cross(c->forward, c->left);
	view = view_transform(c->from, tuple_sum(c->from, c->forward), c->up, c);
	set_camera_transform(c, view);
	app->data_changed = true;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:48:31 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/09 18:03:53 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	change_camera_fov(t_app *app, double ydelta)
{
	double	fov_change;

	fov_change = ydelta * FOV_CHANGE * (M_PI / 180);
	app->scene->camera->fov -= fov_change;
	app->scene->camera->pixel_size = pixel_size(app->scene->camera);
	printf("fov: %lf\n", app->scene->camera->fov);
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

void	handle_looking_around(t_app *app)
{
	int32_t		x;
	int32_t		y;
	double		dx;
	double		dy;
	t_camera	*c;
	t_matrix4	view;

	c = app->scene->camera;
	mlx_set_cursor_mode(app->mlx, MLX_MOUSE_DISABLED);
	mlx_get_mouse_pos(app->mlx, &x, &y);
	if (doubles_are_equal(x, app->prev_mouse_x) && doubles_are_equal(y, app->prev_mouse_y))
		return ;
	dx = x - app->prev_mouse_x;
	dy = y - app->prev_mouse_y;
	app->prev_mouse_x = x;
	app->prev_mouse_y = y;
	c->yaw -= (dx * MOUSE_SPEED);
	c->pitch -= (dy * MOUSE_SPEED);
	c->forward = get_direction_from_angles(c->yaw, c->pitch);
	c->left = cross(c->up, c->forward);
	view = view_transform(c->from, tuple_sum(c->from, c->forward), c->up, c);
	set_camera_transform(c, view);
	app->moving = true;
	app->data_changed = true;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by juhana            #+#    #+#             */
/*   Updated: 2026/02/03 13:51:53 by juhana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_mouse_press(t_app *app, enum mouse_key key)
{
	if (key == MLX_MOUSE_BUTTON_LEFT)
	{
		app->left_mouse_down = true;
		mlx_get_mouse_pos(app->mlx, &app->prev_mouse_x, &app->prev_mouse_y);
		select_object_from_screen(app, &app->error);
	}
	else if (key == MLX_MOUSE_BUTTON_RIGHT)
	{
		app->right_mouse_down = true;
		mlx_set_cursor_mode(app->mlx, MLX_MOUSE_DISABLED);
		mlx_set_mouse_pos(app->mlx, app->prev_mouse_x, app->prev_mouse_y);
	}
}

void	handle_mouse_release(t_app *app, enum mouse_key key)
{
	if (key == MLX_MOUSE_BUTTON_LEFT)
		app->left_mouse_down = false;
	else if (key == MLX_MOUSE_BUTTON_RIGHT)
	{
		app->right_mouse_down = false;
		mlx_set_cursor_mode(app->mlx, MLX_MOUSE_NORMAL);
		mlx_set_mouse_pos(app->mlx,
			(app->scrn_w / 2), (app->scrn_h / 2));
	}
}

void	handle_toggle_keys(mlx_key_data_t keydata, t_app *app)
{
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		app->pixelate = !app->pixelate;
		restart_render(app);
	}
	else if (keydata.key == MLX_KEY_H && keydata.action == MLX_PRESS)
	{
		app->show_hud = !app->show_hud;
		if (!app->show_hud && app->hud)
		{
			mlx_delete_image(app->mlx, app->hud);
			app->hud = NULL;
		}
	}
	else if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		reset_camera_to_original(app);
}

void	reset_camera_to_original(t_app *app)
{
	app->scene->camera->from = app->scene->camera->original_from;
	app->scene->camera->to = app->scene->camera->original_to;
	app->scene->camera->up = app->scene->camera->original_up;
	app->scene->camera->fov = app->scene->camera->original_fov;
	app->scene->camera->transform = view_transform(
			app->scene->camera->from, app->scene->camera->to,
			app->scene->camera->up, app->scene->camera);
	init_camera_yaw_and_pitch(app->scene->camera);
	set_camera_transform(app->scene->camera,
		app->scene->camera->transform);
	restart_render(app);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:26:17 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/17 19:27:35 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	close_window_mouse(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	app->keep_rendering = false;
	exit_and_free_memory(EXIT_SUCCESS, app);
}

void	handle_keypress(mlx_key_data_t keydata, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		app->keep_rendering = false;
		exit_and_free_memory(EXIT_SUCCESS, app);
	}
	else if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
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
}

void	handle_mouse(
	enum mouse_key key, enum action action,
	enum modifier_key mod_key, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (action == MLX_PRESS && key == MLX_MOUSE_BUTTON_LEFT)
	{
		app->left_mouse_down = true;
		mlx_get_mouse_pos(app->mlx, &app->prev_mouse_x, &app->prev_mouse_y);
		select_object_from_screen(app, &app->error);
	}
	else if (action == MLX_RELEASE && key == MLX_MOUSE_BUTTON_LEFT)
		app->left_mouse_down = false;
	else if (action == MLX_PRESS && key == MLX_MOUSE_BUTTON_RIGHT)
	{
		app->right_mouse_down = true;
		mlx_set_cursor_mode(app->mlx, MLX_MOUSE_DISABLED);
		mlx_set_mouse_pos(app->mlx, app->prev_mouse_x, app->prev_mouse_y);
	}
	else if (action == MLX_RELEASE && key == MLX_MOUSE_BUTTON_RIGHT)
	{
		app->right_mouse_down = false;
		mlx_set_cursor_mode(app->mlx, MLX_MOUSE_NORMAL);
		mlx_set_mouse_pos(app->mlx,
			(app->monitor_width / 2), (app->monitor_height / 2));
	}
	(void)mod_key;
}

void	handle_mouse_scroll(double xdelta, double ydelta, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (mlx_is_key_down(app->mlx, MLX_KEY_LEFT_CONTROL))
		transform_light(app, ydelta);
	else if (mlx_is_key_down(app->mlx, MLX_KEY_F))
		change_camera_fov(app, ydelta);
	else if (app->selected_object)
	{
		if (mlx_is_key_down(app->mlx, MLX_KEY_LEFT_SHIFT))
			rotate_selected_object(app, ydelta);
		else
			resize_selected_object(app, ydelta);
	}
	(void)xdelta;
}

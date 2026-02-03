/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:26:17 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/03 13:49:25 by juhana           ###   ########.fr       */
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
	else
		handle_toggle_keys(keydata, app);
}

void	handle_mouse(
	enum mouse_key key, enum action action,
	enum modifier_key mod_key, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (action == MLX_PRESS)
		handle_mouse_press(app, key);
	else if (action == MLX_RELEASE)
		handle_mouse_release(app, key);
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

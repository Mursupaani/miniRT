/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:26:17 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/15 16:20:31 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "minirt.h"

static void	per_frame_loop(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (all_threads_finished_frame(app))
		display_finished_frame(app);
	if (all_threads_started_new_frame(app))
		app->start_next_frame = false;
	handle_movement(app);
	if (app->right_mouse_down)
		handle_looking_around(app);
	if (app->left_mouse_down)
		move_oject_on_screen(app);
	if (app->data_changed)
	{
		restart_render(app);
		app->data_changed = false;
		app->moving = false;
	}
}

static void	close_window_mouse(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	app->keep_rendering = false;
	exit_and_free_memory(EXIT_SUCCESS, app);
}

static void	handle_keypress(mlx_key_data_t keydata, void *param)
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
}

static void	handle_mouse(enum mouse_key mouse_key, enum action action, enum modifier_key modifier_key, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (action == MLX_PRESS && mouse_key == MLX_MOUSE_BUTTON_LEFT)
	{
		app->left_mouse_down = true;
		mlx_get_mouse_pos(app->mlx, &app->prev_mouse_x, &app->prev_mouse_y);
		select_object_from_screen(app);
	}
	else if (action == MLX_RELEASE && mouse_key == MLX_MOUSE_BUTTON_LEFT)
		app->left_mouse_down = false;
	else if (action == MLX_PRESS && mouse_key == MLX_MOUSE_BUTTON_RIGHT)
	{
		app->right_mouse_down = true;
		mlx_set_cursor_mode(app->mlx, MLX_MOUSE_DISABLED);
		mlx_set_mouse_pos(app->mlx, app->prev_mouse_x, app->prev_mouse_y);
	}
	else if (action == MLX_RELEASE && mouse_key == MLX_MOUSE_BUTTON_RIGHT)
	{
		app->right_mouse_down = false;
		mlx_set_cursor_mode(app->mlx, MLX_MOUSE_NORMAL);
		mlx_set_mouse_pos(app->mlx, (app->monitor_width / 2), (app->monitor_height / 2));
	}
	(void)modifier_key;
}

static void	handle_mouse_scroll(double xdelta, double ydelta, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (mlx_is_key_down(app->mlx, MLX_KEY_LEFT_CONTROL))
		transform_light(app, ydelta);
	if (app->selected_object)
	{
		if (mlx_is_key_down(app->mlx, MLX_KEY_LEFT_SHIFT))
			rotate_selected_object(app, ydelta);
		else
			resize_selected_object(app, ydelta);
	}
	(void)xdelta;
}

void	initialize_hooks(t_app *app)
{
	mlx_close_hook(app->mlx, close_window_mouse, app);
	mlx_key_hook(app->mlx, handle_keypress, app);
	mlx_mouse_hook(app->mlx, handle_mouse, app);
	mlx_scroll_hook(app->mlx, handle_mouse_scroll, app);
	mlx_loop_hook(app->mlx, per_frame_loop, app);
}

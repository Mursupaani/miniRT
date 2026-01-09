/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:26:17 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/09 17:11:07 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	per_frame_loop(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	handle_movement(app);
	if (app->right_mouse_down)
		handle_looking_around(app);
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
		app->selected_object = select_object_from_screen(app);
	}
	else if (action == MLX_RELEASE && mouse_key == MLX_MOUSE_BUTTON_LEFT)
	{
		app->left_mouse_down = false;
		if (app->selected_object)
			app->selected_object = NULL;
	}
	else if (action == MLX_PRESS && mouse_key == MLX_MOUSE_BUTTON_RIGHT)
	{
		app->right_mouse_down = true;
		mlx_set_cursor_mode(app->mlx, MLX_MOUSE_DISABLED);
	}
	else if (action == MLX_RELEASE && mouse_key == MLX_MOUSE_BUTTON_RIGHT)
	{
		app->right_mouse_down = false;
		mlx_set_cursor_mode(app->mlx, MLX_MOUSE_NORMAL);
	}
	(void)modifier_key;
}

void	initialize_hooks(t_app *app)
{
	mlx_close_hook(app->mlx, close_window_mouse, app);
	mlx_key_hook(app->mlx, handle_keypress, app);
	mlx_mouse_hook(app->mlx, handle_mouse, app);
	mlx_loop_hook(app->mlx, per_frame_loop, app);
}

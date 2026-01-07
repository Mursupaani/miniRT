/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:26:17 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/07 15:13:21 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "minirt.h"
#include <stdlib.h>

static void	per_frame_loop(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (app->left_mouse_down)
		printf("held\n");
	if (mlx_is_key_down(app->mlx, MLX_KEY_UP))
		move_in_space(app, MLX_KEY_UP);
	if (mlx_is_key_down(app->mlx, MLX_KEY_DOWN))
		move_in_space(app, MLX_KEY_DOWN);
	if (mlx_is_key_down(app->mlx, MLX_KEY_RIGHT))
		move_in_space(app, MLX_KEY_RIGHT);
	if (mlx_is_key_down(app->mlx, MLX_KEY_LEFT))
		move_in_space(app, MLX_KEY_LEFT);

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
	// else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	// {
	// 	t_camera *c;
	// 	c = app->scene->camera;
	// 	c->from = tuple_sum(c->from, point(0, 0, 0.1));
	// 	c->to = tuple_sum(c->to, point(0, 0, 0.1));
	// 	set_camera_transform(c, view_transform(c->from, c->to, c->up, c));
	// 	restart_render(app);
	// }
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
		printf("pressed\n");
	}
	else if (action == MLX_RELEASE && mouse_key == MLX_MOUSE_BUTTON_LEFT)
	{
		app->left_mouse_down = false;
		if (app->selected_object)
			app->selected_object = NULL;
		printf("released\n");
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

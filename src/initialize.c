/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:35:03 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 15:46:11 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_app	*initialize_app(void)
{
	t_app	*app;

	app = ft_calloc(1, sizeof(t_app));
	if (!app)
		return (NULL);
	app->mlx = mlx_init(1, 1, "miniRT", true);
	if (!app->mlx)
		exit_and_free_memory(ERROR_MLX_INIT, app);
	mlx_get_monitor_size(0, &app->monitor_width, &app->monitor_height);

	// NOTE: Uncomment two lines below for testing with different resolution.
	// app->monitor_width = 640;
	// app->monitor_height = 640;

	// NOTE: Uncomment two lines below for testing with Valgrind.
	// app->monitor_width = THREADS;
	// app->monitor_height = THREADS;

	mlx_set_window_size(app->mlx, app->monitor_width, app->monitor_height);
	app->img_buffers[0] = mlx_new_image(app->mlx, app->monitor_width, app->monitor_height);
	app->img_buffers[1] = mlx_new_image(app->mlx, app->monitor_width, app->monitor_height);
	if (!app->img_buffers[0] || !app->img_buffers[1])
		exit_and_free_memory(ERROR_MLX_IMG_INIT, app);
	mlx_image_to_window(app->mlx, app->img_buffers[0], 0, 0);
	mlx_image_to_window(app->mlx, app->img_buffers[1], 0, 0);
	app->img_buffers[0]->instances[0].enabled = false;
	app->img_buffers[1]->instances[0].enabled = true;
	app->bg_img_index = 0;
	app->img = app->img_buffers[app->bg_img_index];
	initialize_hooks(app);
	app->pixel_count = app->img->width * app->img->height * sizeof(int);
	app->keep_rendering = true;
	app->pixelate = true;
	app->go_wait = false;
	app->left_mouse_down = false;
	app->right_mouse_down = false;
	app->start_next_frame = false;
	app->moving = false;
	app->data_changed = false;
	app->show_hud = true;
	return (app);
}

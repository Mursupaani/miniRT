/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:35:03 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/30 15:43:43 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	initialize_hooks(t_app *app)
{
	mlx_close_hook(app->mlx, close_window_mouse, app);
	mlx_key_hook(app->mlx, handle_keypress, app);
	mlx_mouse_hook(app->mlx, handle_mouse, app);
	mlx_scroll_hook(app->mlx, handle_mouse_scroll, app);
	mlx_loop_hook(app->mlx, per_frame_loop, app);
}

static void	init_values(t_app *app)
{
	app->img_buffers[0]->instances[0].enabled = false;
	app->img_buffers[1]->instances[0].enabled = true;
	app->bg_img_index = 0;
	app->img = app->img_buffers[app->bg_img_index];
	app->pixel_count = app->img->width * app->img->height;
	app->img_buffer_size = app->pixel_count * sizeof(int);
	app->keep_rendering = true;
	app->pixelate = true;
	app->go_wait = false;
	app->left_mouse_down = false;
	app->right_mouse_down = false;
	app->start_next_frame = false;
	app->moving = false;
	app->data_changed = false;
	app->show_hud = true;
	app->current_pixelate_scale = PIXELATE_SCALE;
	app->frame_done = false;
	app->ready_percent = 0;
}

static void	init_images(t_app *app)
{
	app->img_buffers[0] = mlx_new_image(
			app->mlx, app->scrn_w, app->scrn_h);
	app->img_buffers[1] = mlx_new_image(
			app->mlx, app->scrn_w, app->scrn_h);
	if (!app->img_buffers[0] || !app->img_buffers[1])
		exit_and_free_memory(ERROR_MLX_IMG_INIT, app);
	mlx_image_to_window(app->mlx, app->img_buffers[0], 0, 0);
	mlx_image_to_window(app->mlx, app->img_buffers[1], 0, 0);
}

t_app	*initialize_app(void)
{
	t_app	*app;

	app = ft_calloc(1, sizeof(t_app));
	if (!app)
		return (NULL);
	app->mlx = mlx_init(1, 1, "miniRT", true);
	if (!app->mlx)
		exit_and_free_memory(ERROR_MLX_INIT, app);
	mlx_get_monitor_size(0, &app->scrn_w, &app->scrn_h);
	init_images(app);
	mlx_set_window_size(app->mlx, app->scrn_w, app->scrn_h);
	initialize_hooks(app);
	init_values(app);
	return (app);
}

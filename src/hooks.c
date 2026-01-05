/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:26:17 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/02 16:37:59 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "libft.h"
#include "minirt.h"
#include <stdbool.h>

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
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		// app->pixelate = !app->pixelate;
		app->restart_render = false;
		app->go_back = true;
		int i = -1;
		while (++i < THREADS)
		{
			if (app->threads[i].ready == false)
			{
				i = -1;
				continue; ;
			}
		}
		app->go_back = false;
		app->restart_render = true;
		printf("command restart render\n");
	}
}

static void	handle_mouse(enum mouse_key mouse_key, enum action action, enum modifier_key modifier_key, void *param)
{
	t_app	*app;
	t_object *selected;

	app = (t_app *)param;
	if (action == MLX_PRESS && mouse_key == MLX_MOUSE_BUTTON_LEFT)
	{
		selected = select_object_from_screen(app);
		if (!selected)
			return ;
	}
	(void)action;
	(void)modifier_key;
}

void	initialize_hooks(t_app *app)
{
	mlx_close_hook(app->mlx, close_window_mouse, app);
	mlx_key_hook(app->mlx, handle_keypress, app);
	mlx_mouse_hook(app->mlx, handle_mouse, app);
}

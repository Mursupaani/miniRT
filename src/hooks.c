/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:26:17 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/15 15:32:58 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
}

void	initialize_hooks(t_app *app)
{
	mlx_close_hook(app->mlx, close_window_mouse, app);
	mlx_key_hook(app->mlx, handle_keypress, app);
}

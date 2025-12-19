/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:35:03 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/19 15:44:58 by anpollan         ###   ########.fr       */
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
	// app->monitor_width = 1024;
	// app->monitor_height = 640;

	// NOTE: Uncomment two lines below for testing with Valgrind.
	// app->monitor_width = 50;
	// app->monitor_height = 50;

	mlx_set_window_size(app->mlx, app->monitor_width, app->monitor_height);
	app->img = mlx_new_image(app->mlx, app->monitor_width, app->monitor_height);
	if (!app->img)
		exit_and_free_memory(ERROR_MLX_IMG_INIT, app);
	initialize_hooks(app);
	app->keep_rendering = true;
	return (app);
}

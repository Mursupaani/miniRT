/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:35:03 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/12 16:44:19 by juhana           ###   ########.fr       */
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
	mlx_set_window_size(app->mlx, app->monitor_width, app->monitor_height);
	app->img = mlx_new_image(app->mlx, app->monitor_width, app->monitor_height);
	if (!app->img)
		exit_and_free_memory(ERROR_MLX_IMG_INIT, app);
	return (app);
}

/*
	int	d = 200;
	app->monitor_width = d;
	app->monitor_height = d;
	mlx_set_window_size(app->mlx, d, d);
	app->img = mlx_new_image(app->mlx, d, d);

*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:35:03 by anpollan          #+#    #+#             */
/*   Updated: 2025/10/31 18:40:33 by anpollan         ###   ########.fr       */
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
	mlx_get_monitor_size(0, &app->monitor_width, &app->monitor_height);
	mlx_set_window_size(app->mlx, app->monitor_width, app->monitor_height);
	mlx_loop(app->mlx);
	return (app);
}

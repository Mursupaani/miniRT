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

static void	close_window(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	exit_and_free_memory(EXIT_SUCCESS, app);
}

void	initialize_hooks(t_app *app)
{
	mlx_close_hook(app->mlx, close_window, app);
}

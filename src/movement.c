/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:32:32 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/09 16:37:20 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_movement(t_app *app)
{
	if (mlx_is_key_down(app->mlx, MLX_KEY_UP))
		move_in_space(app, MLX_KEY_UP);
	if (mlx_is_key_down(app->mlx, MLX_KEY_DOWN))
		move_in_space(app, MLX_KEY_DOWN);
	if (mlx_is_key_down(app->mlx, MLX_KEY_RIGHT))
		move_in_space(app, MLX_KEY_RIGHT);
	if (mlx_is_key_down(app->mlx, MLX_KEY_LEFT))
		move_in_space(app, MLX_KEY_LEFT);
	if (all_threads_finished_frame(app))
		display_finished_frame(app);
	if (all_threads_started_new_frame(app))
		app->start_next_frame = false;
	app->moving = false;
}

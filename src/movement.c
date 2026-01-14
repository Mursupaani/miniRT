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

void	move_in_space(t_app *app, keys_t key)
{
	t_camera	*c;

	app->moving = true;
	c = app->scene->camera;
	if (key == MLX_KEY_UP)
	{
		c->from = tuple_sum(c->from, tuple_scale_multiply(c->forward, MOVEMENT_SPEED));
		c->to = tuple_sum(c->to, c->forward);
	}
	else if (key == MLX_KEY_DOWN)
	{
		c->from = tuple_sum(c->from, tuple_scale_multiply(c->forward, -MOVEMENT_SPEED));
		c->to = tuple_sum(c->to, c->forward);
	}
	else if (key == MLX_KEY_LEFT)
	{
		c->from = tuple_sum(c->from, tuple_scale_multiply(c->left, MOVEMENT_SPEED));
		c->to = tuple_sum(c->to, tuple_scale_multiply(c->left, MOVEMENT_SPEED));
	}
	else if (key == MLX_KEY_RIGHT)
	{
		c->from = tuple_sum(c->from, tuple_scale_multiply(c->left, -MOVEMENT_SPEED));
		c->to = tuple_sum(c->to, tuple_scale_multiply(c->left, -MOVEMENT_SPEED));
	}
	set_camera_transform(c, view_transform(c->from, c->to, c->up, c));
	app->data_changed = true;
}

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
}

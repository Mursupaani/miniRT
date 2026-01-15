/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:12:18 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/15 16:21:12 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	transform_light(t_app *app, double ydelta)
{
	t_light	*light;
	double	movement;

	light = app->scene->light;
	movement = ydelta * MOVEMENT_SPEED;
	if (mlx_is_key_down(app->mlx, MLX_KEY_X))
	{
		light->position.x += movement;
		app->data_changed = true;
	}
	else if (mlx_is_key_down(app->mlx, MLX_KEY_Y))
	{
		light->position.y += movement;
		app->data_changed = true;
	}
	else if (mlx_is_key_down(app->mlx, MLX_KEY_Z))
	{
		light->position.z += movement;
		app->data_changed = true;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:48:31 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/09 18:03:53 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_looking_around(t_app *app)
{
	int32_t		x;
	int32_t		y;
	double		dx;
	double		dy;
	t_camera	*c;

	c = app->scene->camera;
	mlx_set_cursor_mode(app->mlx, MLX_MOUSE_DISABLED);
	mlx_get_mouse_pos(app->mlx, &x, &y);
	dx = x - app->prev_mouse_x;
	dy = y - app->prev_mouse_y;
	app->prev_mouse_x = x;
	app->prev_mouse_y = y;
	c->yaw += dx;
	c->pitch += dy;
	c = app->scene->camera;
	view_transform(c->from, c->to, c->up, c);
	// printf("dx: %lf\n", dx);
	// printf("dy: %lf\n", dy);
}

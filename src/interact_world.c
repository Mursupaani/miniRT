/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_world.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:41:46 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/02 15:56:16 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*select_object(t_app *app)
{
	t_intersections	*xs;
	int				x;
	int				y;
	t_ray			r;

	mlx_get_mouse_pos(app->mlx, &x, &y);
	r = ray_for_pixel(app->scene->camera, x, y);
	xs = intersect_world(app->scene, r);
	if (!xs || xs->count == 0)
		return (NULL);
	return (xs->arr[0].object);
}

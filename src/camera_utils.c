/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:29:51 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 18:34:07 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_camera_pitch_and_yaw(t_camera *c)
{
	c->yaw = atan2(c->forward.z, c->forward.x) * (180 / M_PI);
	c->pitch = asin(c->forward.y) * (180 / M_PI);
	if (c->pitch > 89.999)
		c->pitch = 89.999;
	else if (c->pitch < -89.999)
		c->pitch = -89.999;
	if (c->yaw > 360)
		c->yaw -= 360;
	else if (c->yaw < 0)
		c->yaw += 360;
}

double	pixel_size(t_camera *camera)
{
	double	half_view;

	half_view = tan(camera->fov / 2);
	camera->aspect_ratio = (double)camera->hsize / camera->vsize;
	if (camera->aspect_ratio >= 1)
	{
		camera->half_width = half_view;
		camera->half_height = camera->half_width / camera->aspect_ratio;
	}
	else
	{
		camera->half_height = half_view;
		camera->half_width = camera->half_height / camera->aspect_ratio;
	}
	return ((camera->half_width * 2) / camera->hsize);
}

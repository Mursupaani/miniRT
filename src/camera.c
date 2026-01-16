/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:30:52 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 18:33:37 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera	*camera(int hsize, int vsize, double fov)
{
	t_camera	*camera;

	camera = ft_calloc(1, sizeof(t_camera));
	if (!camera)
		return (NULL);
	camera->hsize = hsize;
	camera->vsize = vsize;
	camera->fov = fov;
	camera->transform = matrix4_identity();
	camera->inverse_transform = camera->transform;
	camera->pixel_size = pixel_size(camera);
	camera->yaw = 0;
	camera->pitch = 0;
	return (camera);
}

static t_ray	calculate_ray(t_camera *c, double world_x, double world_y)
{
	t_point		pixel;
	t_point		origin;
	t_vector	direction;

	pixel = matrix4_and_tuple_multiply(
			c->inverse_transform, point(world_x, world_y, -1));
	origin = matrix4_and_tuple_multiply(
			c->inverse_transform, point(0, 0, 0));
	direction = normalize(tuple_subtract(pixel, origin));
	return (ray(origin, direction));
}

t_ray	ray_for_pixel(t_camera *c, int px, int py)
{
	double	xoffset;
	double	yoffset;
	double	world_x;
	double	world_y;

	xoffset = ((double)px + 0.5) * c->pixel_size;
	yoffset = ((double)py + 0.5) * c->pixel_size;
	world_x = c->half_width - xoffset;
	world_y = c->half_height - yoffset;
	return (calculate_ray(c, world_x, world_y));
}

void	set_camera_transform(t_camera *camera, t_matrix4 transform)
{
	camera->transform = transform;
	camera->inverse_transform = matrix4_invert(transform);
}

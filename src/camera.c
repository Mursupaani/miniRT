/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:30:52 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/11 14:36:45 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	float pixel_size(t_camera *camera)
{
	float	half_view;
	float	aspect_ratio;

	half_view = tanf(camera->fov / 2);
	aspect_ratio = (float)camera->hsize / camera->vsize;
	if (aspect_ratio >= 1)
	{
		camera->half_width = half_view;
		camera->half_height = camera->half_width / aspect_ratio;
	}
	else
	{
		camera->half_height = half_view;
		camera->half_width = camera->half_height / aspect_ratio;
	}
	return (camera->half_width * 2) / camera->hsize;
}

t_camera	*camera(int hsize, int vsize, float fov)
{
	t_camera	*camera;

	camera = ft_calloc(1, sizeof(t_camera));
	if (!camera)
		return (NULL);
	camera->hsize = hsize;
	camera->vsize = vsize;
	camera->fov = fov;
	camera->transform = matrix4_identity();
	camera->pixel_size = pixel_size(camera);
	return (camera);
}

static t_ray	calculate_ray(t_camera *c, float world_x, float world_y)
{
	t_point		pixel;
	t_point		origin;
	t_vector	direction;
	t_matrix4	inverse_camera_transform;

	inverse_camera_transform = matrix4_invert(c->transform);
	pixel = matrix4_and_tuple_multiply(
			inverse_camera_transform, point(world_x, world_y, -1));
	origin = matrix4_and_tuple_multiply(
			inverse_camera_transform, point(0, 0, 0));
	direction = normalize(tuple_subtract(pixel, origin));
	return (ray(origin, direction));
}

t_ray	ray_for_pixel(t_camera *c, int px, int py)
{
	float	xoffset;
	float	yoffset;
	float	world_x;
	float	world_y;

	xoffset = ((float)px + 0.5) * c->pixel_size;
	yoffset = ((float)py + 0.5) * c->pixel_size;
	world_x = c->half_width - xoffset;
	world_y = c->half_height - yoffset;
	return (calculate_ray(c, world_x, world_y));
}

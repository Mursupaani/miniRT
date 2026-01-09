/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:30:52 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/09 18:02:25 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	double pixel_size(t_camera *camera)
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
	return (camera->half_width * 2) / camera->hsize;
}

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
	// t_matrix4	inverse_camera_transform;

	pixel = matrix4_and_tuple_multiply(
			c->inverse_transform, point(world_x, world_y, -1));
	origin = matrix4_and_tuple_multiply(
			c->inverse_transform, point(0, 0, 0));
	direction = normalize(tuple_subtract(pixel, origin));
	// FIXME: Backup. Started using set_camera_transform() so every pixel doesn't have
	// to recalculate inversce_transform.
	// inverse_camera_transform = matrix4_invert(c->transform);
	// pixel = matrix4_and_tuple_multiply(
			// inverse_camera_transform, point(world_x, world_y, -1));
	// origin = matrix4_and_tuple_multiply(
			// inverse_camera_transform, point(0, 0, 0));
	// direction = normalize(tuple_subtract(pixel, origin));
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

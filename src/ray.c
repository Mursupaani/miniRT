/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:50:39 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 20:50:40 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray(t_point origin, t_vector direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_point	ray_position(t_ray ray, double t)
{
	t_vector	distance;

	distance = tuple_scale_multiply(ray.direction, t);
	return (tuple_sum(ray.origin, distance));
}

t_ray	ray_transform(t_ray ray, t_matrix4 matrix)
{
	t_ray	new_ray;

	new_ray.origin = matrix4_and_tuple_multiply(matrix, ray.origin);
	new_ray.direction = matrix4_and_tuple_multiply(matrix, ray.direction);
	return (new_ray);
}

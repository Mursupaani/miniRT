/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:23:50 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 20:26:15 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	cone_normal_at(t_object *cone, t_point local_point)
{
	double	dist;
	double	y;

	dist = pow(local_point.x, 2) + pow(local_point.z, 2);
	if (dist < 1 && local_point.y >= cone->maximum - EPSILON)
		return (vector(0, 1, 0));
	else if (dist < 1 && local_point.y <= cone->minimum + EPSILON)
		return (vector(0, -1, 0));
	y = sqrt(pow(local_point.x, 2) + pow(local_point.z, 2));
	if (local_point.y > 0)
		y = -y;
	return (vector(local_point.x, y, local_point.z));
}

t_vector	cylinder_normal_at(t_object *cylinder, t_point local_point)
{
	double	dist;

	dist = pow(local_point.x, 2) + pow(local_point.z, 2);
	if (dist < 1 && local_point.y >= cylinder->maximum - EPSILON)
		return (vector(0, 1, 0));
	else if (dist < 1 && local_point.y <= cylinder->minimum + EPSILON)
		return (vector(0, -1, 0));
	return (vector(local_point.x, 0, local_point.z));
}

t_vector	sphere_normal_at(t_object *sphere, t_point local_point)
{
	t_vector	local_normal;

	(void)sphere;
	local_normal = tuple_subtract(local_point, point(0, 0, 0));
	return (local_normal);
}

t_vector	plane_normal_at(t_object *plane, t_point local_point)
{
	t_vector	local_normal;

	(void)local_point;
	local_normal = vector(0, 1, 0);
	(void)plane;
	return (local_normal);
}

t_vector	cube_normal_at(t_object *cube, t_point local_point)
{
	double		maxc;
	t_vector	local_normal;

	maxc = max_absolute_coord_component(
			local_point.x, local_point.y, local_point.z);
	if (doubles_are_equal(maxc, fabs(local_point.x)))
		local_normal = vector(local_point.x, 0, 0);
	else if (doubles_are_equal(maxc, fabs(local_point.y)))
		local_normal = vector(0, local_point.y, 0);
	else
		local_normal = vector(0, 0, local_point.z);
	(void)cube;
	return (local_normal);
}

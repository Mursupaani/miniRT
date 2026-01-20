/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 19:00:35 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 19:03:41 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	check_cylinder_cap(t_ray local_ray, double t)
{
	double	x;
	double	z;

	x = local_ray.origin.x + t * local_ray.direction.x;
	z = local_ray.origin.z + t * local_ray.direction.z;
	return ((x * x + z * z) <= 1);
}

t_intersections	*intersect_cylinder_caps(
		t_object *cylinder, t_ray local_ray,
		t_intersections *xs, atomic_int *err)
{
	double	t;

	if (cylinder->closed == false
		|| doubles_are_equal(local_ray.direction.y, 0))
		return (xs);
	t = (cylinder->minimum - local_ray.origin.y) / local_ray.direction.y;
	if (check_cylinder_cap(local_ray, t))
		xs = add_intersection_to_arr(intersection(t, cylinder), xs, err);
	t = (cylinder->maximum - local_ray.origin.y) / local_ray.direction.y;
	if (check_cylinder_cap(local_ray, t))
		xs = add_intersection_to_arr(intersection(t, cylinder), xs, err);
	return (xs);
}

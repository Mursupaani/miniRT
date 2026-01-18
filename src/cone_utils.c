/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:40:00 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 18:42:56 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	check_cone_cap(t_ray local_ray, double t, double limit)
{
	double	x;
	double	z;

	x = local_ray.origin.x + t * local_ray.direction.x;
	z = local_ray.origin.z + t * local_ray.direction.z;
	return ((x * x + z * z) <= limit * limit);
}

t_intersections	*intersect_cone_caps(
		t_object *cone, t_ray local_ray, t_intersections *xs, atomic_int *err)
{
	double	t;

	if (cone->closed == false || doubles_are_equal(local_ray.direction.y, 0))
		return (xs);
	t = (cone->minimum - local_ray.origin.y) / local_ray.direction.y;
	if (check_cone_cap(local_ray, t, cone->minimum))
		xs = add_intersection_to_arr(intersection(t, cone), xs, err);
	t = (cone->maximum - local_ray.origin.y) / local_ray.direction.y;
	if (check_cone_cap(local_ray, t, cone->maximum))
		xs = add_intersection_to_arr(intersection(t, cone), xs, err);
	return (xs);
}

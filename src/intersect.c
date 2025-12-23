/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 14:55:17 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/22 12:21:58 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersections *intersect(t_object *obj, t_ray ray)
{
	t_ray	local_ray;

	local_ray = ray_transform(ray, obj->inverse_transform);
	if (!obj)
		return (NULL);
	if (obj->type == SPHERE)
		return (intersect_sphere(obj, local_ray));
	else if (obj->type == PLANE)
		return (intersect_plane(obj, local_ray));
	else if (obj->type == CUBE)
		return (intersect_cube(obj, local_ray));
	else if (obj->type == CYLINDER)
		return (intersect_cylinder(obj, local_ray));
	else if (obj->type == CONE)
		return (intersect_cone(obj, local_ray));
	else
		return (NULL);
}

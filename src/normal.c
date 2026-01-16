/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:41:48 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 20:24:32 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	local_normal_at(t_object *obj, t_point local_point)
{
	if (obj->type == SPHERE)
		return (sphere_normal_at(obj, local_point));
	else if (obj->type == PLANE)
		return (plane_normal_at(obj, local_point));
	else if (obj->type == CUBE)
		return (cube_normal_at(obj, local_point));
	else if (obj->type == CYLINDER)
		return (cylinder_normal_at(obj, local_point));
	else if (obj->type == CONE)
		return (cone_normal_at(obj, local_point));
	else
		return (vector(DBL_MAX, DBL_MAX, DBL_MAX));
}

t_vector	normal_at(t_object *obj, t_point world_point)
{
	t_point		local_point;
	t_vector	local_normal;
	t_vector	world_normal;

	local_point = matrix4_and_tuple_multiply(
			obj->inverse_transform, world_point);
	local_normal = local_normal_at(obj, local_point);
	if (obj->bump_map.has_bump_map)
		apply_bump_map_on_normal(obj, &local_normal, local_point);
	world_normal = matrix4_and_tuple_multiply(
			obj->inverse_transpose, local_normal);
	world_normal.w = 0;
	return (normalize(world_normal));
}

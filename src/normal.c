/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:41:48 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/10 18:43:16 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	sphere_normal_at(t_object *sphere, t_point world_point)
{
	t_point		object_point;
	t_vector	object_normal;
	t_vector	world_normal;

	object_point = matrix4_and_tuple_multiply(
				sphere->inverse_transform, world_point);
	object_normal = tuple_subtract(object_point, point(0, 0, 0));
	world_normal = matrix4_and_tuple_multiply(
		matrix4_transpose(sphere->inverse_transform), object_normal);
	world_normal.w = 0;
	return (normalize(world_normal));
}

t_vector	normal_at(t_object *obj, t_point world_point)
{
	if (obj->type == SPHERE)
		return (sphere_normal_at(obj, world_point));
	else
		return (normalize(vector(FLT_MAX, FLT_MAX, FLT_MAX)));
}

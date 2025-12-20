/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:41:48 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/20 13:30:14 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	cylinder_normal_at(t_object *cylinder, t_point world_point)
{
	(void)cylinder;
	return (vector(world_point.x, 0, world_point.z));
}

static t_vector	sphere_normal_at(t_object *sphere, t_point world_point)
{
	t_point		object_point;
	t_vector	object_normal;
	t_vector	world_normal;

	object_point = matrix4_and_tuple_multiply(
				sphere->inverse_transform, world_point);
	object_normal = tuple_subtract(object_point, point(0, 0, 0));
	world_normal = matrix4_and_tuple_multiply(
		sphere->inverse_transpose, object_normal);
	world_normal.w = 0;
	return (normalize(world_normal));
}

static t_vector	plane_normal_at(t_object *plane, t_point world_point)
{
	t_vector	object_normal;
	t_vector	world_normal;

	(void)world_point;
	object_normal = vector(0, 1, 0);
	world_normal = matrix4_and_tuple_multiply(
		plane->inverse_transpose, object_normal);
	world_normal.w = 0;
	return (normalize(world_normal));
}

t_vector	cube_normal_at(t_object *cube, t_point world_point)
{
	double		maxc;
	t_vector	object_normal;
	t_vector	world_normal;

	
	maxc = max_absolute_coord_component(world_point.x, world_point.y, world_point.z);
	if (doubles_are_equal(maxc, fabs(world_point.x)))
		object_normal = vector(world_point.x, 0, 0);
	else if (doubles_are_equal(maxc, fabs(world_point.y)))
		object_normal = vector(0, world_point.y, 0);
	else
		object_normal = vector(0, 0, world_point.z);
	world_normal = matrix4_and_tuple_multiply(
		cube->inverse_transpose, object_normal);
	world_normal.w = 0;
	return (normalize(world_normal));
}

t_vector	normal_at(t_object *obj, t_point world_point)
{
	if (obj->type == SPHERE)
		return (sphere_normal_at(obj, world_point));
	else if (obj->type == PLANE)
		return (plane_normal_at(obj, world_point));
	else if (obj->type == CUBE)
		return (cube_normal_at(obj, world_point));
	else if (obj->type == CYLINDER)
		return (cylinder_normal_at(obj, world_point));
	else
		return (vector(DBL_MAX, DBL_MAX, DBL_MAX));
}

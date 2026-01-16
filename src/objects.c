/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:26:45 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 20:28:56 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_transform(t_object *object, t_matrix4 transform)
{
	if (!object)
		return ;
	object->transform = matrix4_multiply(transform, object->transform);
	object->inverse_transform = matrix4_invert(object->transform);
	object->inverse_transpose = matrix4_transpose(object->inverse_transform);
}

void	set_transform(t_object *object, t_matrix4 transform)
{
	if (!object)
		return ;
	object->transform = transform;
	object->inverse_transform = matrix4_invert(transform);
	object->inverse_transpose = matrix4_transpose(object->inverse_transform);
}

static void	set_min_max_closed(t_object *obj, t_object_type type)
{
	if (type == CYLINDER || type == CONE)
	{
		obj->minimum = -INFINITY;
		obj->maximum = INFINITY;
		obj->closed = false;
	}
	else
	{
		obj->minimum = 0;
		obj->maximum = 0;
		obj->closed = true;
	}
}

t_object	*object_new(t_object_type type)
{
	t_object	*obj;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->type = type;
	obj->center = point(0, 0, 0);
	obj->diameter = 1;
	obj->height = 1;
	obj->material = material();
	obj->transform = matrix4_identity();
	obj->inverse_transform = obj->transform;
	obj->inverse_transpose = obj->transform;
	set_min_max_closed(obj, type);
	return (obj);
}

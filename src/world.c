/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:31:17 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/12 14:20:30 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_object	**copy_objects_to_array(t_object **old_arr, t_object **new_arr, t_object *new)
{
	int	i;

	if (old_arr)
	{
		i = -1;
		while (old_arr[++i])
			new_arr[i] = old_arr[i];
		free_object_array(old_arr);
	}
	else
		i = 0;
	new_arr[i++] = new;
	new_arr[i] = NULL;
	return (new_arr);
}

t_object	**world_add_object(t_world *w, t_object *obj)
{
	t_object	**temp;

	if (!w || !obj)
		return (NULL);
	w->object_count++;
	temp = w->objects;
	w->objects = ft_calloc(1, sizeof(t_object *) * (w->object_count + 1));
	if (!w->objects)
	{
		w->object_count = -1;
		return (NULL);
	}
	w->objects = copy_objects_to_array(temp, w->objects, obj);
	return (w->objects);
}

t_world	*world()
{
	t_world	*w;

	w = ft_calloc(1, sizeof(t_world));
	if (!w)
		return (NULL);
	w->object_count = 0;
	return (w);
}

t_world	*default_world()
{
	t_world	*w;
	t_matrix4 transform;

	w = world();
	if (!w)
		return (NULL);
	w->light = point_light(point(-10, 10, -10), color(1, 1, 1));
	if (!w->light)
		return (NULL);
	w->objects = ft_calloc(1, sizeof(t_object) * 3);
	if (!w->objects)
		return (NULL);
	w->objects[0] = sphere_new();
	w->objects[0]->material.color = color(0.8, 1.0, 0.6);
	w->objects[0]->material.diffuse = 0.7;
	w->objects[0]->material.specular = 0.2;
	w->objects[1] = sphere_new();
	w->objects[2] = NULL;
	w->object_count = 2;
	transform = scaling_matrix4(0.5, 0.5, 0.5);
	set_transform(w->objects[1], transform);
	return (w);
}

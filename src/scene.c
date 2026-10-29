/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:31:17 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/05 11:21:36 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_object	**copy_objects_to_array(
		t_object **old_arr, t_object **new_arr, t_object *new)
{
	int	i;

	if (old_arr)
	{
		i = -1;
		while (old_arr[++i])
			new_arr[i] = old_arr[i];
		free(old_arr);
	}
	else
		i = 0;
	new_arr[i++] = new;
	new_arr[i] = NULL;
	return (new_arr);
}

t_object	**add_object_to_scene(t_object *obj, t_scene *s)
{
	t_object	**temp;

	if (!s || !obj)
		return (NULL);
	s->object_count++;
	temp = s->objects;
	s->objects = ft_calloc(1, sizeof(t_object *) * (s->object_count + 1));
	if (!s->objects)
	{
		s->object_count = -1;
		return (NULL);
	}
	s->objects = copy_objects_to_array(temp, s->objects, obj);
	return (s->objects);
}

t_scene	*scene(void)
{
	t_scene	*s;

	s = ft_calloc(1, sizeof(t_scene));
	if (!s)
		return (NULL);
	s->object_count = 0;
	return (s);
}

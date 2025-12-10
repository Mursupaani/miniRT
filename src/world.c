/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:31:17 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/09 15:51:58 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

t_world	*world()
{
	t_world	*w;

	w = ft_calloc(1, sizeof(t_world));
	if (!w)
		return (NULL);
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
	w->objects = ft_calloc(1, sizeof(t_object) * 2);
	if (!w->objects)
		return (NULL);
	w->objects[0] = sphere_new();
	w->objects[0]->material.color = color(0.8, 1.0, 0.6);
	w->objects[0]->material.diffuse = 0.7;
	w->objects[0]->material.specular = 0.2;
	w->objects[1] = sphere_new();
	transform = scaling_matrix4(0.5, 0.5, 0.5);
	set_transform(w->objects[1], transform);
	return (w);
}

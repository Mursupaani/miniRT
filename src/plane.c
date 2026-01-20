/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:31:27 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/17 16:31:28 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*plane_new(void)
{
	return (object_new(PLANE));
}

t_intersections	*intersect_plane(
		t_object *plane, t_ray local_ray, atomic_int *err)
{
	t_intersections	*xs;
	double			t;

	if (fabs(local_ray.direction.y) < EPSILON)
		return (NULL);
	t = -local_ray.origin.y / local_ray.direction.y;
	xs = ft_calloc(1, sizeof(t_intersections));
	if (!xs)
		return (memory_alloc_error(err));
	xs->count = 1;
	xs->arr = ft_calloc(1, sizeof(t_intersection));
	if (!xs->arr)
	{
		free(xs);
		return (memory_alloc_error(err));
	}
	xs->arr[0] = intersection(t, plane);
	return (xs);
}

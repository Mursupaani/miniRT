/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:36:27 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/10 17:44:44 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_computations	prepare_computations(t_intersection x, t_ray r)
{
	t_computations	comps;
	
	comps.t = x.t;
	comps.object = x.object;
	comps.point = ray_position(r, comps.t);
	comps.eyev = tuple_negate(r.direction);
	comps.normalv = normal_at(comps.object, comps.point);
	if (dot(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = tuple_negate(comps.normalv);
	}
	else
		comps.inside = false;
	return (comps);
}

static t_intersection	*add_intersection(
				t_intersections *cur, t_intersections *xs)
{
	t_intersection *temp;
	int				i;

	if (!cur || !xs)
		return (NULL);
	if (xs->count == 2)
	{
		xs->arr = malloc(sizeof(t_intersection) * 2);
		xs->arr[0] = cur->arr[0];
		xs->arr[1] = cur->arr[1];
	}
	else
	{
		temp = xs->arr;
		xs->arr = malloc(sizeof(t_intersection) * (xs->count));
		if (!xs->arr)
		{
			free(temp);
			return (NULL);
		}
		i = -1;
		while (++i < xs->count - 2)
			xs->arr[i] = temp[i];
		free(temp);
		xs->arr[i++] = cur->arr[0];
		xs->arr[i] = cur->arr[1];
	}
	return (xs->arr);
}

t_intersections *intersect_world(t_world *w, t_ray r)
{
	t_intersections	*xs;
	t_intersections	*current;
	int				i;

	if (!w)
		return (NULL);
	xs = malloc(sizeof(t_intersections));
	if (!xs)
		return (NULL);
	xs->arr = NULL;
	xs->count = 0;
	i = -1;
	while (w->objects[++i])
	{
		current = intersect(w->objects[i], r);
		if (!current)
			continue ;
		xs->count += current->count;
		xs->arr = add_intersection(current, xs);
		free_intersections(current);
		quick_sort_intersections(xs->arr, 0, xs->count - 1);
	}
	return (xs);
}

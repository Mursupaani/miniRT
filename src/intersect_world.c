/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:36:27 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/17 11:47:11 by anpollan         ###   ########.fr       */
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
	comps.reflectv = reflect(r.direction, comps.normalv);
	if (dot(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = tuple_negate(comps.normalv);
	}
	else
		comps.inside = false;
	comps.over_point = tuple_sum(comps.point, tuple_scale_multiply(comps.normalv, EPSILON));
	comps.shadowed = false;
	return (comps);
}

static t_intersection	*add_intersection(
				t_intersections *cur, t_intersections *xs, int old_xs_count)
{
	t_intersection *temp;
	int				i;

	if (!cur || !xs)
		return (NULL);
	if (xs->arr == NULL)
	{
		xs->arr = malloc(sizeof(t_intersection) * xs->count);
		if (!xs->arr)
			return (NULL);
		i = -1;
		while (++i < xs->count)
			xs->arr[i] = cur->arr[i];
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
		while (++i < old_xs_count)
			xs->arr[i] = temp[i];
		free(temp);
		--i;
		while (++i < xs->count)
			xs->arr[i] = cur->arr[i - old_xs_count];
	}
	return (xs->arr);
}

t_intersections *intersect_world(t_world *w, t_ray r)
{
	t_intersections	*xs;
	t_intersections	*current;
	int				i;
	int				old_xs_count;

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
		old_xs_count = xs->count;
		xs->count += current->count;
		xs->arr = add_intersection(current, xs, old_xs_count);
		free_intersections(current);
		quick_sort_intersections(xs->arr, 0, xs->count - 1);
	}
	return (xs);
}

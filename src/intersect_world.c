/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:36:27 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 19:52:51 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_intersection	*append_current_intersections_to_array(
		t_intersections *xs, t_intersections *cur, int old_xs_count)
{
	t_intersection	*temp;
	int				i;

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
	return (xs->arr);
}

static t_intersection	*copy_current_intersections_to_new_array(
		t_intersections *xs, t_intersections *cur)
{
	int	i;

	xs->arr = malloc(sizeof(t_intersection) * xs->count);
	if (!xs->arr)
		return (NULL);
	i = -1;
	while (++i < xs->count)
		xs->arr[i] = cur->arr[i];
	return (xs->arr);
}

static t_intersection	*add_intersection(
		t_intersections *cur, t_intersections *xs, int old_xs_count)
{
	if (!cur || !xs)
		return (NULL);
	if (xs->arr == NULL)
	{
		copy_current_intersections_to_new_array(xs, cur);
		if (xs->arr == NULL)
			return (NULL);
	}
	else
	{
		append_current_intersections_to_array(xs, cur, old_xs_count);
		if (!xs->arr)
			return (NULL);
	}
	return (xs->arr);
}

t_intersections	*intersect_world(t_world *w, t_ray r)
{
	t_intersections	*xs;
	t_intersections	*current;
	int				i;
	int				old_xs_count;

	if (!w)
		return (NULL);
	xs = ft_calloc(1, sizeof(t_intersections));
	if (!xs)
		return (NULL);
	i = -1;
	while (w->objects[++i])
	{
		current = intersect(w->objects[i], r);
		if (!current)
			continue ;
		old_xs_count = xs->count;
		xs->count += current->count;
		xs->arr = add_intersection(current, xs, old_xs_count);
		free_intersections(&current);
		quick_sort_intersections(xs->arr, 0, xs->count - 1);
	}
	return (xs);
}

// FIXME: Old function. Left here so that previous tests don't fail.
t_computations	prepare_computations_old(t_intersection x, t_ray r)
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
	comps.over_point = tuple_sum(
			comps.point, tuple_scale_multiply(comps.normalv, EPSILON));
	comps.shadowed = false;
	return (comps);
}

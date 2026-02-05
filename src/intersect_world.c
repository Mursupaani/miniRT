/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:36:27 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/21 13:42:54 by juhana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_intersection	*append_current_intersections_to_array(
		t_intersections *xs, t_intersections *cur,
		int old_xs_count, atomic_int *err)
{
	t_intersection	*temp;
	int				i;

	temp = xs->arr;
	xs->arr = malloc(sizeof(t_intersection) * (xs->count));
	if (!xs->arr)
	{
		free(temp);
		return (memory_alloc_error(err));
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
		t_intersections *xs, t_intersections *cur, atomic_int *err)
{
	int	i;

	xs->arr = malloc(sizeof(t_intersection) * xs->count);
	if (!xs->arr)
		return (memory_alloc_error(err));
	i = -1;
	while (++i < xs->count)
		xs->arr[i] = cur->arr[i];
	return (xs->arr);
}

static t_intersection	*add_intersection(
		t_intersections *cur, t_intersections *xs,
		int old_xs_count, atomic_int *err)
{
	if (!cur || !xs)
		return (NULL);
	if (xs->arr == NULL)
	{
		copy_current_intersections_to_new_array(xs, cur, err);
		if (*err)
			return (NULL);
	}
	else
	{
		append_current_intersections_to_array(xs, cur, old_xs_count, err);
		if (*err)
			return (NULL);
	}
	return (xs->arr);
}

static void	intersect_world_objects(
		t_scene *w, t_ray r, t_intersections *xs, atomic_int *err)
{
	t_intersections	*current;
	int				old_xs_count;
	int				i;

	if (!w->objects)
		return ;
	i = -1;
	while (w->objects[++i])
	{
		current = intersect(w->objects[i], r, err);
		if (!current || *err)
		{
			if (*err)
				return ;
			continue ;
		}
		old_xs_count = xs->count;
		xs->count += current->count;
		xs->arr = add_intersection(current, xs, old_xs_count, err);
		if (*err)
			return ;
		free_intersections(&current);
		quick_sort_intersections(xs->arr, 0, xs->count - 1);
	}
}

t_intersections	*intersect_world(t_scene *w, t_ray r, atomic_int *err)
{
	t_intersections	*xs;

	if (!w)
		return (NULL);
	xs = ft_calloc(1, sizeof(t_intersections));
	if (!xs)
		return (memory_alloc_error(err));
	intersect_world_objects(w, r, xs, err);
	if (*err)
		return (NULL);
	return (xs);
}

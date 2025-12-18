/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_computations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:33:45 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/18 15:05:47 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	void	add_item(t_intersection *x, t_intersection **containers)
{
	int	i;

	i = 0;
	while (containers[i])
		i++;
	containers[i] = x;
}

static	void remove_item(int i, t_intersection **containers, int containers_items)
{
	containers[i] = NULL;
	while (++i < containers_items)
	{
		if (containers[i])
			containers[i - 1] = containers[i];
	}
}

static void	handle_item_in_container(t_intersections *xs, t_intersection **containers, int *containers_items, int i)
{
	int		j;
	bool	found;

	j = -1;
	found = false;
	while (containers[++j])
	{
		if (xs->arr[i].object->type == containers[j]->object->type
			&& matrix4s_are_equal(xs->arr[i].object->transform, containers[j]->object->transform))
		{
			found = true;
			break ;
		}
	}
	if (found)
	{
		remove_item(j, containers, *containers_items);
		(*containers_items)--;
	}
	else
	{
		add_item(&xs->arr[i], containers);
		(*containers_items)++;
	}
}

static bool	get_n1_and_n2(
			t_intersection x, t_intersections *xs, t_computations *comps)
{
	t_intersection	**containers;
	int				i;
	int				containers_items;

	containers = ft_calloc(1, sizeof(t_intersection *) * xs->count + 1);
	containers_items = 0;
	if (!containers)
		return (false);
	i = -1;
	while (++i < xs->count)
	{
		if (xs->arr[i].object->type == x.object->type && xs->arr[i].t == x.t )
			handle_n1(comps, containers);
		handle_item_in_container(xs, containers, &containers_items, i);
		if (xs->arr[i].object->type == x.object->type && xs->arr[i].t == x.t )
		{
			handle_n2(comps, containers);
			break ;
		}
	}
	return (true);
}

t_computations	prepare_computations(
			t_intersection x, t_ray r, t_intersections *xs)
{
	t_computations	comps;
	
	comps.t = x.t;
	comps.object = x.object;
	comps.point = ray_position(r, comps.t);
	comps.eyev = tuple_negate(r.direction);
	comps.normalv = normal_at(comps.object, comps.point);
	comps.reflectv = reflect(r.direction, comps.normalv);
	// If malloc fails in get_n1_and_n2?
	get_n1_and_n2(x, xs, &comps);
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

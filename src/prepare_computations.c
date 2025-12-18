/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_computations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:33:45 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/18 14:33:55 by anpollan         ###   ########.fr       */
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

static int	containers_has_item(t_intersection *x, t_intersection **containers)
{
	int	i;

	i = -1;
	while (containers[++i])
	{
		if (x->object->type == containers[i]->object->type
			&& matrix4s_are_equal(x->object->transform, containers[i]->object->transform))
			return (i);
	}
	return (-1);
}

static bool	get_n1_and_n2(
			t_intersection x, t_intersections *xs, t_computations *comps)
{
	t_intersection	**containers;
	int				i;
	int				j;
	int				containers_items;

	containers = ft_calloc(1, sizeof(t_intersection *) * xs->count + 1);
	containers_items = 0;
	// Exit app if malloc fails.
	if (!containers)
		return (false);
	i = -1;
	while (++i < xs->count)
	{
		if (xs->arr[i].object->type == x.object->type && xs->arr[i].t == x.t )
		{
			if (containers[0] == NULL)
				comps->n1 = 1;
			else
			{
				j = 0;
				while (containers[j])
					j++;
				comps->n1 = containers[--j]->object->material.refractive_index;
			}
		}
		int indx = containers_has_item(&xs->arr[i], containers);
		if (indx != -1)
		{
			remove_item(indx, containers, containers_items);
			containers_items--;
		}
		else
		{
			add_item(&xs->arr[i], containers);
			containers_items++;
		}
		if (xs->arr[i].object->type == x.object->type && xs->arr[i].t == x.t )
		{
			if (containers[0] == NULL)
				comps->n2 = 1;
			else
			{
				j = 0;
				while (containers[j])
					j++;
				comps->n2 = containers[--j]->object->material.refractive_index;
			}
			break ;
		}
	}
	return (false);
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

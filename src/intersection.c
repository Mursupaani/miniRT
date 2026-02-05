/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:28:15 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/19 16:39:53 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersections	*malloc_intersections(int xs_count, atomic_int *err)
{
	t_intersections	*xs;

	xs = malloc(sizeof(t_intersections));
	if (!xs)
		return (memory_alloc_error(err));
	xs->arr = malloc(sizeof(t_intersection) * xs_count);
	if (!xs->arr)
	{
		free(xs);
		return (memory_alloc_error(err));
	}
	return (xs);
}

t_intersection	intersection(double t, t_object *object)
{
	t_intersection	intersection;

	intersection.t = t;
	intersection.object = object;
	return (intersection);
}

t_intersection	hit(t_intersections *xs)
{
	int				i;
	t_intersection	closest;

	i = -1;
	closest = (t_intersection){DBL_MAX, NULL};
	while (++i < xs->count)
	{
		if (xs->arr[i].t >= 0)
		{
			if (xs->arr[i].t < closest.t)
				closest = xs->arr[i];
		}
	}
	return (closest);
}

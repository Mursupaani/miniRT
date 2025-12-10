/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:36:27 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/09 18:34:06 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersection	*add_intersection(t_intersections *cur, t_intersections *xs)
{
	t_intersection *temp;
	int				i;

	if (!cur || !xs)
		return (NULL);
	if (xs->count == 2)
	{
		xs->xs = malloc(sizeof(t_intersection) * 2);
		xs->xs[0] = cur->xs[0];
		xs->xs[1] = cur->xs[1];
	}
	else
	{
		temp = xs->xs;
		xs->xs = malloc(sizeof(t_intersection) * (xs->count));
		if (!xs->xs)
			return (NULL);
		i = -1;
		while (++i < xs->count - 2)
			xs->xs[i] = temp[i];
		xs->xs[i++] = cur->xs[0];
		xs->xs[i] = cur->xs[1];
	}
	return (xs->xs);
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
	xs->count = 0;
	i = -1;
	while (w->objects[++i])
	{
		current = intersect(w->objects[i], r);
		if (!current)
			continue ;
		xs->count += current->count;
		xs->xs = add_intersection(current, xs);
		quick_sort_intersections(&xs->xs, 0, xs->count - 1);
	}
	return (xs);
}

int	count_intersections(t_intersection **xs)
{
	int	i;

	if (!xs || !*xs)
		return (-1);
	i = -1;
	while (xs[i])
		i++;
	return (i);

}

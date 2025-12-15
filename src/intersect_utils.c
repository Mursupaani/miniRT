/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:36:56 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/09 18:39:55 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	swap_intersections(t_intersection *x1, t_intersection *x2)
{
	t_intersection	temp;

	temp = *x1;
	*x1 = *x2;
	*x2 = temp;
}

static int	partition(t_intersection *xs, int start, int end)
{
	double	pivot;
	int		store_i;
	int		i;

	pivot = xs[end].t;
	store_i = start - 1;
	i = start;
	while (i < end)
	{
		if (xs[i].t < pivot)
		{
			store_i++;
			swap_intersections(&xs[i], &xs[store_i]);
		}
		i++;
	}
	swap_intersections(&xs[store_i + 1], &xs[end]);
	return (store_i + 1);
}

void	quick_sort_intersections(t_intersection *xs, int start, int end)
{
	int	pivot;

	if (start < end)
	{
		pivot = partition(xs, start, end);
		quick_sort_intersections(xs, start, pivot - 1);
		quick_sort_intersections(xs, pivot + 1, end);
	}
}

